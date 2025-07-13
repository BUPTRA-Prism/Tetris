#include "conf/sceneconf.h"

const std::string TITLE_SCENE::NAME = "title";
const SDL_Color TITLE_SCENE::BGCOLOR = { 0, 0, 0, 255 };
const TextConf TITLE_SCENE::START_TEXT_CONF = { "PUSH START", { 224, 608 }, { 255, 255, 255, 255 } };
const TextConf TITLE_SCENE::YEAR_TEXT_CONF = { "1989", { 352, 768 }, { 255, 255, 255, 255 } };
const TextConf TITLE_SCENE::COPYRIGHT_ICON_CONF = { "", { 288, 768 }, { 188, 190, 0, 255 } };

const std::string MENU_SCENE::NAME = "menu";
const SDL_Color MENU_SCENE::BGCOLOR = { 0, 0, 0, 255 };
const TextConf MENU_SCENE::GAME_TYPE_TITLE_TEXT_CONF = { "GAME  TYPE", { 160, 96 }, { 255, 255, 255, 255 } };
const std::vector<TextConf> MENU_SCENE::GAME_TYPE_TEXT_CONF = {
    { "A-TYPE", { 288, 224 }, { 255, 255, 255, 255 } },
    { "B-TYPE", { 672, 224 }, { 255, 255, 255, 255 } }
};
const TextConf MENU_SCENE::MUSIC_TYPE_TITLE_TEXT_CONF = { "MUSIC TYPE", { 160, 384 }, { 255, 255, 255, 255 } };
const std::vector<TextConf> MENU_SCENE::MUSIC_TYPE_TEXT_CONF = {
    { "MUSIC  1", { 448, 544 }, { 255, 255, 255, 255 } },
    { "MUSIC  2", { 448, 608 }, { 255, 255, 255, 255 } },
    { "MUSIC  3", { 448, 672 }, { 255, 255, 255, 255 } },
    { "OFF", { 512, 736 }, { 255, 255, 255, 255 } },
};
const std::array<std::vector<SDL_Point>, 2> MENU_SCENE::GAME_TYPE_OPTION_POS = {
    std::vector<SDL_Point>{ { 252, 224 }, { 636, 224 } },
    std::vector<SDL_Point>{ { 488, 224 }, { 872, 224 } }
};
const std::array<std::vector<SDL_Point>, 2> MENU_SCENE::MUSIC_TYPE_OPTION_POS = {
    std::vector<SDL_Point>{ { 412, 544 }, { 412, 608 }, { 412, 672 }, { 412, 736 } },
    std::vector<SDL_Point>{ { 712, 544 }, { 712, 608 }, { 712, 672 }, { 712, 736 } },
};
const int MENU_SCENE::OPTION_SHOW_FRAME = 3;
const int MENU_SCENE::OPTION_HIDE_FRAME = 1;

const std::string SETTING_SCENE::NAME = "setting";
const SDL_Color SETTING_SCENE::BGCOLOR = { 0, 0, 0, 255 };
const SDL_Point SETTING_SCENE::TYPE_FRAME_POS = { 100 , 36 };
const std::string SETTING_SCENE::GAME_TYPE_A_STR = "A-TYPE";
const std::string SETTING_SCENE::GAME_TYPE_B_STR = "B-TYPE";
const TextConf SETTING_SCENE::GAME_TYPE_TEXT_CONF = { "", { 416, 64 }, { 255, 255, 255, 255 } };

const std::string GAME_SCENE::NAME = "game";
const SDL_Color GAME_SCENE::BGCOLOR = { 0, 0, 0, 255 };

const std::string PAUSE_SCENE::NAME = "pause";
const SDL_Color PAUSE_SCENE::BGCOLOR = { 0, 0, 0, 255 };

const std::string COUNT_SCENE::NAME = "count";
const SDL_Color COUNT_SCENE::BGCOLOR = { 0, 0, 0, 255 };