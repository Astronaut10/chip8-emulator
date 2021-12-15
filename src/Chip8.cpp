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

void Chip8::emulateCycle() {
    opcode = memory[pc] << 8 | memory[pc+1];
    pc += 2;
    uint8_t vx = (opcode & 0x0F00) >> 8;
    uint8_t vy = (opcode & 0x00F0) >> 4;
    uint8_t kk = opcode & 0x00FF;
    uint16_t nnn = opcode & 0x0FFF;

    switch (opcode & 0xF000) {
        case 0x0000:
            switch (opcode & 0x00FF){
                case 0x00E0:
                    memset(video, 0, VIDEO_SIZE);
                    break;
                case 0x00EE:
                    pc = stack[--sp];
                    break;
                case 0x0000:
                    break;
                default:
                    cout << "Unknown opcode: " + opcode << endl;
                    break;
            }
            break;
        case 0x1000:
            pc = opcode & nnn;
            break;
        case 0x2000:
            stack[sp] = pc;
            ++sp;
            pc = opcode & nnn;
            break;
        case 0x3000:
            if (registers[vx] == opcode & kk) {
                pc +=2;
            }
            break;
        case 0x4000:
            if (registers[vx] != opcode & kk) {
                pc += 2;
            }
            break;
        case 0x5000:
            if (registers[vx] == registers[(opcode & 0x00F0) >> 4]) {
                pc += 2;
            }
            break;
        case 0x6000:
            registers[vx] = opcode & kk;
            break;
        case 0x7000:
            registers[vx] += opcode & kk;
            break;
        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0000:
                    registers[vx] = registers[vy];
                    break;
                case 0x0001:
                    registers[vx] |= registers[vy];
                    break;
                case 0x0002:
                    registers[vx] &= registers[vy];
                    break;
                case 0x0003:    
                    registers[vx] ^= registers[vy]; 
                    break;
                case 0x0004:
                    {
                        uint16_t sum = registers[vx] + registers[vy];
                        if (sum > 0x00FF) {
                            registers[0xF] = 1;
                        }
                        else {
                            registers[0xF] = 0;
                        }
                        registers[vx] = sum & 0xFF;
                    }
                    break;
                case 0x0005:
                    registers[0xF] = registers[vx] > registers[vy];
                    registers[vx] -= registers[vy];
                    break;
                case 0x0006:
                    registers[0xF] = registers[vx] & 0x1;
                    registers[vx] /= 2;
                    break;
                case 0x0007:
                    registers[0xF] = registers[vy] > registers[vx];
                    registers[vx] = registers[vy] - registers[vx];
                    break;
                case 0x000E:
                    registers[0xF] = (registers[vx] & 0x80) >> 7;
                    registers[vx] *= 2;
                    break;
                default:
                    // TODO: Throw error
                    break;
            }
            break;
        case 0x9000:
            if (registers[vx] != registers[vy]) {
                pc += 2;
            }
            break;
        case 0xA000:
            index = opcode & nnn;
            break;
        case 0xB000:
            pc = nnn + registers[0];
            break;
        case 0xC000:
            registers[vx] = getRandomNumber() & kk;
            break;
        case 0xD000:

            break;
        case 0xE000:
            switch (opcode & 0x00FF) {
                case 0x009E:
                    
                    break;
                case 0x00A1:

                    break;
                default:
                    // TODO
                    break;
            }
            break;
        case 0xF000:
            switch(opcode & 0x00FF) {
                case 0x0007:
                    break;
                case 0x000A:
                    break;
                case 0x0015:
                    break;
                case 0x0018:
                    break;
                case 0x001E:
                    break;
                case 0x0029:
                    break;
                case 0x0033:
                    break;
                case 0x0055:
                    break;
                case 0x0065:
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}