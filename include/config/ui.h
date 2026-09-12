/**
 * @file ui.h
 * @brief 各场景的 UI 布局与配色配置
 */
#pragma once

#include <array>
#include <string_view>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>

namespace Config {
    /**
     * @brief 多个场景共用的 UI 常量
     */
    namespace UICommon {
        /** @brief 选项图标隐藏动画帧数 */
        constexpr int OPTION_ICON_HIDE_TOTAL_FRAME = 2;
        /** @brief 选项图标显示动画帧数 */
        constexpr int OPTION_ICON_SHOW_TOTAL_FRAME = 2;

        /** @brief "A-TYPE" 文本 */
        constexpr std::string_view GAME_TYPE_A_TEXT_STR = "A-TYPE";
        /** @brief "B-TYPE" 文本 */
        constexpr std::string_view GAME_TYPE_B_TEXT_STR = "B-TYPE";
        /** @brief "SCORE" 文本 */
        constexpr std::string_view SCORE_TEXT_STR = "SCORE";
        /** @brief "LEVEL" 文本 */
        constexpr std::string_view LEVEL_TEXT_STR = "LEVEL";
        /** @brief "HEIGHT" 文本 */
        constexpr std::string_view HEIGHT_TEXT_STR = "HEIGHT";

        /** @brief 排行榜名字列标题文本 */
        constexpr std::string_view LEADER_BOARD_COLUMN_NAME_TEXT_STR = " NAME ";
        /** @brief 排行榜等级列标题文本 */
        constexpr std::string_view LEADER_BOARD_COLUMN_LEVEL_TEXT_STR = "LV";
        /** @brief 排行榜序号列宽度 */
        constexpr int LEADER_BOARD_ORDER_COLUMN_WIDTH = 64;
        /** @brief 排行榜名字列宽度 */
        constexpr int LEADER_BOARD_NAME_COLUMN_WIDTH = 224;
        /** @brief 排行榜分数列宽度 */
        constexpr int LEADER_BOARD_SCORE_COLUMN_WIDTH = 224;
        /** @brief 排行榜条目行高 */
        constexpr int LEADER_BOARD_ENTRY_HEIGHT = 64;

        /** @brief 分数显示位数 */
        constexpr int SCORE_NUM_DIGITS = 6;
        /** @brief 等级显示位数 */
        constexpr int LEVEL_NUM_DIGITS = 2;
        /** @brief 计数显示位数 */
        constexpr int COUNT_NUM_DIGITS = 3;
    }

    /**
     * @brief 标题场景 UI 布局配置
     */
    namespace TitleSceneUI {
        /** @brief 场景名（与 SceneManager 注册名一致） */
        constexpr std::string_view NAME = "title";

        /** @brief 版权图片绘制位置 */
        constexpr SDL_Point COPYRIGHT_IMG_POS = { 288, 768 };
        /** @brief 版权图片着色 */
        constexpr SDL_Color COPYRIGHT_IMG_COLOR = { 243, 190, 60, 255 };
        /** @brief "PUSH START" 文本 */
        constexpr std::string_view START_TEXT_STR = "PUSH START";
        /** @brief 开始提示文本绘制位置 */
        constexpr SDL_Point START_TEXT_POS = { 224, 608 };
        /** @brief 年份文本内容 */
        constexpr std::string_view YEAR_TEXT_STR = "1989";
        /** @brief 年份文本绘制位置 */
        constexpr SDL_Point YEAR_TEXT_POS = { 352, 768 };
    }

    /**
     * @brief 菜单场景 UI 布局配置
     */
    namespace MenuSceneUI {
        /** @brief 场景名 */
        constexpr std::string_view NAME = "menu";

