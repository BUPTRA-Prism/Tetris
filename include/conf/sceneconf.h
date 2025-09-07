#pragma once

#include <array>
#include <string>
#include <utility>
#include <vector>
#include <SDL.h>

// 标题场景
namespace TITLE_SCENE {
    const std::string NAME = "title";                               // 场景名
    const std::string START_TEXT_STR = "PUSH START";                // 游戏开始文本内容
    const SDL_Point START_TEXT_POS = { 224, 608 };                  // 游戏开始文本位置
    const std::string YEAR_TEXT_STR = "1989";                       // 年份文本内容
    const SDL_Point YEAR_TEXT_POS =  { 352, 768 };                  // 年份文本位置
    const SDL_Point COPYRIGHT_ICON_POS = { 288, 768 };              // 版权图标位置
    const SDL_Color COPYRIGHT_ICON_COLOR =  { 188, 190, 0, 255 };   // 版权图标颜色
};

// 菜单场景
namespace MENU_SCENE {
    inline const std::string NAME = "menu";                         // 场景名
    inline const std::string GAME_TYPE_TEXT_STR = "GAME  TYPE";     // 游戏模式标题文本内容
    inline const SDL_Point GAME_TYPE_TEXT_POS = { 160, 96 };        // 游戏模式标题文本位置
    inline const std::vector<SDL_Point> GAME_TYPE_OPTION_TEXT_POS = { { 288, 224 }, { 672, 224 } }; // 游戏模式选项文本位置
    inline const std::string MUSIC_TYPE_TEXT_STR = "MUSIC TYPE";    // 音乐模式标题文本内容
    inline const SDL_Point MUSIC_TYPE_TEXT_POS = { 160, 384 };      // 音乐模式标题文本位置
    inline const std::vector<SDL_Point> MUSIC_TYPE_OPTION_TEXT_POS = { { 448, 544 }, { 448, 608 }, { 448, 672 }, { 512, 736 } };    // 音乐模式选项文本位置
    // 游戏模式选项图标位置
    inline const std::array<std::vector<SDL_Point>, 2> GAME_TYPE_OPTION_ICON_POS = {
        std::vector<SDL_Point>{ { 252, 224 }, { 636, 224 } },
        std::vector<SDL_Point>{ { 488, 224 }, { 872, 224 } }
    };
    // 音乐模式选项图标位置
    inline const std::array<std::vector<SDL_Point>, 2> MUSIC_TYPE_OPTION_ICON_POS = {
        std::vector<SDL_Point>{ { 412, 544 }, { 412, 608 }, { 412, 672 }, { 412, 736 } },
        std::vector<SDL_Point>{ { 712, 544 }, { 712, 608 }, { 712, 672 }, { 712, 736 } },
    };
    inline const int OPTION_ICON_SHOW_FRAME = 3;    // 选项图标显示帧数
    inline const int OPTION_ICON_HIDE_FRAME = 1;    // 选项图标隐藏帧数
};

// 设置场景
namespace SETTING_SCENE {
    inline const std::string NAME = "setting";      // 场景名
};

// 游戏场景
namespace GAME_SCENE {
    inline const std::string NAME = "game";     // 场景名
};

// 暂停场景
namespace PAUSE_SCENE {
    inline const std::string NAME = "pause";        // 场景名
};

// 结算场景
namespace COUNT_SCENE {
    inline const std::string NAME = "count";        // 场景名
};