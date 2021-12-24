#include <iostream>
#include <chrono>
#include "Chip8.h"
#include "Display.h"

using namespace std;

int main(int argc, char* args[]) {
    string romFile = args[1];
    Chip8 chip8 = Chip8();
    Display display = Display("CHIP-8", 300, 300);
    int videoPitch = 3 * VIDEO_WIDTH;
    auto lastCycleTime = std::chrono::high_resolution_clock::now();
	bool quit = false;

    chip8.loadRom(romFile);

    while (!quit) {
        quit = display.handleInput(chip8.getKeypad());
        auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, 
                   std::chrono::milliseconds::period>
                   (currentTime - lastCycleTime).count();
        
        if (dt > 1) {
            lastCycleTime = currentTime;
            chip8.emulateCycle();
            display.update(chip8.getVideo(), videoPitch);
        }
    }

    return 0;
}