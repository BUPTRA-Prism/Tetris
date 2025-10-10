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
    inline const std::string NAME = "menu";                                         // 场景名
    inline const std::string GAME_TYPE_TITLE_STR = "GAME  TYPE";                    // 游戏模式标题内容
    inline const SDL_Point GAME_TYPE_TITLE_POS = { 160, 96 };                       // 游戏模式标题位置
    inline const SDL_Point GAME_TYPE_OPTION_POS = { 288, 224 };                     // 游戏模式选项位置
    inline const int GAME_TYPE_OPTION_SPACING = 384;                                // 游戏模式选项间距
    inline const std::array<int, 2> GAME_TYPE_OPTION_ICON_OFFSET = { -36, 200 };    // 游戏模式选项图标位置偏移量
    inline const std::string MUSIC_TYPE_TITLE_STR = "MUSIC TYPE";                   // 音乐模式标题内容
    inline const SDL_Point MUSIC_TYPE_TITLE_POS = { 160, 384 };                     // 音乐模式标题位置
    inline const SDL_Point MUSIC_TYPE_OPTION_POS = { 448, 544 };                    // 音乐模式选项位置
    inline const int MUSIC_TYPE_OPTION_SPACING = 64;                                // 音乐模式选项间距
    inline const std::array<int, 2> MUSIC_TYPE_OPTION_ICON_OFFSET = { -36, 264 };   // 音乐模式选项图标位置偏移量
    inline const int OPTION_ICON_SHOW_FRAME = 3;                                    // 选项图标显示帧数
    inline const int OPTION_ICON_HIDE_FRAME = 1;                                    // 选项图标隐藏帧数
};

// 设置场景
namespace SETTING_SCENE {
    inline const std::string NAME = "setting";                          // 场景名
    inline const SDL_Point GAME_TYPE_FRAME_POS = { 100, 36 };           // 游戏模式框架位置
    inline const SDL_Point GAME_TYPE_TITLE_POS = { 416, 64 };           // 游戏模式标题位置
    inline const SDL_Point LEVEL_FRAME_POS = { 204, 200 };              // 等级选项框架位置
    inline const std::string LEVEL_TITLE_STR = "LEVEL";                 // 等级选项标题内容
    inline const SDL_Point LEVEL_TITLE_POS = { 288, 224 };              // 等级选项标题位置
    inline const SDL_Point HEIGHT_FRAME_POS = { 616, 200 };             // 高度选项框架位置
    inline const std::string HEIGHT_TITLE_STR = "HEIGHT";               // 高度选项标题内容
    inline const SDL_Point HEIGHT_TITLE_POS = { 640, 224 };             // 高度选项标题位置
    inline const SDL_Point LEVEL_OPTION_POS = { 224, 320 };             // 等级选项位置
    inline const SDL_Point HEIGHT_OPTION_POS = { 640, 320 };            // 高度选项位置
    inline const int OPTION_ROW_NUM = 2;                                // 选项行数
    inline const int OPTION_SPACING = 64;                               // 选项间距
    inline const int OPTION_ICON_OFFSET = -16;                          // 选项图标位置偏移量
    inline const SDL_Color OPTION_COLOR = { 181, 49, 32, 255 };         // 选项文本颜色
    inline const int OPTION_ICON_SIZE = 64;                             // 选项图标尺寸
    inline const SDL_Color OPTION_ICON_COLOR = { 234, 158, 34, 255 };   // 选项图标颜色
    inline const int OPTION_ICON_SHOW_FRAME = 3;                        // 选项图标显示帧数
    inline const int OPTION_ICON_HIDE_FRAME = 1;                        // 选项图标隐藏帧数
    inline const SDL_Point RECORD_ORDER_POS = { 224, 608 };             // 名次位置
    inline const SDL_Point RECORD_POS = { 288, 544 };                   // 排行榜位置
    inline const int RECORD_ROW_SPACING = 64;                           // 排行榜行间距
    inline const int RECORD_COL_SPACING = 224;                          // 排行榜列间距
    inline const std::vector<std::string> RECORD_TITLE_STR = { " NAME", "SCORE", "LV" };   // 排行榜表头内容
};

