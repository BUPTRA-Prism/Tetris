#pragma once

#include <array>
#include <string>
#include <utility>
#include <vector>
#include <SDL.h>

struct TextConf {
    const std::string STR;
    SDL_Point POS;
    SDL_Color COLOR;
};

namespace TITLE_SCENE {
    extern const std::string NAME;
    extern const SDL_Color BGCOLOR;
    extern const TextConf START_TEXT_CONF;
    extern const TextConf YEAR_TEXT_CONF;
    extern const TextConf COPYRIGHT_ICON_CONF;
};

namespace MENU_SCENE {
    extern const std::string NAME;
    extern const SDL_Color BGCOLOR;
    extern const TextConf GAME_TYPE_TITLE_TEXT_CONF;
    extern const std::vector<TextConf> GAME_TYPE_TEXT_CONF;
    extern const TextConf MUSIC_TYPE_TITLE_TEXT_CONF;
    extern const std::vector<TextConf> MUSIC_TYPE_TEXT_CONF;
    extern const std::array<std::vector<SDL_Point>, 2> GAME_TYPE_OPTION_POS;
    extern const std::array<std::vector<SDL_Point>, 2> MUSIC_TYPE_OPTION_POS;
    extern const int OPTION_SHOW_FRAME;
    extern const int OPTION_HIDE_FRAME;
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