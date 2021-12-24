#ifndef CHIP8_H
#define CHIP8_H

#include <iostream>
#include <cstdint>
#include <fstream>
#include <random>
#include <time.h>
#include <string.h>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;
const unsigned int VIDEO_WIDTH = 64;
const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_SIZE = VIDEO_WIDTH * VIDEO_HEIGHT;

class Chip8 {
    private:
        uint8_t registers[16] {};
        uint8_t memory[4096] {};
        uint16_t index {};
        uint16_t pc {};
        uint16_t stack[16] {};
        uint8_t sp {};
        uint8_t delayTimer {};
        uint8_t soundTimer {};
        uint8_t keypad[16] {};
        uint32_t video[VIDEO_SIZE] {};
        uint16_t opcode {};
        std::default_random_engine randEngine;

        void throwUnknownOpcode(uint16_t code);

    public:
        Chip8();
        uint8_t* getKeypad();
        uint32_t* getVideo();
        void loadRom(std::string fileName);
        uint8_t getRandomNumber();
        void emulateCycle();
};

#endif