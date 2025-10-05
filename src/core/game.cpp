#include "core/game.h"
#include "util/common.h"

Game::Game() {
    // 初始化各种类型方块统计
    m_tetrisCount = {
        { TetrisMode::T, 0 },
        { TetrisMode::J, 0 },
        { TetrisMode::Z, 0 },
        { TetrisMode::O, 0 },
        { TetrisMode::S, 0 },
        { TetrisMode::L, 0 },
        { TetrisMode::I, 0 }
    };
}

int Game::getLevel() const { return m_level; }

int Game::getScore() const { return m_score; }

int Game::getLineCount() const { return m_lineCount; }

TetrisStyle Game::getFieldStyle(int row, int col) const { 
    // 边界检查
    if (row >= 0 && row < m_field.size() && col >= 0 && col < m_field[0].size() ) {
        return m_field[row][col];
    }
    // 兜底
    return TetrisStyle::Blank;
}

int Game::getTetrisCount(TetrisMode mode) const { 
    // 边界检查
    if (m_tetrisCount.count(mode)) {
        return m_tetrisCount.at(mode);
    }
    // 兜底
    return 0; 
}

TetrisMode Game::getCurMode() const { return m_curMode; }

TetrisMode Game::getNextMode() const { return m_nextMode; }

int Game::getTetrisLowestRow() const {
    // 找到当前方块的最低行位置
    int row = m_tetrisPos[0].first;
    for (auto& pos: m_tetrisPos) {
        if (pos.first < row) {
            row = pos.first;
        }
    }
    return row;
}

void Game::resetGame(int level) {
    m_level = level;
    m_score = 0;
    m_lineCount = 0;

    // 清空游戏场地
    for (auto& row : m_field) {
        row.fill(TetrisStyle::Blank);
    }
    // 清空方块统计
    for (auto& pair : m_tetrisCount) {
        pair.second = 0;
    }
    // 随机生成下一个方块类型
    m_nextMode = static_cast<TetrisMode>(getRandomInt(0, m_tetrisCount.size() - 1));
}

bool Game::generate() {
    bool success = true;
    // 更新下一个方块和当前方块
    m_curMode = m_nextMode;
    m_nextMode = static_cast<TetrisMode>(getRandomInt(0, m_tetrisCount.size() - 1));
    // 1H2R - 如果第一次随机到的方块类型与当前方块类型重复，则再生成一次
    // 第二次无论是否重复，都不再重新生成
    if (m_nextMode == m_curMode) {
        m_nextMode = static_cast<TetrisMode>(getRandomInt(0, m_tetrisCount.size() - 1));
    }
    // 当前方块统计+1
    ++m_tetrisCount.at(m_curMode);
    // 重置方块旋转状态
    m_tetrisRotateStatus = 0;

    // 根据方块类型和初始位置设置方块位置
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_tetrisPos[i] = { 
            TETRIS_INIT_POS.first + TETRIS_MODE_ROTATE.at(m_curMode)[0][i].first,
            TETRIS_INIT_POS.second + TETRIS_MODE_ROTATE.at(m_curMode)[0][i].second
        };

        // 检查位置是否被占用，如果被占用则生成失败
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

    // 清除当前方块在场地中的标记
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TetrisStyle::Blank;
    }

    // 计算移动后的目标位置并检查是否合法
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        targetPos[i] = { 
            m_tetrisPos[i].first,
            m_tetrisPos[i].second + delta
        };

        // 检查列边界和碰撞
        if (targetPos[i].second < 0 || targetPos[i].second >= TETRIS_FIELD_WIDTH || 
            m_field[targetPos[i].first][targetPos[i].second] != TetrisStyle::Blank) {
            success = false;
            break;
        }
    }

    // 如果移动合法，更新位置
    if (success) {
        for (int i = 0; i < m_tetrisPos.size(); ++i) {
            m_tetrisPos[i] = targetPos[i];
        }
    }
    // 重新在场地中标记方块
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TETRIS_MODE_STYLE.at(m_curMode);
    }

    return success;
}

bool Game::rotate(int delta) {
    std::array<std::pair<int, int>, TETRIS_NUM> targetPos;
    bool success = true;

    // 清除当前方块在场地中的标记
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TetrisStyle::Blank;
    }

    // 获取旋转配置，并计算目标旋转状态
    auto& rotateList = TETRIS_MODE_ROTATE.at(m_curMode);
    int targetStatus = (m_tetrisRotateStatus + rotateList.size() + delta) % rotateList.size();

    // 计算旋转后的目标位置并检查是否合法
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        targetPos[i] = { 
            m_tetrisPos[i].first + rotateList[targetStatus][i].first - rotateList[m_tetrisRotateStatus][i].first,
            m_tetrisPos[i].second + rotateList[targetStatus][i].second - rotateList[m_tetrisRotateStatus][i].second
        };

        // 检查边界和碰撞
        if (targetPos[i].second < 0 || targetPos[i].second >= TETRIS_FIELD_WIDTH || targetPos[i].first < 0 ||
            m_field[targetPos[i].first][targetPos[i].second] != TetrisStyle::Blank) {
            success = false;
            break;
        }
    }

    // 如果旋转合法，更新位置和旋转状态
    if (success) {
        m_tetrisRotateStatus = targetStatus;
        for (int i = 0; i < m_tetrisPos.size(); ++i) {
            m_tetrisPos[i] = targetPos[i];
        }
    }
    // 重新在场地中标记方块
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TETRIS_MODE_STYLE.at(m_curMode);
    }

    return success;
}

