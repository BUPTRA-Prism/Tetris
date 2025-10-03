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
    inline const std::string NAME = "menu";                             // 场景名
    inline const std::string GAME_TYPE_TITLE_STR = "GAME  TYPE";        // 游戏模式标题内容
    inline const SDL_Point GAME_TYPE_TITLE_POS = { 160, 96 };           // 游戏模式标题位置
    inline const SDL_Point GAME_TYPE_OPTION_POS = { 288, 224 };         // 游戏模式选项位置
    inline const int GAME_TYPE_OPTION_SPACING = 384;                    // 游戏模式选项间距
    inline const std::string MUSIC_TYPE_TITLE_STR = "MUSIC TYPE";       // 音乐模式标题内容
    inline const SDL_Point MUSIC_TYPE_TITLE_POS = { 160, 384 };         // 音乐模式标题位置
    inline const SDL_Point MUSIC_TYPE_OPTION_POS = { 448, 544 };        // 音乐模式选项位置
    inline const int MUSIC_TYPE_OPTION_SPACING = 64;                    // 音乐模式选项间距
    inline const SDL_Point GAME_TYPE_OPTION_ICON_POS = { 252, 224 };    // 游戏模式选项图标位置
    inline const int GAME_TYPE_OPTION_ICON_INNER_SPACING = 236;         // 游戏模式选项图标组内间距
    inline const int GAME_TYPE_OPTION_ICON_OUTER_SPACING = 384;         // 游戏模式选项图标选项间距
    inline const SDL_Point MUSIC_TYPE_OPTION_ICON_POS = { 412, 544 };   // 音乐模式选项图标位置
    inline const int MUSIC_TYPE_OPTION_ICON_INNER_SPACING = 300;        // 游戏模式选项图标组内间距
    inline const int MUSIC_TYPE_OPTION_ICON_OUTER_SPACING = 64;         // 游戏模式选项图标选项间距
    inline const int OPTION_ICON_SHOW_FRAME = 3;                        // 选项图标显示帧数
    inline const int OPTION_ICON_HIDE_FRAME = 1;                        // 选项图标隐藏帧数
};

// 设置场景
namespace SETTING_SCENE {
    inline const std::string NAME = "setting";                          // 场景名
    inline const SDL_Point GAME_TYPE_FRAME_POS = { 100, 36 };           // 游戏模式框架位置
    inline const SDL_Point GAME_TYPE_TITLE_POS = { 416, 64 };           // 游戏模式标题位置
    inline const SDL_Point LEVEL_FRAME_POS = { 204, 200 };              // 关卡选项框架位置
    inline const std::string LEVEL_TITLE_STR = "LEVEL";                 // 关卡选项标题内容
    inline const SDL_Point LEVEL_TITLE_POS = { 288, 224 };              // 关卡选项标题位置
    inline const SDL_Point HEIGHT_FRAME_POS = { 616, 200 };             // 高度选项框架位置
    inline const std::string HEIGHT_TITLE_STR = "HEIGHT";               // 高度选项标题内容
    inline const SDL_Point HEIGHT_TITLE_POS = { 640, 224 };             // 高度选项标题位置
    inline const SDL_Point LEVEL_OPTION_ICON_POS = { 208, 304 };        // 关卡选项图标位置
    inline const SDL_Point HEIGHT_OPTION_ICON_POS = { 624, 304 };       // 高度选项图标位置
    inline const int OPTION_ROW_NUM = 2;                                // 选项行数
    inline const int OPTION_ICON_SPACING = 64;                          // 选项间距
    inline const int OPTION_MARGIN = 16;                                // 选项边距
    inline const SDL_Color OPTION_COLOR = { 181, 49, 32, 255 };         // 选项文本颜色
    inline const SDL_Point OPTION_ICON_SIZE = { 64, 64 };               // 选项图标尺寸
    inline const SDL_Color OPTION_ICON_COLOR = { 234, 158, 34, 255 };   // 选项图标颜色
    inline const int OPTION_ICON_SHOW_FRAME = 3;                        // 选项图标显示帧数
    inline const int OPTION_ICON_HIDE_FRAME = 1;                        // 选项图标隐藏帧数
    inline const SDL_Point RECORD_ORDER_POS = { 224, 608 };             // 记录表名词位置
    inline const SDL_Point RECORD_POS = { 288, 544 };                   // 记录表位置
    inline const int RECORD_ROW_SPACING = 64;                           // 记录表行间距
    inline const int RECORD_COL_SPACING = 224;                          // 记录表列间距
    inline const std::vector<std::string> RECORD_TITLE_STR = { " NAME", "SCORE", "LV" };   // 记录表头内容
    inline const int RECORD_SCORE_MAX_LEN = 6;      // 记录分数最大长度
    inline const int RECORD_LV_MAX_LEN = 2;         // 记录关卡数最大长度
};

