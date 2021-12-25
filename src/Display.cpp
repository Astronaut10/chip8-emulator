#include "Display.h"

using namespace std;

Display::Display(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw "Could not initialize SDL";
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED,
                              width*SCALE, height*SCALE, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                                SDL_TEXTUREACCESS_STREAMING, width, height);
    keymap.emplace(SDLK_x, 0);
    keymap.emplace(SDLK_1, 1);
    keymap.emplace(SDLK_2, 2);
    keymap.emplace(SDLK_3, 3);
    keymap.emplace(SDLK_q, 4);
    keymap.emplace(SDLK_w, 5);
    keymap.emplace(SDLK_e, 6);
    keymap.emplace(SDLK_a, 7);
    keymap.emplace(SDLK_s, 8);
    keymap.emplace(SDLK_d, 9);
    keymap.emplace(SDLK_z, 10);
    keymap.emplace(SDLK_c, 11);
    keymap.emplace(SDLK_4, 12);
    keymap.emplace(SDLK_r, 13);
    keymap.emplace(SDLK_f, 14);
    keymap.emplace(SDLK_v, 0xF);

}

Display::~Display() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Display::handleInput(uint8_t *keypad) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDLK_ESCAPE) {
            return true;
        }
        else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            keypad[keymap[event.key.keysym.sym]] 
                = event.type == SDL_KEYDOWN ? 1 : 0;
        }
    }

    return false;
}

void Display::update(uint32_t const* buffer, int pitch) {
    SDL_UpdateTexture(texture, nullptr, buffer, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}