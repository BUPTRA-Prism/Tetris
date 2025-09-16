#pragma once

#include <string>

enum TetrisStyle {
    SolidDark,
    SolidLight,
    HollowDark
};

inline const std::string TETRIS_MODE = "TJZOSLI";
inline const int TETRIS_FIELD_WIDTH = 10;
inline const int TETRIS_FIELD_HEIGHT = 20;