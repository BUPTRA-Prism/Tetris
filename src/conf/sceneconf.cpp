#include "conf/sceneconf.h"

const std::string TITLE_SCENE::NAME = "title";
const SDL_Color TITLE_SCENE::BGCOLOR = {0, 0, 0, 255};
const std::string TITLE_SCENE::START_TEXT::STR = "PUSH START";
const SDL_Point TITLE_SCENE::START_TEXT::POS = { 224, 608 };
const SDL_Color TITLE_SCENE::START_TEXT::COLOR = { 255, 255, 255, 255 };
const std::string TITLE_SCENE::YEAR_TEXT::STR = "1989";
const SDL_Point TITLE_SCENE::YEAR_TEXT::POS = { 352, 768 };
const SDL_Color TITLE_SCENE::YEAR_TEXT::COLOR = { 255, 255, 255, 255 };
const SDL_Point TITLE_SCENE::COPYRIGHT_ICON::POS = { 288, 768 };
const SDL_Color TITLE_SCENE::COPYRIGHT_ICON::COLOR = { 188, 190, 0, 255 };

const std::string MENU_SCENE::NAME = "menu";
const SDL_Color MENU_SCENE::BGCOLOR = {0, 0, 0, 255};

const std::string SETTING_SCENE::NAME = "setting";
const SDL_Color SETTING_SCENE::BGCOLOR = {0, 0, 0, 255};

const std::string GAME_SCENE::NAME = "game";
const SDL_Color GAME_SCENE::BGCOLOR = {0, 0, 0, 255};

const std::string PAUSE_SCENE::NAME = "pause";
const SDL_Color PAUSE_SCENE::BGCOLOR = {0, 0, 0, 255};

const std::string COUNT_SCENE::NAME = "count";
const SDL_Color COUNT_SCENE::BGCOLOR = {0, 0, 0, 255};