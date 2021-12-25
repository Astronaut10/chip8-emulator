#include <iostream>
#include <chrono>
#include "Chip8.h"
#include "Display.h"

using namespace std;

int main(int argc, char* args[]) {
    if  (argc != 3) {
        cerr << "Usage: " << "[Delay] [ROM]" << endl;
        exit(EXIT_FAILURE);
    }
    int delay = stoi(args[1]);
    string romFile = args[2];
    Chip8 chip8 = Chip8();
    Display display = Display("CHIP-8", VIDEO_WIDTH, VIDEO_HEIGHT);
    auto lastCycleTime = std::chrono::high_resolution_clock::now();
	bool quit = false;

    chip8.loadRom(romFile);

    while (!quit) {
        quit = display.handleInput(chip8.getKeypad());
        auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, 
                   std::chrono::milliseconds::period>
                   (currentTime - lastCycleTime).count();
        
        if (dt > delay) {
            lastCycleTime = currentTime;
            chip8.emulateCycle();
            display.update(chip8.getVideo(), VIDEO_WIDTH);
        }
    }

    return 0;
}