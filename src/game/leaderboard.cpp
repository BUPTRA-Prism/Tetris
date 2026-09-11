/**
 * @file leaderboard.cpp
 * @brief 排行榜实现
 */
#include "game/leaderboard.h"

/**
 * @brief 构造并载入默认排行榜数据
 */
LeaderBoard::LeaderBoard()
    : m_playerRank(-1)
    , m_playerNameCharsetPos{} {
    m_leaderBoardA = std::vector<LeaderBoard::Entry> {
        LeaderBoard::Entry{ std::string(Config::Rank::RANK_A_NAME_1), Config::Rank::RANK_A_SCORE_1, Config::Rank::RANK_LEVEL_1 },
        LeaderBoard::Entry{ std::string(Config::Rank::RANK_A_NAME_2), Config::Rank::RANK_A_SCORE_2, Config::Rank::RANK_LEVEL_2 },
        LeaderBoard::Entry{ std::string(Config::Rank::RANK_A_NAME_3), Config::Rank::RANK_A_SCORE_3, Config::Rank::RANK_LEVEL_3 }
    };
    m_leaderBoardB = std::vector<LeaderBoard::Entry> {
        LeaderBoard::Entry{ std::string(Config::Rank::RANK_B_NAME_1), Config::Rank::RANK_B_SCORE_1, Config::Rank::RANK_LEVEL_1 },
        LeaderBoard::Entry{ std::string(Config::Rank::RANK_B_NAME_2), Config::Rank::RANK_B_SCORE_2, Config::Rank::RANK_LEVEL_2 },
        LeaderBoard::Entry{ std::string(Config::Rank::RANK_B_NAME_3), Config::Rank::RANK_B_SCORE_3, Config::Rank::RANK_LEVEL_3 }
    };
}

/**
 * @brief 获取指定类型的排行榜副本
 */
std::vector<LeaderBoard::Entry> LeaderBoard::GetLeaderBoard(Setting::GameType gameType) const {
    switch (gameType) {
        case Setting::GameType::TypeA:
            return m_leaderBoardA;
        case Setting::GameType::TypeB:
            return m_leaderBoardB;
        default:
            return {};
    }
}

/**
 * @brief 获取指定类型的最高分（榜首分数）
 */
int LeaderBoard::GetHiScore(Setting::GameType gameType) const {
    switch (gameType) {
        case Setting::GameType::TypeA:
            return m_leaderBoardA.empty() ? 0 : m_leaderBoardA[0].score;
        case Setting::GameType::TypeB:
            return m_leaderBoardB.empty() ? 0 : m_leaderBoardB[0].score;
        default:
            return 0;
    }
}

/** @brief 获取玩家当前排名 */
int LeaderBoard::GetPlayerRank() const {
    return m_playerRank;
}

/**
 * @brief 插入玩家成绩并按序更新排行榜
 */
bool LeaderBoard::Insert(Setting::GameType gameType, int score, int level) {
    switch (gameType) {
        case Setting::GameType::TypeA: {
            return InsertEntry(m_leaderBoardA, score, level);
        }
        case Setting::GameType::TypeB: {
            return InsertEntry(m_leaderBoardB, score, level);
        }
        default: {
            return false;
        }
    }
}

/**
 * @brief 调整玩家姓名某一字符
 */
void LeaderBoard::UpdatePlayerName(Setting::GameType gameType, int charIdx, int delta) {
    switch (gameType) {
        case Setting::GameType::TypeA: {
            UpdateName(m_leaderBoardA, charIdx, delta);
            break;
        }
        case Setting::GameType::TypeB: {
            UpdateName(m_leaderBoardB, charIdx, delta);
            break;
        }
        default: {
            break;
        }
    }
}

/**
 * @brief 向指定排行榜插入成绩
 *
 * 从榜尾向前找到第一个可被超越的条目作为插入位置，
 * 将后续条目后移一位并填入玩家新条目
 */
bool LeaderBoard::InsertEntry(std::vector<LeaderBoard::Entry>& entries, int score, int level) {
    m_playerRank = -1;
    m_playerNameCharsetPos.fill(0);

    if (entries.empty()) {
        return false;
    }

    for (int i = static_cast<int>(entries.size()) - 1; i >= 0; --i) {
        if (entries[i].score < score || (entries[i].score == score && entries[i].level < level)) {
            m_playerRank = i;
        }
    }

    if (m_playerRank != -1) {
        for (int i = static_cast<int>(entries.size()) - 1; i > m_playerRank; --i) {
            entries[i] = entries[i - 1];
        }
        entries[m_playerRank] = LeaderBoard::Entry{
            std::string(Config::Rank::NAME_LEN, Config::Rank::NAME_CHARSET[0]),
            score,
            level
        };
        return true;
    }

    return false;
}

/**
 * @brief 更新指定排行榜中玩家姓名的某一字符
 */
void LeaderBoard::UpdateName(std::vector<LeaderBoard::Entry>& entries, int charIdx, int delta) {
    if (m_playerRank == -1 || charIdx < 0 || charIdx >= Config::Rank::NAME_LEN) {
        return;
    }

    int charsetLen = static_cast<int>(Config::Rank::NAME_CHARSET.size());
    int& charsetPos = m_playerNameCharsetPos[charIdx];
    charsetPos = (charsetPos + delta + charsetLen) % charsetLen;
    (entries[m_playerRank].name)[charIdx] = Config::Rank::NAME_CHARSET[charsetPos];
}