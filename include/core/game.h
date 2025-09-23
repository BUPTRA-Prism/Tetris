#pragma once

#include "conf/gameconf.h"
#include <array>
#include <vector>

class Game {
private: 
    std::array<std::array<TetrisStyle, TETRIS_FIELD_WIDTH>, TETRIS_FIELD_HEIGHT> m_field;
    int m_level;
    int m_height;
    int m_score;
    int m_lines;
    std::unordered_map<TetrisMode, int> m_count;

    TetrisMode m_curMode;
    TetrisMode m_nextMode;

public:
    Game();
    ~Game() = default;

    TetrisStyle getFieldStyle(int row, int col) const;
    int getLevel() const;
    int getHeight() const;
    int getScore() const;
    int getLines() const;
    const std::unordered_map<TetrisMode, int>& getCount();

    void resetGame(int level, int height);

    void move(int delta);
    void rotate(int delta);

    void generate();
    int erase();
    int calculate();
    bool win();
    bool lose();
};