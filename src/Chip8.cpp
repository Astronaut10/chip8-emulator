#include "Chip8.h"

using namespace std;

Chip8::Chip8() : randEngine(time(0)) {
    this->pc = START_ADDRESS;

    uint8_t fontset[FONTSET_SIZE] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for (int i = 0, j = FONTSET_START_ADDRESS ; i < FONTSET_SIZE ; ++i, ++j) {
        this->memory[j] = fontset[i];
    }

}

void Chip8::loadRom(string fileName) {
    ifstream file(fileName, ios::binary | ios::ate);
    if (file.is_open()) {
        streampos size = file.tellg();
        char* block = new char[size];
        file.seekg(0, ios::beg);
        file.read(block, size);
        file.close();
        
        for (int i = 0 ; i < size ; i++) {
            memory[START_ADDRESS + i] = block[i];
        }
        delete[] block;
    }
}

uint8_t Chip8::getRandomNumber() {
    uniform_int_distribution<uint8_t> distribution(0, 255);
    
    return distribution(this->randEngine);
}