bool Game::drop() {
    std::array<std::pair<int, int>, TETRIS_NUM> targetPos;
    bool success = true;

    // 清除当前方块在场地中的标记
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TetrisStyle::Blank;
    }

    // 计算下落一格后的目标位置
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        targetPos[i] = { 
            m_tetrisPos[i].first - 1,
            m_tetrisPos[i].second
        };

        // 检查是否触底或碰撞
        if (targetPos[i].first < 0 || 
            m_field[targetPos[i].first][targetPos[i].second] != TetrisStyle::Blank) {
            success = false;
            break;
        }
    }

    // 如果下落合法，更新位置
    if (success) {
        for (int i = 0; i < m_tetrisPos.size(); ++i) {
            m_tetrisPos[i] = targetPos[i];
        }
    }
    // 重新在场地中标记方块
    for (int i = 0; i < m_tetrisPos.size(); ++i) {
        m_field[m_tetrisPos[i].first][m_tetrisPos[i].second] = TETRIS_MODE_STYLE.at(m_curMode);
    }

    return success;
}

int Game::checkEraseLine() {
    m_eraseLines.clear();

    // 遍历所有行，检查是否有完整的行可以消除
    for (int i = 0; i < TETRIS_FIELD_HEIGHT; ++i) {
        bool isErase = true;
        for (int j = 0; j < TETRIS_FIELD_WIDTH; ++j) {
            if (m_field[i][j] == TetrisStyle::Blank) {
                isErase = false;
                break;
            }
        }
        if (isErase) {
            // 记录需要消除的行号
            m_eraseLines.emplace_back(i);
        }
    }
    return m_eraseLines.size();
}

bool Game::eraseComplete(int order) {
    // 如果待消除行方块已消除完毕
    if (2 * order >= TETRIS_FIELD_WIDTH) {
        // 未消除行下落（双指针）
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
        // 从中间向两侧，每一步 order 对应左右各消除一个方块
        for (auto line: m_eraseLines) {
            m_field[line][TETRIS_FIELD_WIDTH / 2 + order] = TetrisStyle::Blank;
            m_field[line][(TETRIS_FIELD_WIDTH - 1) / 2 - order] = TetrisStyle::Blank;
        }
        return false;
    }
}

bool GameA::isUpgrade() const { return m_upgrade; }

void GameA::specificReset() { m_upgrade = false; }

void GameA::calculate(int accelerateLineCount) {
    // 更新已消除行数
    m_lineCount += m_eraseLines.size();

    // 检查是否升级
    m_upgrade = false;
    if (m_lineCount >= 10 * (m_level + 1)) {
        ++m_level;
        m_upgrade = true;
    }

    // 计算得分：基础得分 * (等级 + 1) + 加速下落奖励
    m_score += TETRIS_ERASE_SCORE[m_eraseLines.size()] * (m_level + 1) + accelerateLineCount;
}

int GameB::getHeight() const { return m_height; }

void GameB::specificReset(int height) {
    m_height = height;
    m_lineCount = TYPE_B_TARGET_LINE_COUNT;

    // 根据高度生成垃圾行
    for (int i = 0; i < TETRIS_HEIGHT_LINE[height]; ++i) {
        // 随机决定每行哪些位置生成垃圾方块
        int garbageCount = getRandomInt(TYPE_B_GARBAGE_MIN_COUNT, TYPE_B_GARBAGE_MAX_COUNT);
        std::vector<int> garbageIdxList = getRandomIntList(0, TETRIS_FIELD_WIDTH - 1, garbageCount);
        for (auto idx: garbageIdxList) {
            // 随机生成垃圾方块样式
            m_field[i][idx] = static_cast<TetrisStyle>(
                getRandomInt(static_cast<int>(TetrisStyle::SolidDark), static_cast<int>(TetrisStyle::HollowDark))
            );
        }
    }
}

void GameB::calculate(int accelerateLineCount) {
    // 更新剩余需要消除的行数
    m_lineCount -= m_eraseLines.size();
    if (m_lineCount < 0) {
        m_lineCount = 0;
    } 

    // 计算得分：基础得分 * (等级 + 1) + 加速下落奖励
    m_score += TETRIS_ERASE_SCORE[m_eraseLines.size()] * (m_level + 1) + accelerateLineCount;
}