#ifndef DISPLAY_H
#define DISPLAY_H
#define SDL_MAIN_HANDLED

#include "include/SDL2/SDL.h"

class Display {
    private:
        SDL_Window* window;
    public:
        Display(const char* title, int width, int height);
};


#endif