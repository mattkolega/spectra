#include "app.h"

#include "logger.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

static void handle_events(bool *is_running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        *is_running = false;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_EVENT_QUIT:
                *is_running = false;
                break;
            default:
                break;
        }
	}
}

static void update(App *app) {

}

static void draw(App *app) {
    // Render to texture
    SDL_SetRenderTarget(app->renderer, app->texture);
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
    SDL_RenderClear(app->renderer);

    // Render to window
    SDL_SetRenderTarget(app->renderer, NULL);
    SDL_RenderTexture(app->renderer, app->texture, NULL, NULL);
    SDL_RenderPresent(app->renderer);
}

int app_init(App *app) {
    if (!SDL_SetAppMetadata("Spectra", "0.1.0", "com.mattkolega.spectra")) {
        log_error("Failed to set app metadata. (SDL_Error: %s)", SDL_GetError());
        return -1;
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        log_error("Failed to initialise SDL. (SDL_Error: %s)", SDL_GetError());
        return -1;
    }

    app->window = SDL_CreateWindow(
        "Spectra",
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (!app->window) {
        log_error("Failed to create window. (SDL_Error: %s)", SDL_GetError());
        return -1;
    }

    app->renderer = SDL_CreateRenderer(app->window, NULL);

    if (!app->renderer) {
        log_error("Failed to create renderer. (SDL_Error: %s)", SDL_GetError());
        return -1;
    }

    app->texture = SDL_CreateTexture(app->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!app->texture) {
        log_error("Failed to create texture. (SDL_Error: %s)", SDL_GetError());
        return -1;
    }

    const char *rendererName = SDL_GetRendererName(app->renderer);
    log_info("SDL Renderer - %s", rendererName ? rendererName : "null");

    return 0;
}

void app_run(App *app) {
    bool is_running = true;

    while (is_running) {
        handle_events(&is_running);
        update(app);
        draw(app);
    }
}

void app_shutdown(App *app) {
    if (app->texture) {
        SDL_DestroyTexture(app->texture);
        app->texture = NULL;
    }

    if (app->renderer) {
        SDL_DestroyRenderer(app->renderer);
        app->renderer = NULL;
    }

    if (app->window) {
        SDL_DestroyWindow(app->window);
        app->window = NULL;
    }

    if (SDL_WasInit(0) != 0) {
        SDL_Quit();
    }
}