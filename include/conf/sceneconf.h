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
    inline const std::string NAME = "setting";                          // 场景名
    inline const SDL_Point GAME_TYPE_FRAME_POS = { 100, 36 };           // 游戏模式框架位置
    inline const SDL_Point GAME_TYPE_TEXT_POS = { 416, 64 };            // 游戏模式文本位置
    inline const SDL_Point LEVEL_FRAME_POS = { 204, 200 };              // 关卡选项框架位置
    inline const std::string LEVEL_TEXT_STR = "LEVEL";                  // 关卡选项标题文本内容
    inline const SDL_Point LEVEL_TEXT_POS = { 288, 224 };               // 关卡选项标题文本位置
    // 关卡选项文本位置
    inline const std::vector<SDL_Point> LEVEL_OPTION_TEXT_POS = {
        { 224, 320 }, { 288, 320 }, { 352, 320 }, { 416, 320 }, { 480, 320 }, 
        { 224, 384 }, { 288, 384 }, { 352, 384 }, { 416, 384 }, { 480, 384 }
    };
    // 关卡选项图标位置
    inline const std::vector<SDL_Point> LEVEL_OPTION_ICON_POS = {
        { 208, 304 }, { 272, 304 }, { 336, 304 }, { 400, 304 }, { 464, 304 }, 
        { 208, 368 }, { 272, 368 }, { 336, 368 }, { 400, 368 }, { 464, 368 }
    }; 
    inline const SDL_Point HEIGHT_FRAME_POS = { 616, 200 };             // 高度选项框架位置
    inline const std::string HEIGHT_TEXT_STR = "HEIGHT";                // 高度选项标题文本内容
    inline const SDL_Point HEIGHT_TEXT_POS = { 640, 224 };              // 高度选项标题文本位置
    // 高度选项文本位置
    inline const std::vector<SDL_Point> HEIGHT_OPTION_TEXT_POS = {
        { 640, 320 }, { 704, 320 }, { 768, 320 },
        { 640, 384 }, { 704, 384 }, { 768, 384 }
    };
    // 高度选项图标位置
    inline const std::vector<SDL_Point> HEIGHT_OPTION_ICON_POS = {
        { 624, 304 }, { 688, 304 }, { 752, 304 },
        { 624, 368 }, { 688, 368 }, { 752, 368 }
    }; 
    inline const SDL_Color OPTION_TEXT_COLOR = { 181, 49, 32, 255 };    // 选项文本颜色
    inline const SDL_Point OPTION_ICON_SIZE = { 64, 64 };               // 选项图标尺寸
    inline const SDL_Color OPTION_ICON_COLOR = { 234, 158, 34, 255 };   // 选项图标颜色
    inline const int OPTION_ICON_SHOW_FRAME = 3;                        // 选项图标显示帧数
    inline const int OPTION_ICON_HIDE_FRAME = 1;                        // 选项图标隐藏帧数
    inline const std::vector<std::string> RECORD_TITLE_TEXT_STR = { "NAME", "SCORE", "LV" };                    // 记录表头文本内容
    inline const std::vector<SDL_Point> RECORD_TITLE_TEXT_POS = { { 320, 544 }, { 512, 544 }, { 736, 544 } };   // 记录表头文本位置
    inline const std::vector<SDL_Point> RECORD_ORDER_TEXT_POS = { { 224, 608 }, { 224, 672 }, { 224, 736 } };   // 记录名次文本位置
    inline const std::vector<SDL_Point> RECORD_NAME_TEXT_POS = { { 288, 608 }, { 288, 672 }, { 288, 736 } };    // 记录姓名文本位置
    inline const std::vector<SDL_Point> RECORD_SCORE_TEXT_POS = { { 512, 608 }, { 512, 672 }, { 512, 736 } };   // 记录分数文本位置
    inline const std::vector<SDL_Point> RECORD_LV_TEXT_POS = { { 736, 608 }, { 736, 672 }, { 736, 736 } };      // 记录关卡数文本位置
    inline const int RECORD_SCORE_MAX_LEN = 6;      // 记录分数最大长度
    inline const int RECORD_LV_MAX_LEN = 2;         // 记录关卡数最大长度
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