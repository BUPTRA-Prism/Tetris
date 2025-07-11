#pragma once

#include <string>
#include <utility>
#include <SDL.h>

namespace TITLE_SCENE {
    extern const std::string NAME;
    extern const SDL_Color BGCOLOR;
    namespace START_TEXT {
        extern const std::string STR;
        extern const SDL_Point POS;
        extern const SDL_Color COLOR;
    };
    namespace YEAR_TEXT {
        extern const std::string STR;
        extern const SDL_Point POS;
        extern const SDL_Color COLOR;
    };
    namespace COPYRIGHT_ICON {
        extern const SDL_Point POS;
        extern const SDL_Color COLOR;
    }
};

namespace MENU_SCENE {
    extern const std::string NAME;
    extern const SDL_Color BGCOLOR;
};

namespace SETTING_SCENE {
    extern const std::string NAME;
    extern const SDL_Color BGCOLOR;
};

namespace GAME_SCENE {
    extern const std::string NAME;
    extern const SDL_Color BGCOLOR;
};

namespace PAUSE_SCENE {
    extern const std::string NAME;
    extern const SDL_Color BGCOLOR;
};

namespace COUNT_SCENE {
    extern const std::string NAME;
    extern const SDL_Color BGCOLOR;
};