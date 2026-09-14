/**
 * @file resource.h
 * @brief 资源路径配置，定义音频、字体与图片资源的路径常量
 */
#pragma once

#include <string_view>

namespace Resource {
    /**
     * @brief 音频资源路径常量
     */
    namespace Audio {
        /** @brief 音乐资源目录 */
        constexpr std::string_view MUSIC_FOLDER = "resource/audio/music/";

        /** @brief 标题音乐文件名 */
        constexpr std::string_view TITLE_MUSIC = "title.ogg";
        /** @brief 背景音乐 1 文件名 */
        constexpr std::string_view BGM_1 = "bgm_1.ogg";
        /** @brief 背景音乐 2 文件名 */
        constexpr std::string_view BGM_2 = "bgm_2.ogg";
        /** @brief 背景音乐 3 文件名 */
        constexpr std::string_view BGM_3 = "bgm_3.ogg";
        /** @brief 胜利音乐文件名 */
        constexpr std::string_view WIN_MUSIC = "win.ogg";
        /** @brief 失败音乐文件名 */
        constexpr std::string_view LOSE_MUSIC = "lose.ogg";
        /** @brief 排行榜音乐文件名 */
        constexpr std::string_view RANK_MUSIC = "rank.ogg";

        /** @brief 音效资源目录 */
        constexpr std::string_view CHUNK_FOLDER = "resource/audio/chunk/";

        /** @brief 场景切换音效文件名 */
        constexpr std::string_view LOAD_SCENE_CHUNK = "load_scene.ogg";
        /** @brief 选项移动音效文件名 */
        constexpr std::string_view OPTION_CHUNK = "option.ogg";
        /** @brief 暂停音效文件名 */
        constexpr std::string_view PAUSE_CHUNK = "pause.ogg";
        /** @brief 水平移动音效文件名 */
        constexpr std::string_view MOVE_CHUNK = "move.ogg";
        /** @brief 旋转音效文件名 */
        constexpr std::string_view ROTATE_CHUNK = "rotate.ogg";
        /** @brief 方块落地音效文件名 */
        constexpr std::string_view LAND_CHUNK = "land.ogg";
        /** @brief 消行音效文件名 */
        constexpr std::string_view ERASE_CHUNK = "erase.ogg";
        /** @brief 四行消除（Tetris）音效文件名 */
        constexpr std::string_view ERASE_FOUR_CHUNK = "erase_four.ogg";
        /** @brief 升级音效文件名 */
        constexpr std::string_view LEVEL_UP_CHUNK = "level_up.ogg";
    }

    /**
     * @brief 字体资源路径常量
     */
    namespace Font {
        /** @brief 字体资源目录 */
        constexpr std::string_view FOLDER = "resource/font/";

        /** @brief 默认字体文件名 */
        constexpr std::string_view DEFAULT_FONT = "PressStart2P-Regular.ttf";
        /** @brief 默认字体大小（像素） */
        constexpr int DEFAULT_FONT_SIZE = 32;
    }

    /**
     * @brief 图标资源路径常量
     */
    namespace Icon {
        /** @brief 图标资源目录 */
        constexpr std::string_view ICON_FOLDER = "resource/icon";

        
    }

    /**
     * @brief 图片资源路径常量
     */
    namespace Image {
        /** @brief 图片资源目录 */
        constexpr std::string_view FOLDER = "resource/image/";

        /** @brief 图标文件名 */
        constexpr std::string_view ICON_IMG = "icon.ico";
        /** @brief 标题页图片文件名 */
        constexpr std::string_view TITLE_IMG = "title.png";
        /** @brief 版权信息图片文件名 */
        constexpr std::string_view COPYRIGHT_IMG = "copyright.png";
        /** @brief 菜单背景图片文件名 */
        constexpr std::string_view MENU_IMG = "menu.png";
        /** @brief 菜单选项图标图片文件名 */
        constexpr std::string_view MENU_OPTION_ICON_IMG = "menu_option_icon.png";
        /** @brief 设置页背景图片文件名 */
        constexpr std::string_view SETTING_IMG = "setting.png";
        /** @brief A 类型面板图片文件名 */
        constexpr std::string_view GAME_TYPE_A_PANEL_IMG = "game_type_a_panel.png";
        /** @brief B 类型面板图片文件名 */
        constexpr std::string_view GAME_TYPE_B_PANEL_IMG = "game_type_b_panel.png";
        /** @brief A 类型等级面板图片文件名 */
        constexpr std::string_view LEVEL_A_PANEL_IMG = "level_a_panel.png";
        /** @brief B 类型等级面板图片文件名 */
        constexpr std::string_view LEVEL_B_PANEL_IMG = "level_b_panel.png";
        /** @brief 高度面板图片文件名 */
        constexpr std::string_view HEIGHT_PANEL_IMG = "height_panel.png";
        /** @brief 设置选项图标图片文件名 */
        constexpr std::string_view SETTING_OPTION_ICON_IMG = "setting_option_icon.png";
        /** @brief 排行榜面板图片文件名 */
        constexpr std::string_view LEADER_BOARD_PANEL_IMG = "leader_board_panel.png";
        /** @brief A 类型游戏背景图片文件名 */
        constexpr std::string_view GAME_A_IMG = "game_a.png";
        /** @brief B 类型游戏背景图片文件名 */
        constexpr std::string_view GAME_B_IMG = "game_b.png";
        /** @brief 方块底色图片文件名 */
        constexpr std::string_view BLOCK_BASE_IMG = "block_base.png";
        /** @brief 方块实心纹样图片文件名 */
        constexpr std::string_view BLOCK_SOLID_PATTERN_IMG = "solid_pattern.png";
        /** @brief 方块空心纹样图片文件名 */
        constexpr std::string_view BLOCK_HOLLOW_PATTERN_IMG = "hollow_pattern.png";
        /** @brief 方块图标底色图片文件名 */
        constexpr std::string_view BLOCK_ICON_BASE_IMG = "block_icon_base.png";
        /** @brief 方块图标实心纹样图片文件名 */
        constexpr std::string_view BLOCK_ICON_SOLID_PATTERN_IMG = "icon_solid_pattern.png";
        /** @brief 方块图标空心纹样图片文件名 */
        constexpr std::string_view BLOCK_ICON_HOLLOW_PATTERN_IMG = "icon_hollow_pattern.png";
        /** @brief 结束外层面板图片文件名 */
        constexpr std::string_view FINISH_OUTER_PANEL_IMG = "finish_outer_panel.png";
        /** @brief 结束内层面板图片文件名 */
        constexpr std::string_view FINISH_INNER_PANEL_IMG = "finish_inner_panel.png";
        /** @brief 排行榜选项图标图片文件名 */
        constexpr std::string_view RANK_OPTION_ICON_IMG = "rank_option_icon.png";
    }
}