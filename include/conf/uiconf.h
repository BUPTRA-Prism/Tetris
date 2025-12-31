#pragma once

#include <string>
#include <vector>
#include <SDL.h>

namespace FONT {
    inline const int SIZE = 28;
    inline const int SPACING = 32;
}

namespace SCOREBOARD {
    inline const SDL_Point POS = { 200, 36 };
    inline const std::string SCORE_TEXT_STR = "SCORE";
    inline const SDL_Point SCORE_TEXT_POS = { 432, 36 };
    inline const std::string LINE_TEXT_STR = "LINES";
    inline const SDL_Point LINE_TEXT_POS = { 432, 100 };
    inline const std::string LEVEL_TEXT_STR = "LEVEL";
}

namespace FIREWORK {
    inline const std::vector<int> FRAME_TARGETS = { 8, 8, 8, 12, 12 };
    inline const std::vector<SDL_Point> INNER_POS_DELTA = { 
        { -10, -10 }, { -30, -30 }, { -66, -70 }, { -98, -102 }, { -98, -86 } 
    };
    inline const std::vector<SDL_Point> OUTER_POS_DELTA = { 
        { -26, -26 }, { -46, -46 }, { -82, -86 }, { -106, -110 }, { -106, -94 } 
    };
}

namespace TITLE_SCENE {
    inline const std::string NAME = "title";
    inline const std::string TITLE_TEXT_STR = "THE SOVIET MIND GAME";
    inline const SDL_Point TITLE_TEXT_POS = { 192, 178 };
    inline const SDL_Color TITLE_TEXT_COLOR = { 255, 154, 56, 255 };
    inline const SDL_Point TITLE_IMAGE_POS = { 256, 226 };
    inline const int FIREWORK_TARGET = 12;
    inline const int FIREWORK_CREATE_FRAME_TARGET = 85;
    inline const SDL_Rect FIREWORK_BORDER = { 160, 320, 576, 128 };
    inline const std::vector<SDL_Color> FIREWORK_ALT_COLORS = {
        { 255, 117, 97, 255 },
        { 219, 40, 0, 255 },
        { 255, 219, 170, 255 },
        { 203, 77, 12, 255 },
        { 60, 190, 255, 255 },
        { 0, 113, 239, 255 }
    };
}

namespace SETTING_SCENE {
    inline const std::string NAME = "setting";
    inline const SDL_Point LOGO_POS = { 144, 300 };
    inline const SDL_Point LEVEL_TEXT_POS = { 432, 164 };
    inline const SDL_Color SETTING_TEXT_COLOR = { 32, 56, 239, 255 };
    inline const std::string GAME_SELECT_TEXT_STR = "GAME SELECT";
    inline const SDL_Point GAME_SELECT_TEXT_POS = { 320, 420 };
    inline const std::string LEVEL_SELECT_TEXT_STR = "LEVEL SELECT";
    inline const SDL_Point LEVEL_SELECT_TEXT_POS = { 320, 292 };
    inline const std::string HANDICAP_SELECT_TEXT_STR = "HANDICAP SELECT";
    inline const SDL_Point HANDICAP_SELECT_TEXT_POS = { 288, 292 };
    inline const std::string MUSIC_SELECT_TEXT_STR = "MUSIC SELECT";
    inline const SDL_Point MUSIC_SELECT_TEXT_POS = { 352, 292 };
    inline const int SELECT_OPTION_SPACING = 32;
    inline const SDL_Point GAME_SELECT_OPTION_TEXT_START_POS = { 384, 484 };
    inline const SDL_Point GAME_SELECT_OPTION_ARROW_START_POS = { 320, 480 };
    inline const SDL_Point LEVEL_SELECT_OPTION_TEXT_START_POS = { 480, 356 };
    inline const SDL_Point LEVEL_SELECT_OPTION_ARROW_START_POS = { 416, 352 };
    inline const SDL_Point HANDICAP_SELECT_OPTION_TEXT_START_POS = { 448, 356 };
    inline const SDL_Point HANDICAP_SELECT_OPTION_ARROW_START_POS = { 416, 352 };
    inline const SDL_Point MUSIC_SELECT_OPTION_TEXT_START_POS = { 416, 356 };
    inline const SDL_Point MUSIC_SELECT_OPTION_ARROW_START_POS = { 352, 352 };
}

namespace GAME_SCENE {
    inline const std::string NAME = "game";
    inline const SDL_Point VERSUS_LEVEL_TEXT_POS = { 432, 164 };
    inline const SDL_Point COOP_LEVEL_TEXT_POS = { 64, 324 };
    inline const std::string NEXT_TEXT_STR = "NEXT";
    inline const SDL_Point NEXT_TEXT_1_POS = { 68, 36 };
    inline const SDL_Point NEXT_TEXT_2_POS = { 836, 36 };
    inline const SDL_Color NEXT_TEXT_COLOR = { 219, 40, 0, 255 };
}