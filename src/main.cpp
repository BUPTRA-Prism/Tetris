#define SDL_MAIN_HANDLED

#include "conf/basicconf.h"
#include "framework/context.h"
#include "game/core.h"
#include "scene/scenemanager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    SDLInitializer init;
    if (!init.isSuccess()) {
        return 1;
    }

    UniqueWindow window(
        SDL_CreateWindow(WINDOW_NAME.c_str(), 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, WINDOW_HEIGHT, 
            SDL_WINDOW_SHOWN
        )
    );
    if (!window) {
        std::cerr << "Create Window Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    UniqueRenderer renderer(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED)
    );
    if (!renderer) {
        std::cerr << "Create Renderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    ResourceManager resourceManager;
    if (!resourceManager.loadResource(renderer.get())) {
        std::cerr << "Load Resource Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    AudioManager audioManager;
    InputManager inputManager;

    Context ctx(resourceManager, audioManager, inputManager, renderer.get());

    Settings settings;
    Core core(settings);

    SceneManager sceneManager(ctx, core);

    bool running = true;
    while (running) {
        inputManager.beginFrame();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            inputManager.processEvent(event);
        }

        sceneManager.onUpdate();
        sceneManager.onRender();

        SDL_Delay(FRAME_TIME);
    }
    
    return 0;
}