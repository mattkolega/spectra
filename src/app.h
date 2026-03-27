#pragma once

#include <SDL3/SDL.h>

typedef struct App {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
} App;

int app_init(App *app);

void app_run(App *app);

void app_shutdown(App *app);