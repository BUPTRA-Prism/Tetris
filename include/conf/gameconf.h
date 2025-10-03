#pragma once

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

enum class TetrisStyle {
    Blank,
    SolidDark,
    SolidLight,
    HollowDark
};

enum class TetrisMode { T, J, Z, O, S, L, I };

inline const int TETRIS_NUM = 4;

inline const std::unordered_map<TetrisMode, 
    std::vector<std::array<std::pair<int, int>, TETRIS_NUM>>> TETRIS_MODE_ROTATE = {
    {
        TetrisMode::T, {
            { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { -1, 1 } } },
            { { { 1, 1 }, { 0, 1 }, { -1, 1 }, { 0, 0 } } },
            { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 1 } } },
            { { { 1, 1 }, { 0, 1 }, { -1, 1 }, { 0, 2 } } }
        }
    },
    {
        TetrisMode::J, {
            { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { -1, 2 } } },
            { { { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 0 } } },
            { { { 0, 2 }, { 0, 1 }, { 0, 0 }, { 1, 0 } } },
            { { { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 2 } } }
        }
    },
    {
        TetrisMode::Z, {
            { { { 0, 0 }, { 0, 1 }, { -1, 1 }, { -1, 2 } } },
            { { { 1, 2 }, { 0, 2 }, { 0, 1 }, { -1, 1 } } }
        }
    },
    {
        TetrisMode::O, {
            { { { 0, 0 }, { 0, 1 }, { -1, 0 }, { -1, 1 } } },
        }
    },
    {
        TetrisMode::S, {
            { { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 0, 2 } } },
            { { { 1, 1 }, { 0, 1 }, { 0, 2 }, { -1, 2 } } }
        }
    },
    {
        TetrisMode::L, {
            { { { 0, 2 }, { 0, 1 }, { 0, 0 }, { -1, 0 } } },
            { { { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 } } },
            { { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 } } },
            { { { 1, 1 }, { 0, 1 }, { -1, 1 }, { -1, 2 } } }
        }
    },
    {
        TetrisMode::I, {
            { { { 0, -1 }, { 0, 0 }, { 0, 1 }, { 0, 2 } } },
            { { { -1, 1 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } }
        }
    }
};

inline const std::unordered_map<TetrisMode, TetrisStyle> TETRIS_MODE_STYLE = {
    { TetrisMode::T, TetrisStyle::HollowDark },
    { TetrisMode::J, TetrisStyle::SolidDark },
    { TetrisMode::Z, TetrisStyle::SolidLight },
    { TetrisMode::O, TetrisStyle::HollowDark },
    { TetrisMode::S, TetrisStyle::SolidDark },
    { TetrisMode::L, TetrisStyle::SolidLight },
    { TetrisMode::I, TetrisStyle::HollowDark },
};

inline const int TETRIS_FIELD_WIDTH = 10;
inline const int TETRIS_FIELD_HEIGHT = 20;
inline const int TETRIS_RESERVE_HEIGHT = 2;
inline const int TETRIS_DAS_FRAME = 16;
inline const int TETRIS_ARR_FRAME = 6;
inline const int TETRIS_ACCELERATE_FRAME = 2;
inline const int TETRIS_ERASE_FRAME = 4;
inline const std::vector<int> TETRIS_GRAVITY_FRAME = {
    48, 43, 38, 33, 28, 23, 18, 13, 8, 6,
    5, 5, 5, 4, 4, 4, 3, 3, 3, 2, 
    2, 2, 2, 2, 2, 2, 2, 2, 2, 1
};
inline const std::vector<int> TETRIS_HEIGHT_LINE = { 0, 3, 5, 8, 10, 12 };

inline const std::pair<int, int> TETRIS_INIT_POS = { 19, 4 };

inline const std::vector<int> TETRIS_ERASE_SCORE = { 0, 40, 100, 300, 1200 };

inline const int TYPE_B_TARGET_LINE_COUNT = 25;

inline const int TYPE_B_GARBAGE_MIN_COUNT = 3;

inline const int TYPE_B_GARBAGE_MAX_COUNT = 6;