all:
	g++ -Wall -Isrc/include -Lsrc/lib -o main src/main.cpp src/Chip8.cpp src/Display.cpp -lSDL2main -lSDL2