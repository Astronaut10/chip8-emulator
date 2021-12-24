#ifndef DISPLAY_H
#define DISPLAY_H
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <iostream>
#include <map>

class Display {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        std::map<SDL_Keycode, uint8_t> keymap;
        
    public:
        Display(const char* title, int width, int height);
        ~Display();
        bool handleInput(uint8_t *keypad);
        void update(uint32_t const* buffer, int pitch);
};


#endif