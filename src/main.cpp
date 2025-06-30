#define SDL_MAIN_HANDLED

#include "conf/basicconf.h"
#include "util/sdlresource.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    {
        UniqueWindow window(
        SDL_CreateWindow(SCREEN_TITLE.c_str(), 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0));
    
        if (!window) {
            std::cerr << "Create Window Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }

        SDL_Delay(2000);
    }
    
    SDL_Quit();
    return 0;
}