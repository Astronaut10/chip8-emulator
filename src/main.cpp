#include <iostream>
#include "Chip8.h"
#include "Display.h"

using namespace std;

int main(int argc, char* args[]) {
    Chip8 c = Chip8();
    Display d = Display("Window", 300, 300);
    
    return 0;
}