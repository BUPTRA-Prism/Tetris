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
    int m_lineCount;
    std::unordered_map<TetrisMode, int> m_tetrisCount;

    TetrisMode m_curMode;
    TetrisMode m_nextMode;

    std::array<std::pair<int, int>, TETRIS_NUM> m_tetrisPos;
    int m_tetrisRotateStatus;

public:
    Game();
    ~Game() = default;

    TetrisStyle getFieldStyle(int row, int col) const;
    int getLevel() const;
    int getHeight() const;
    int getScore() const;
    int getLineCount() const;
    const std::unordered_map<TetrisMode, int>& getTetrisCount();

    void resetGame(int level, int height);

    bool generate();
    bool move(int delta);
    bool rotate(int delta);
    bool drop();

    std::vector<int> checkEraseLine();
    void erase(std::vector<int>& lines, int order);
    int calculate(int eraseLine, int accelerateLine);
    bool win();
};