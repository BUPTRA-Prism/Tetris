#pragma once

#include <array>

class Score {
private:
    std::array<int, 2> m_playerScore;
    std::array<int, 2> m_playerLines;
    std::array<int, 2> m_playerLevel;

public:
    Score();
    ~Score() = default;

    int getPlayerScore(int idx) const;
    int getPlayerLines(int idx) const;
    int getPlayerLevel(int idx) const;
    int getHiScore() const;

    void addPlayerScore(int idx, int score);
    void addPlayerLines(int idx, int lines);
    void addPlayerLevel(int idx);
};