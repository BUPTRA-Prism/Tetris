#pragma once

#include "conf/gameconf.h"
#include <array>
#include <vector>

class Game {
private: 
    std::array<std::array<TetrisStyle, TETRIS_FIELD_WIDTH>, TETRIS_FIELD_HEIGHT + TETRIS_RESERVE_HEIGHT> m_field;
    int m_level;
    int m_height;
    int m_score;
    int m_lineCount;
    std::unordered_map<TetrisMode, int> m_tetrisCount;

    TetrisMode m_curMode;
    TetrisMode m_nextMode;

    std::array<std::pair<int, int>, TETRIS_NUM> m_tetrisPos;
    int m_tetrisRotateStatus;

    std::vector<int> m_eraseLines;
    int m_levelLineCount;

    bool m_upgrade;

public:
    Game();
    ~Game() = default;

    int getLevel() const;
    int getHeight() const;
    int getScore() const;
    int getLineCount() const;
    TetrisMode getCurMode() const;
    bool isUpgrade() const;
    int getTetrisCount(TetrisMode mode) const;
    TetrisStyle getFieldStyle(int row, int col) const;

    void resetGame(int level, int height);

    bool generate();
    bool move(int delta);
    bool rotate(int delta);
    bool drop();

    int checkEraseLine();
    bool eraseComplete(int order);
    void calculate(int accelerateLineCount);
    bool win();
};