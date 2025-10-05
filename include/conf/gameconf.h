#pragma once

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

// 方块样式
enum class TetrisStyle {
    Blank,          // 空
    SolidDark,      // 深色实心花纹
    SolidLight,     // 深度空心花纹
    HollowDark      // 浅色实心花纹
};
// 方块类型
enum class TetrisMode { T, J, Z, O, S, L, I };

inline const int TETRIS_NUM = 4;    // 每组方块数量
// 方块旋转详情
inline const std::unordered_map<TetrisMode, 
    std::vector<std::array<std::pair<int, int>, TETRIS_NUM>>> TETRIS_MODE_ROTATE = {
    // T形方块
    {
        TetrisMode::T, {
            { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { -1, 1 } } },
            { { { 1, 1 }, { 0, 1 }, { -1, 1 }, { 0, 0 } } },
            { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 1 } } },
            { { { 1, 1 }, { 0, 1 }, { -1, 1 }, { 0, 2 } } }
        }
    },
    // J形方块
    {
        TetrisMode::J, {
            { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { -1, 2 } } },
            { { { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 0 } } },
            { { { 0, 2 }, { 0, 1 }, { 0, 0 }, { 1, 0 } } },
            { { { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 2 } } }
        }
    },
    // Z形方块
    {
        TetrisMode::Z, {
            { { { 0, 0 }, { 0, 1 }, { -1, 1 }, { -1, 2 } } },
            { { { 1, 2 }, { 0, 2 }, { 0, 1 }, { -1, 1 } } }
        }
    },
    // O形方块
    {
        TetrisMode::O, {
            { { { 0, 0 }, { 0, 1 }, { -1, 0 }, { -1, 1 } } },
        }
    },
    // S形方块
    {
        TetrisMode::S, {
            { { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 0, 2 } } },
            { { { 1, 1 }, { 0, 1 }, { 0, 2 }, { -1, 2 } } }
        }
    },
    // L形方块
    {
        TetrisMode::L, {
            { { { 0, 2 }, { 0, 1 }, { 0, 0 }, { -1, 0 } } },
            { { { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 } } },
            { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 } } },
            { { { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 2 } } }
        }
    },
    // I形方块
    {
        TetrisMode::I, {
            { { { 0, -1 }, { 0, 0 }, { 0, 1 }, { 0, 2 } } },
            { { { -1, 1 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }
        }
    }
};
// 方块类型对应样式
inline const std::unordered_map<TetrisMode, TetrisStyle> TETRIS_MODE_STYLE = {
    { TetrisMode::T, TetrisStyle::HollowDark },
    { TetrisMode::J, TetrisStyle::SolidDark },
    { TetrisMode::Z, TetrisStyle::SolidLight },
    { TetrisMode::O, TetrisStyle::HollowDark },
    { TetrisMode::S, TetrisStyle::SolidDark },
    { TetrisMode::L, TetrisStyle::SolidLight },
    { TetrisMode::I, TetrisStyle::HollowDark },
};

inline const int TETRIS_FIELD_WIDTH = 10;       // 场地宽度
inline const int TETRIS_FIELD_HEIGHT = 20;      // 场地高度
inline const int TETRIS_RESERVE_HEIGHT = 2;     // 场地预留高度（用于旋转过顶）
inline const int TETRIS_DAS_FRAME = 16;         // DAS - 16帧
inline const int TETRIS_ARR_FRAME = 6;          // ARR - 6帧
inline const int TETRIS_ACCELERATE_FRAME = 2;   // 加速下落一行所耗帧数
inline const int TETRIS_ERASE_FRAME = 4;        // 行消除时单方块所耗帧数
// 重力（自然降落一行所耗帧数）
inline const std::vector<int> TETRIS_GRAVITY_FRAME = {
    48, 43, 38, 33, 28, 23, 18, 13, 8, 6,
    5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 
    2, 2, 2, 2, 2, 2, 2, 2, 2, 1
};
inline const std::pair<int, int> TETRIS_INIT_POS = { 19, 4 };                   // 方块生成初始位置
inline const std::vector<int> TETRIS_ERASE_SCORE = { 0, 40, 100, 300, 1200 };   // 消除行数对应分数
inline const std::vector<int> TETRIS_HEIGHT_LINE = { 0, 3, 5, 8, 10, 12 };      // B模式高度对应垃圾行数
inline const int TYPE_B_TARGET_LINE_COUNT = 25;     // B模式消除目标总行数
inline const int TYPE_B_GARBAGE_MIN_COUNT = 3;      // B模式单垃圾行最少方块数
inline const int TYPE_B_GARBAGE_MAX_COUNT = 6;      // B模式单垃圾行最多方块数