        /** @brief "GAME  TYPE" 文本 */
        constexpr std::string_view GAME_TYPE_TEXT_STR = "GAME  TYPE";
        /** @brief 游戏类型标题绘制位置 */
        constexpr SDL_Point GAME_TYPE_TEXT_POS = { 160, 96 };
        /** @brief 游戏类型选项起始位置 */
        constexpr SDL_Point GAME_TYPE_OPTION_POS = { 288, 224 };
        /** @brief 游戏类型选项水平间距 */
        constexpr int GAME_TYPE_OPTION_SPACING_X = 384;
        /** @brief 游戏类型选项图标相对选项的 X 偏移 */
        constexpr int GAME_TYPE_OPTION_ICON_OFFSET_X = -36;
        /** @brief 游戏类型选项翻转图标相对选项的 X 偏移 */
        constexpr int GAME_TYPE_OPTION_FLIP_ICON_OFFSET_X = 200;
        /** @brief "MUSIC TYPE" 文本 */
        constexpr std::string_view MUSIC_TYPE_TEXT_STR = "MUSIC TYPE";
        /** @brief 音乐类型标题绘制位置 */
        constexpr SDL_Point MUSIC_TYPE_TEXT_POS = { 160, 384 };
        /** @brief "MUSIC  1" 文本 */
        constexpr std::string_view MUSIC_1_TEXT_STR = "MUSIC  1";
        /** @brief "MUSIC  2" 文本 */
        constexpr std::string_view MUSIC_2_TEXT_STR = "MUSIC  2";
        /** @brief "MUSIC  3" 文本 */
        constexpr std::string_view MUSIC_3_TEXT_STR = "MUSIC  3";
        /** @brief "  OFF" 文本 */
        constexpr std::string_view MUSIC_OFF_TEXT_STR = "  OFF";
        /** @brief 音乐选项起始位置 */
        constexpr SDL_Point MUSIC_OPTION_POS = { 448, 544 };
        /** @brief 音乐选项垂直间距 */
        constexpr int MUSIC_OPTION_SPACING_Y = 64;
        /** @brief 音乐选项图标相对选项的 X 偏移 */
        constexpr int MUSIC_OPTION_ICON_OFFSET_X = -36;
        /** @brief 音乐选项翻转图标相对选项的 X 偏移 */
        constexpr int MUSIC_OPTION_FLIP_ICON_OFFSET_X = 264;
    }

    /**
     * @brief 设置场景 UI 布局配置
     */
    namespace SettingSceneUI {
        /** @brief 场景名 */
        constexpr std::string_view NAME = "setting";

        /** @brief 游戏类型面板绘制位置 */
        constexpr SDL_Point GAME_TYPE_PANEL_POS = { 100, 36 };
        /** @brief 游戏类型文本绘制位置 */
        constexpr SDL_Point GAME_TYPE_TEXT_POS = { 416, 64 };
        /** @brief 选项行数 */
        constexpr int OPTION_ROW = 2;
        /** @brief 选项文本颜色 */
        constexpr SDL_Color OPTION_COLOR = { 219, 40, 0, 255 };
        /** @brief 选项间水平/垂直间距 */
        constexpr int OPTION_SPACING = 64;
        /** @brief 选项图标相对选项的偏移 */
        constexpr int OPTION_ICON_OFFSET = -16;
        /** @brief 等级面板绘制位置 */
        constexpr SDL_Point LEVEL_PANEL_POS = { 204, 200 };
        /** @brief "LEVEL" 文本绘制位置 */
        constexpr SDL_Point LEVEL_TEXT_POS = { 288, 224 };
        /** @brief 等级选项起始位置 */
        constexpr SDL_Point LEVEL_OPTION_POS = { 224, 320 };
        /** @brief 高度面板绘制位置 */
        constexpr SDL_Point HEIGHT_PANEL_POS = { 616, 200 };
        /** @brief "HEIGHT" 文本绘制位置 */
        constexpr SDL_Point HEIGHT_TEXT_POS = { 640, 224 };
        /** @brief 高度选项起始位置 */
        constexpr SDL_Point HEIGHT_OPTION_POS = { 640, 320 };
        /** @brief 排行榜面板绘制位置 */
        constexpr SDL_Point LEADER_BOARD_PANEL_POS = { 172, 520 };
        /** @brief 排行榜内容绘制位置 */
        constexpr SDL_Point LEADER_BOARD_POS = { 224, 544 };
    }

    /**
     * @brief 游戏场景 UI 布局、配色与方块类型配置
     */
    namespace GameSceneUI {
        /** @brief 场景名 */
        constexpr std::string_view NAME = "game";

        /**
         * @brief 方块小格显示类型
         */
        enum class BlockType {
            DarkSolid, ///< 深色实心
            DarkHollow, ///< 深色空心
            LightSolid, ///< 浅色实心
            Blank       ///< 空白
        };

        /**
         * @brief 某一等级对应的深/浅两级配色
         */
        struct LevelColor {
            SDL_Color dark;  ///< 深色
            SDL_Color light; ///< 浅色
        };