// 游戏场景
namespace GAME_SCENE {
    inline const std::string NAME = "game";                             // 场景名
    inline const SDL_Point GAME_TYPE_TITLE_POS = { 96, 96 };            // 游戏类型标题位置
    inline const SDL_Point TETRIS_COUNT_POS = { 192, 352 };             // 方块计数区域位置
    inline const SDL_Point TETRIS_MODE_CENTER_POS = { 138, 366 };       // 方块预览位置
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
    inline const SDL_Point NEXT_TETRIS_TITLE_POS = { 768, 384 };        // 下一个方块标题位置
    inline const SDL_Point NEXT_TETRIS_CENTER_POS = { 830, 478 };       // 下一个方块中心位置
    inline const std::string LEVEL_TITLE_STR = "LEVEL";                 // 等级标题文本
    inline const SDL_Point LEVEL_TITLE_POS = { 768, 608 };              // 等级标题位置
    inline const SDL_Point LEVEL_TEXT_POS = { 800, 640 };               // 等级文本位置
    inline const std::string HEIGHT_TITLE_STR = "HEIGHT";               // 高度标题文本
    inline const SDL_Point HEIGHT_TITLE_POS = { 768, 736 };             // 高度标题位置
    inline const SDL_Point HEIGHT_TEXT_POS = { 864, 768 };              // 高度文本位置
    inline const int TETRIS_COUNT_MAX_LEN = 3;                          // 方块计数最大长度
    inline const int LINE_COUNT_MAX_LEN = 3;                            // 消除行数最大长度
    inline const SDL_Point TETRIS_FIELD_POS = { 384, 764 };             // 场地位置
    inline const int TETRIS_SPACING = 32;                               // 方块间距
    inline const int TETRIS_SIZE = 28;                                  // 方块尺寸
    inline const int TETRIS_PREVIEW_SPACING = 24;                       // 方块间距（预览）
    inline const int TETRIS_PREVIEW_SIZE = 20;                          // 方块尺寸（预览）
    inline const SDL_Color TETRIS_BASIC_COLOR = { 255, 255, 255, 255 }; // 方块基底颜色
    inline const std::vector<SDL_Color> TETRIS_PATTERN_DARK_COLOR = {   // 方块花纹颜色 - 深色
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
    inline const std::vector<SDL_Color> TETRIS_PATTERN_LIGHT_COLOR = {  // 方块花纹颜色 - 浅色
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
    inline const SDL_Point RESULT_OUTER_FRAME_POS = { 384, 384 };       // 游戏结束外层框架位置
    inline const SDL_Point RESULT_INNER_FRAME_POS = { 400, 400 };       // 游戏结束里层框架位置
    inline const SDL_Point RESULT_TEXT_POS = { 416, 416 };              // 游戏结束文本位置
    inline const std::string WIN_TEXT_STR = "YOU  WIN";                 // 胜利文本
    inline const std::string LOSE_TEXT_STR = "YOU LOSE";                // 失败文本
    inline const std::string PAUSE_TEXT_STR = "PAUSE";                  // 暂停文本
    inline const SDL_Point PAUSE_TEXT_POS = { 448, 448 };               // 暂停文本位置
    inline const SDL_Color PAUSE_TEXT_COLOR = { 146, 144, 255, 255 };   // 暂停文本颜色
};

// 结算场景
namespace COUNT_SCENE {
    inline const std::string NAME = "count";        // 场景名
    inline const std::vector<std::string> COUNT_TEXT_STR = {                // 结算界面文本
        "CONGRATULATIONS",
        "YOU ARE A",
        "TETRIS MASTER.",
        "PLEASE ENTER YOUR NAME"
    };
    inline const std::vector<SDL_Point> COUNT_TEXT_POS = {                  // 结算界面文本位置
        { 288, 192 }, { 352, 288 }, { 288, 352 }, { 160, 448 }
    };
    inline const SDL_Color COUNT_TITLE_COLOR = { 181, 49, 32, 255 };        // 结算界面首条文本颜色
    inline const SDL_Color RECORD_NAME_ICON_COLOR = { 255, 129, 112, 255 }; // 新纪录图标颜色
    inline const int RECORD_NAME_ICON_SIZE = 32;        // 新纪录图标尺寸
    inline const int RECORD_NAME_ICON_SHOW_FRAME = 3;   // 新纪录图标显示帧数
    inline const int RECORD_NAME_ICON_HIDE_FRAME = 1;   // 新纪录图标隐藏帧数
    inline const std::string RECORD_NAME_OPTIONAL_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,/()\". -";  // 新纪录姓名可用字符集
    inline const int RECORD_NAME_CHANGE_FRAME = 8;      // 新纪录姓名字符改动帧数
};