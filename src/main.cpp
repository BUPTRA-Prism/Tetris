#define SDL_MAIN_HANDLED

#include "conf/basicconf.h"
#include "core/context.h"
#include "scene/scenemanager.h"
#include <iostream>

int main(int argc, char* argv[]) {
    SDLInitializer init(SDL_INIT_VIDEO);
    if (!init.isSuccess()) {
        return 1;
    }
    
    {
        UniqueWindow window(
            SDL_CreateWindow(SCREEN_TITLE.c_str(), 
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH, SCREEN_HEIGHT, 
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

        ResourceManager& resourceManager = ResourceManager::getInstance();
        if (!resourceManager.loadResource(renderer.get())) {
            std::cerr << "Load Resource Error: " << SDL_GetError() << std::endl;
            resourceManager.destroyResource();
            return 1;
        }

        Context ctx(resourceManager, renderer.get());
        SceneManager& sceneManager = SceneManager::getInstance(ctx);

        bool running = true;
        while (running) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }

            sceneManager.onUpdate();
            sceneManager.onRender();

            SDL_Delay(MSPF);
        }

        resourceManager.destroyResource();
    }
    
    return 0;
}