        /** @brief "PAUSE" 文本 */
        constexpr std::string_view PAUSE_TEXT_STR = "PAUSE";
        /** @brief 暂停文本绘制位置 */
        constexpr SDL_Point PAUSE_TEXT_POS = { 448, 448 };
        /** @brief 暂停文本颜色 */
        constexpr SDL_Color PAUSE_TEXT_COLOR = { 94, 150, 255, 255 };
        /** @brief 游戏类型文本绘制位置 */
        constexpr SDL_Point GAME_TYPE_TEXT_POS = { 96, 96 };
        /** @brief T 形方块图标位置 */
        constexpr SDL_Point TETROMINO_T_ICON_POS = { 104, 340 };
        /** @brief J 形方块图标位置 */
        constexpr SDL_Point TETROMINO_J_ICON_POS = { 104, 400 };
        /** @brief Z 形方块图标位置 */
        constexpr SDL_Point TETROMINO_Z_ICON_POS = { 104, 468 };
        /** @brief O 形方块图标位置 */
        constexpr SDL_Point TETROMINO_O_ICON_POS = { 116, 532 };
        /** @brief S 形方块图标位置 */
        constexpr SDL_Point TETROMINO_S_ICON_POS = { 104, 596 };
        /** @brief L 形方块图标位置 */
        constexpr SDL_Point TETROMINO_L_ICON_POS = { 104, 656 };
        /** @brief I 形方块图标位置 */
        constexpr SDL_Point TETROMINO_I_ICON_POS = { 120, 736 };
        /** @brief 各方块使用计数文本起始位置 */
        constexpr SDL_Point TETROMINO_COUNT_POS = { 192, 352 };
        /** @brief 方块图标小格间距 */
        constexpr int BLOCK_ICON_SPACING = 24;
        /** @brief 各方块计数文本垂直间距 */
        constexpr int TETROMINO_COUNT_SPACING_Y = 64;
        /** @brief 方块计数文本颜色 */
        constexpr SDL_Color TETROMINO_COUNT_COLOR = { 219, 40, 0, 255 };

        /** @brief "LINES-" 文本 */
        constexpr std::string_view LINES_TEXT_STR = "LINES-";
        /** @brief 行数文本绘制位置 */
        constexpr SDL_Point LINES_TEXT_POS = { 416, 64 };
        /** @brief 行数数字绘制位置 */
        constexpr SDL_Point LINES_NUM_POS = { 608, 64 };
        /** @brief "TOP" 文本 */
        constexpr std::string_view HISCORE_TEXT_STR = "TOP";
        /** @brief 最高分文本绘制位置 */
        constexpr SDL_Point HISCORE_TEXT_POS = { 768, 96 };
        /** @brief 最高分数字绘制位置 */
        constexpr SDL_Point HISCORE_NUM_POS = { 768, 128 };
        /** @brief 分数文本绘制位置 */
        constexpr SDL_Point SCORE_TEXT_POS = { 768, 192 };
        /** @brief 分数数字绘制位置 */
        constexpr SDL_Point SCORE_NUM_POS = { 768, 224 };
        /** @brief "NEXT" 文本 */
        constexpr std::string_view NEXT_TETROMINO_TEXT_STR = "NEXT";
        /** @brief 下一个方块文本绘制位置 */
        constexpr SDL_Point NEXT_TETROMINO_TEXT_POS = { 768, 384 };
        /** @brief 下一个方块默认预览位置 */
        constexpr SDL_Point NEXT_TETROMINO_DEFAULT_POS = { 784, 448 };
        /** @brief 下一个 I 形方块预览位置 */
        constexpr SDL_Point NEXT_TETROMINO_I_POS = { 800, 464 };
        /** @brief 下一个 O 形方块预览位置 */
        constexpr SDL_Point NEXT_TETROMINO_O_POS = { 800, 448 };
        /** @brief 等级文本绘制位置 */
        constexpr SDL_Point LEVEL_TEXT_POS = { 768, 608 };
        /** @brief 等级数字绘制位置 */
        constexpr SDL_Point LEVEL_NUM_POS = { 832, 640 };
        /** @brief 高度文本绘制位置 */
        constexpr SDL_Point HEIGHT_TEXT_POS = { 768, 736 };
        /** @brief 高度数字绘制位置 */
        constexpr SDL_Point HEIGHT_NUM_POS = { 864, 768 };
        /** @brief 游戏区原点位置（左下角） */
        constexpr SDL_Point FIELD_POS = { 384, 768 };
        /** @brief 游戏区小格间距 */
        constexpr int BLOCK_SPACING = 32;
        /** @brief 等级配色表长度 */
        constexpr int LEVEL_COLOR_SIZE = 7;
        /** @brief 各等级对应的配色（按等级取模循环使用） */
        constexpr std::array<LevelColor, LEVEL_COLOR_SIZE> LEVEL_COLOR = {
            LevelColor{ SDL_Color{ 0, 0, 255, 255 }, SDL_Color{ 0, 180, 255, 255 } },
            LevelColor{ SDL_Color{ 0, 180, 0, 255 }, SDL_Color{ 200, 255, 130, 255 } },
            LevelColor{ SDL_Color{ 230, 0, 230, 255 }, SDL_Color{ 255, 180, 255, 255 } },
            LevelColor{ SDL_Color{ 255, 160, 0, 255 }, SDL_Color{ 255, 210, 150, 255 } },
            LevelColor{ SDL_Color{ 255, 0, 0, 255 }, SDL_Color{ 255, 120, 120, 255 } },
            LevelColor{ SDL_Color{ 125, 0, 200, 255 }, SDL_Color{ 200, 100, 255, 255 } },
            LevelColor{ SDL_Color{ 110, 50, 20, 255 }, SDL_Color{ 185, 120, 80, 255 } }
        };