// 游戏场景
namespace GAME_SCENE {
    inline const std::string NAME = "game";                             // 场景名
    inline const SDL_Point GAME_TYPE_TITLE_POS = { 96, 96 };            // 游戏类型标题位置
    inline const SDL_Point TETRIS_COUNT_POS = { 192, 352 };             // 方块计数区域位置
    inline const SDL_Point TETRIS_MODE_CENTER_POS = { 138, 366 };       // 方块模板位置
    inline const SDL_Point NEXT_TETRIS_CENTER_POS = { 830, 478 };
    inline const int TETRIS_COUNT_SPACING = 64;                         // 方块计数区域间距
    inline const SDL_Color TETRIS_COUNT_COLOR = { 181, 49, 32, 255 };   // 方块计数文本颜色
    inline const std::string LINE_COUNT_STR = "LINES-";                 // 消除行文本内容
    inline const SDL_Point LINE_COUNT_POS = { 416, 64 };                // 消除行文本位置
    inline const std::string TOP_TITLE_STR = "TOP";                     // 最高分标题文本
    inline const std::string SCORE_TITLE_STR = "SCORE";                 // 分数标题文本
    inline const SDL_Point TOP_POS = { 768, 96 };                       // 最高分区域位置
    inline const SDL_Point SCORE_POS = { 768, 192 };                    // 分数区域位置 
    inline const int SCORE_SPACING = 32;                                // 分数区域间距
    inline const std::string NEXT_TETRIS_TITLE_STR = "NEXT";            // 下一个方块标题文本
    inline const SDL_Point NEXT_TETRIS_TITLE_POS = { 768, 384 };        // 下一个方块区域位置
    inline const std::string LEVEL_TITLE_STR = "LEVEL";                 // 关卡标题文本
    inline const SDL_Point LEVEL_TITLE_POS = { 768, 608 };                    // 关卡标题位置
    inline const SDL_Point LEVEL_TEXT_POS = { 800, 640 };                    // 关卡文本位置
    inline const int LEVEL_SPACING = 32;                                // 关卡区域间距
    inline const int TETRIS_COUNT_MAX_LEN = 3;                          // 方块计数最大长度
    inline const int LINE_COUNT_MAX_LEN = 3;                            // 消除行数最大长度
    inline const int SCORE_MAX_LEN = 6;                                 // 分数最大长度
    inline const int LEVEL_MAX_LEN = 2;                                 // 关卡数最大长度
    inline const SDL_Point TETRIS_FIELD_POS = { 384, 764 };
    inline const int TETRIS_SPACING = 32;
    inline const int TETRIS_SIZE = 28;
    inline const int TETRIS_MODE_SPACING = 24;
    inline const int TETRIS_MODE_SIZE = 20;
    inline const SDL_Color TETRIS_BASIC_COLOR = { 255, 255, 255, 255 };
    inline const std::vector<SDL_Color> TETRIS_PATTERN_DARK_COLOR = {
        { 0, 88, 248, 255 },
        { 0, 168, 0, 255 },
        { 216, 0, 204, 255 },
        { 0, 88, 248, 255 },
        { 228, 0, 88, 255 },
        { 88, 248, 152, 255 },
        { 248, 56, 0, 255 },
        { 104, 68, 252, 255 },
        { 0, 88, 248, 255 },
        { 248, 56, 0, 255 }
    };
    inline const std::vector<SDL_Color> TETRIS_PATTERN_LIGHT_COLOR = {
        { 60, 188, 252, 255 },
        { 184, 248, 24, 255 },
        { 248, 120, 248, 255 },
        { 88, 216, 84, 255 },
        { 88, 248, 152, 255 },
        { 104, 136, 252, 255 },
        { 124, 124, 124, 255 },
        { 168, 0, 32, 255 },
        { 248, 56, 0, 255 },
        { 252, 160, 68, 255 }
    };
    inline const SDL_Point RESULT_OUTER_FRAME_POS = { 384, 384 };
    inline const SDL_Point RESULT_INNER_FRAME_POS = { 400, 400 };
    inline const SDL_Point RESULT_TEXT_POS = { 416, 416 };
    inline const std::string WIN_TEXT_STR = "YOU  WIN";
    inline const std::string LOSE_TEXT_STR = "YOU LOSE";
};

// 结算场景
namespace COUNT_SCENE {
    inline const std::string NAME = "count";        // 场景名
    inline const std::vector<std::string> COUNT_TEXT_STR = {
        "CONGRATULATIONS",
        "YOU ARE A",
        "TETRIS MASTER.",
        "PLEASE ENTER YOUR NAME"
    };
    inline const std::vector<SDL_Point> COUNT_TEXT_POS = {
        { 288, 192 }, { 352, 288 }, { 288, 352 }, { 160, 448 }
    };
    inline const SDL_Color COUNT_TITLE_COLOR = { 181, 49, 32, 255 };
    inline const SDL_Color RECORD_NAME_ICON_COLOR = { 255, 129, 112, 255 };
    inline const int RECORD_NAME_ICON_SIZE = 32;
    inline const int RECORD_NAME_ICON_SPACING = 32;
    inline const int RECORD_NAME_ICON_SHOW_FRAME = 3;
    inline const int RECORD_NAME_ICON_HIDE_FRAME = 1;
    inline const std::string RECORD_NAME_OPTIONAL_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,/()\". -";
    inline const int RECORD_NAME_CHANGE_FRAME = 8;
};