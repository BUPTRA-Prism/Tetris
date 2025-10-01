#include "core/game.h"
#include "util/common.h"

Game::Game() {
    m_tetrisCount.emplace(TetrisMode::T, 0);
    m_tetrisCount.emplace(TetrisMode::J, 0);
    m_tetrisCount.emplace(TetrisMode::Z, 0);
    m_tetrisCount.emplace(TetrisMode::O, 0);
    m_tetrisCount.emplace(TetrisMode::S, 0);
    m_tetrisCount.emplace(TetrisMode::L, 0);
    m_tetrisCount.emplace(TetrisMode::I, 0);
}

int Game::getLevel() const { return m_level; }

int Game::getHeight() const { return m_height; }

int Game::getScore() const { return m_score; }

int Game::getLineCount() const { return m_lineCount; }

TetrisMode Game::getCurMode() const { return m_curMode; }

bool Game::isUpgrade() const { return m_upgrade; }

int Game::getTetrisCount(TetrisMode mode) const { 
    if (!m_tetrisCount.count(mode)) {
        return 0;
    }
    return m_tetrisCount.at(mode); 
}

TetrisStyle Game::getFieldStyle(int row, int col) const { 
    if (row < 0 || row >= m_field.size() || col < 0 || col >= m_field[0].size() ) {
        return TetrisStyle::Blank;
    }
    return m_field[row][col];
}

void Game::resetGame(int level, int height) {
    for (int row = 0; row < m_field.size(); ++row) {
        m_field[row].fill(TetrisStyle::Blank);
    }
    m_level = level;
    m_height = height;
    m_score = 0;
    m_lineCount = 0;

    for (auto it = m_tetrisCount.begin(); it != m_tetrisCount.end(); ++it) {
        it->second = 0;
    }

    m_nextMode = static_cast<TetrisMode>(getRandomInt(0, m_tetrisCount.size() - 1));

    m_levelLineCount = 0;
    m_upgrade = false;
}

bool Game::generate() {
    bool success = true;

    m_curMode = m_nextMode;
    m_nextMode = static_cast<TetrisMode>(getRandomInt(0, m_tetrisCount.size() - 1));
    ++m_tetrisCount.at(m_curMode);
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

bool Game::move(int delta) {
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

    return success;
}

bool Game::rotate(int delta) {
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
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TETRIS_MODE_STYLE.at(m_curMode);
    }

    return success;
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

int Game::checkEraseLine() {
    m_eraseLines.clear();
    for (int i = 0; i < TETRIS_FIELD_HEIGHT; ++i) {
        bool isErase = true;
        for (int j = 0; j < TETRIS_FIELD_WIDTH; ++j) {
            if (m_field[i][j] == TetrisStyle::Blank) {
                isErase = false;
                break;
            }
        }
        if (isErase) {
            m_eraseLines.emplace_back(i);
        }
    }
    return m_eraseLines.size();
}

bool Game::eraseComplete(int order) {
    if (2 * order >= TETRIS_FIELD_WIDTH) {
        for (int j = 0; j < TETRIS_FIELD_WIDTH; ++j) {
            int slow = 0;
            int eraseIdx = 0;
            for (int fast = 0; fast < TETRIS_FIELD_HEIGHT; ++fast) {
                if (eraseIdx == m_eraseLines.size() || fast != m_eraseLines[eraseIdx]) {
                    m_field[slow++][j] = m_field[fast][j];
                } else {
                    ++eraseIdx;
                }
            } 
            for (; slow < TETRIS_FIELD_HEIGHT; ++slow) {
                m_field[slow][j] = TetrisStyle::Blank;
            }
        }
        return true;
    } else {
        for (auto line: m_eraseLines) {
            m_field[line][TETRIS_FIELD_WIDTH / 2 + order] = TetrisStyle::Blank;
            m_field[line][(TETRIS_FIELD_WIDTH - 1) / 2 - order] = TetrisStyle::Blank;
        }
        return false;
    }
}

void Game::calculate(int accelerateLineCount) {
    m_lineCount += m_eraseLines.size();
    m_levelLineCount += m_eraseLines.size();
    if (m_levelLineCount >= 10 * (m_level + 1)) {
        ++m_level;
        m_levelLineCount = 0;
        m_upgrade = true;
    } else {
        m_upgrade = false;
    }
    m_score += TETRIS_ERASE_SCORE[m_eraseLines.size()] * (m_level + 1) + accelerateLineCount;
}

bool Game::win() {
    return false;
}