        /**
         * @brief 获取指定等级的配色
         * @param level 等级
         * @return 对应配色，负等级返回全黑
         */
        constexpr LevelColor GetLevelColor(int level) {
            if (level < 0) {
                return LevelColor{ SDL_Color{ 0, 0, 0, 255 }, SDL_Color{ 0, 0, 0, 255 } };
            }
            return LEVEL_COLOR[level % LEVEL_COLOR_SIZE];
        }
        /** @brief 结束外层面板绘制位置 */
        constexpr SDL_Point FINISH_OUTER_PANEL_POS = { 384, 384 };
        /** @brief 结束内层面板绘制位置 */
        constexpr SDL_Point FINISH_INNER_PANEL_POS = { 400, 400 };
        /** @brief 胜利结束文本 */
        constexpr std::string_view FINISH_TEXT_WIN_STR = "SUCCESS!";
        /** @brief 失败结束文本 */
        constexpr std::string_view FINISH_TEXT_LOSE_STR = "GAMEOVER";
        /** @brief 结束文本绘制位置 */
        constexpr SDL_Point FINISH_TEXT_POS = { 416, 416 };
    }

    /**
     * @brief 排行榜场景 UI 布局配置
     */
    namespace RankSceneUI {
        /** @brief 场景名 */
        constexpr std::string_view NAME = "rank";

        /** @brief 游戏类型面板绘制位置 */
        constexpr SDL_Point GAME_TYPE_PANEL_POS = { 100, 36 };
        /** @brief 游戏类型文本绘制位置 */
        constexpr SDL_Point GAME_TYPE_TEXT_POS = { 416, 64 };
        /** @brief "CONGRATULATIONS" 文本 */
        constexpr std::string_view CONGRATULATION_TEXT_STR = "CONGRATULATIONS";
        /** @brief 祝贺文本绘制位置 */
        constexpr SDL_Point CONGRATULATION_TEXT_POS = { 288, 192 };
        /** @brief 祝贺文本颜色 */
        constexpr SDL_Color CONGRATULATION_TEXT_COLOR = { 219, 40, 0, 255 };
        /** @brief 称赞文本第一行 */
        constexpr std::string_view PRAISE_TEXT_1_STR = "YOU ARE A";
        /** @brief 称赞文本第一行绘制位置 */
        constexpr SDL_Point PRAISE_TEXT_1_POS = { 352, 288 };
        /** @brief 称赞文本第二行 */
        constexpr std::string_view PRAISE_TEXT_2_STR = "TETRIS MASTER.";
        /** @brief 称赞文本第二行绘制位置 */
        constexpr SDL_Point PRAISE_TEXT_2_POS = { 288, 352 };
        /** @brief 输入姓名提示文本 */
        constexpr std::string_view ENTER_NAME_TEXT_STR = "PLEASE ENTER YOUR NAME";
        /** @brief 输入姓名提示文本绘制位置 */
        constexpr SDL_Point ENTER_NAME_TEXT_POS = { 160, 448 };
        /** @brief 排行榜面板绘制位置 */
        constexpr SDL_Point LEADER_BOARD_PANEL_POS = { 172, 520 };
        /** @brief 排行榜内容绘制位置 */
        constexpr SDL_Point LEADER_BOARD_POS = { 224, 544 };
    }
}