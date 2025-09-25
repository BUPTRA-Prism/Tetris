#include "core/game.h"
#include "util/util.h"

Game::Game() {
    m_count.emplace(TetrisMode::T, 0);
    m_count.emplace(TetrisMode::J, 0);
    m_count.emplace(TetrisMode::Z, 0);
    m_count.emplace(TetrisMode::O, 0);
    m_count.emplace(TetrisMode::S, 0);
    m_count.emplace(TetrisMode::L, 0);
    m_count.emplace(TetrisMode::I, 0);
}

TetrisStyle Game::getFieldStyle(int row, int col) const { 
    if (row < 0 || row >= m_field.size() || col < 0 || col >= m_field[0].size() ) {
        return TetrisStyle::Blank;
    }
    return m_field[row][col];
}

int Game::getLevel() const { return m_level; }

int Game::getHeight() const { return m_height; }

int Game::getScore() const { return m_score; }

int Game::getLines() const { return m_lines; }

const std::unordered_map<TetrisMode, int>& Game::getCount() { return m_count; }

void Game::resetGame(int level, int height) {
    for (int row = 0; row < m_field.size(); ++row) {
        m_field[row].fill(TetrisStyle::Blank);
    }
    m_level = level;
    m_height = height;
    m_score = 0;
    m_lines = 0;

    for (auto it = m_count.begin(); it != m_count.end(); ++it) {
        it->second = 0;
    }

    m_nextMode = static_cast<TetrisMode>(getRandomInt(0, m_count.size() - 1));
}

bool Game::generate() {
    bool success = true;

    m_curMode = m_nextMode;
    m_nextMode = static_cast<TetrisMode>(getRandomInt(0, m_count.size() - 1));
    m_tetrisRotateStatus = 0;

    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_tetrisPos[i] = { 
            TETRIS_INIT_POS.first + TETRIS_MODE_ROTATE.at(m_curMode)[0][i].first,
            TETRIS_INIT_POS.second + TETRIS_MODE_ROTATE.at(m_curMode)[0][i].second
        };

        if (m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] != TetrisStyle::Blank) {
            success = false;
        }
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TETRIS_MODE_STYLE.at(m_curMode);
    }

    return success;
}

void Game::move(int delta) {
    std::array<std::pair<int, int>, TETRIS_NUM> targetPos;
    bool success = true;

    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TetrisStyle::Blank;
    }
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        targetPos[i] = { 
            m_tetrisPos[i].first,
            m_tetrisPos[i].second + delta
        };

        if (targetPos[i].second < 0 || targetPos[i].second >= TETRIS_FIELD_WIDTH || 
            m_field[targetPos[i].first][targetPos[i].second] != TetrisStyle::Blank) {
            success = false;
            break;
        }
    }

    if (success) {
        for (int i = 0; i < m_tetrisPos.size(); ++i) {
            m_tetrisPos[i] = targetPos[i];
        }
    }
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TETRIS_MODE_STYLE.at(m_curMode);
    }
}

void Game::rotate(int delta) {
    std::array<std::pair<int, int>, TETRIS_NUM> targetPos;
    bool success = true;

    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TetrisStyle::Blank;
    }
    auto& rotateList = TETRIS_MODE_ROTATE.at(m_curMode);
    int targetStatus = (m_tetrisRotateStatus + rotateList.size() + delta) % rotateList.size();

    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        targetPos[i] = { 
            m_tetrisPos[i].first + rotateList[targetStatus][i].first - rotateList[m_tetrisRotateStatus][i].first,
            m_tetrisPos[i].second + rotateList[targetStatus][i].second - rotateList[m_tetrisRotateStatus][i].second
        };

        if (targetPos[i].second < 0 || targetPos[i].second >= TETRIS_FIELD_WIDTH || targetPos[i].first < 0 ||
            m_field[targetPos[i].first][targetPos[i].second] != TetrisStyle::Blank) {
            success = false;
            break;
        }
    }

    if (success) {
        m_tetrisRotateStatus = targetStatus;
        for (int i = 0; i < m_tetrisPos.size(); ++i) {
            m_tetrisPos[i] = targetPos[i];
        }
    }
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        if (m_tetrisPos[i].first < TETRIS_FIELD_HEIGHT) {
            m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TETRIS_MODE_STYLE.at(m_curMode);
        }
    }
}

bool Game::drop() {
    std::array<std::pair<int, int>, TETRIS_NUM> targetPos;
    bool success = true;

    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TetrisStyle::Blank;
    }
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        targetPos[i] = { 
            m_tetrisPos[i].first - 1,
            m_tetrisPos[i].second
        };

        if (targetPos[i].first < 0 || 
            m_field[targetPos[i].first][targetPos[i].second] != TetrisStyle::Blank) {
            success = false;
            break;
        }
    }

    if (success) {
        for (int i = 0; i < m_tetrisPos.size(); ++i) {
            m_tetrisPos[i] = targetPos[i];
        }
    }
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TETRIS_MODE_STYLE.at(m_curMode);
    }

    return success;
}

std::vector<int> Game::checkEraseLine() {
    std::vector<int> lines;
    for (int i = 0; i < TETRIS_FIELD_HEIGHT; ++i) {
        bool isErase = true;
        for (int j = 0; j < TETRIS_FIELD_WIDTH; ++j) {
            if (m_field[i][j] == TetrisStyle::Blank) {
                isErase = false;
                break;
            }
        }
        if (isErase) {
            lines.emplace_back(i);
        }
    }
    return lines;
}

void Game::erase(std::vector<int>& lines, int order) {
    if (2 * order >= TETRIS_FIELD_WIDTH) {
        for (int j = 0; j < TETRIS_FIELD_WIDTH; ++j) {
            int slow = 0;
            for (int fast = 0; fast < TETRIS_FIELD_HEIGHT; ++fast) {
                if (m_field[fast][j] != TetrisStyle::Blank) {
                    m_field[slow++][j] = m_field[fast][j];
                }
            } 
            for (; slow < TETRIS_FIELD_HEIGHT; ++slow) {
                m_field[slow][j] = TetrisStyle::Blank;
            }
        }
    } else {
        for (auto line: lines) {
            m_field[line][TETRIS_FIELD_WIDTH / 2 + order] = TetrisStyle::Blank;
            m_field[line][(TETRIS_FIELD_WIDTH - 1) / 2 - order] = TetrisStyle::Blank;
        }
    }
}

int Game::calculate() {

}

bool Game::win() {

}