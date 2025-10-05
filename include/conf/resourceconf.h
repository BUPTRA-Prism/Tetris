#pragma once

#include <string>

/* 资源文件夹路径 */
inline const std::string IMAGE_DIR = "resource/image/";         // 图像资源目录
inline const std::string FONT_DIR = "resource/font/";           // 字体资源目录
inline const std::string MUSIC_DIR = "resource/audio/music/";   // 音乐资源目录
inline const std::string CHUNK_DIR = "resource/audio/chunk/";   // 音效资源目录

/* 图像资源文件 */
inline const std::string COYRIGHT_ICON_IMAGE_PATH = "copyright_icon.png";               // 版权图标
inline const std::string GAME_A_FRAME_IMAGE_PATH = "game_a_frame.png";                  // A模式游戏界面框架
inline const std::string GAME_B_FRAME_IMAGE_PATH = "game_b_frame.png";                  // B模式游戏界面框架
inline const std::string HEIGHT_FRAME_IMAGE_PATH = "height_frame.png";                  // 高度选项框架
inline const std::string LEVEL_A_FRAME_IMAGE_PATH = "level_a_frame.png";                // A模式等级选项框架
inline const std::string LEVEL_B_FRAME_IMAGE_PATH = "level_b_frame.png";                // B模式等级选项框架
inline const std::string MENU_FRAME_IMAGE_PATH = "menu_frame.png";                      // 菜单界面框架
inline const std::string OPTION_ICON_IMAGE_PATH = "option_icon.png";                    // 选项图标框架
inline const std::string RESULT_OUTER_FRAME_IMAGE_PATH = "result_outer_frame.png";      // 游戏结束外层框架
inline const std::string RESULT_INNER_FRAME_IMAGE_PATH = "result_inner_frame.png";      // 游戏结束里层框架
inline const std::string SETTING_FRAME_IMAGE_PATH = "setting_frame.png";                // 设置界面框架
inline const std::string TITLE_FRAME_IMAGE_PATH = "title_frame.png";                    // 标题界面框架
inline const std::string TYPE_A_FRAME_IMAGE_PATH = "type_a_frame.png";                  // A模式框架
inline const std::string TYPE_B_FRAME_IMAGE_PATH = "type_b_frame.png";                  // B模式框架
inline const std::string TETRIS_SOLID_PATTERN_IMAGE_PATH = "tetris_solid_pattern.png";              // 方块实心花纹
inline const std::string TETRIS_HOLLOW_PATTERN_IMAGE_PATH = "tetris_hollow_pattern.png";            // 方块空心花纹
inline const std::string TETRIS_MODE_SOLID_PATTERN_IMAGE_PATH = "tetris_mode_solid_pattern.png";    // 方块实心花纹（预览）
inline const std::string TETRIS_MODE_HOLLOW_PATTERN_IMAGE_PATH = "tetris_mode_hollow_pattern.png";  // 方块空心花纹（预览）

/* 字体资源文件 */
inline const std::string DIGIT_FONT_PATH = "digit.png";                 // 数字
inline const std::string LETTER_FONT_PATH = "letter.png";               // 大写字母
inline const std::string PUNCTUATION_FONT_PATH = "punctuation.png";     // 标点符号
inline const std::string PUNCTUATION_LIST = ",/()\". -";                // 支持的标点符号列表

/* 音乐资源文件 */
inline const std::string BGM1_MUSIC_PATH = "bgm1.ogg";      // 游戏背景音乐1
inline const std::string BGM2_MUSIC_PATH = "bgm2.ogg";      // 游戏背景音乐2
inline const std::string BGM3_MUSIC_PATH = "bgm3.ogg";      // 游戏背景音乐3
inline const std::string COUNT_MUSIC_PATH = "count.ogg";    // 结算界面背景音乐
inline const std::string LOSE_MUSIC_PATH = "lose.ogg";      // 游戏失败背景音乐
inline const std::string TITLE_MUSIC_PATH = "title.ogg";    // 标题界面背景音乐
inline const std::string WIN_MUSIC_PATH = "win.ogg";        // 游戏胜利背景音乐

/* 音效资源文件 */
inline const std::string DROP_CHUNK_PATH = "drop.ogg";              // 方块下落音效
inline const std::string ERASE_FOUR_CHUNK_PATH = "erase_four.ogg";  // 消除4行音效
inline const std::string ERASE_CHUNK_PATH = "erase.ogg";            // 消除音效（非4行）
inline const std::string UPGRADE_CHUNK_PATH = "upgrade.ogg";        // 下一关音效
inline const std::string MOVE_CHUNK_PATH = "move.ogg";              // 方块移动音效
inline const std::string OPTION_CHUNK_PATH = "option.ogg";          // 选项切换音效
inline const std::string ROTATE_CHUNK_PATH = "rotate.ogg";          // 方块旋转音效
inline const std::string SCENE_CHUNK_PATH = "scene.ogg";            // 场景切换音效