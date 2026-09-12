/**
 * @file leaderboard.h
 * @brief 排行榜，维护 A/B 两种游戏类型的得分记录
 */
#pragma once

#include "config/game.h"
#include "game/setting.h"
#include <array>
#include <string>
#include <vector>

/**
 * @brief 排行榜，维护并更新得分记录与玩家姓名
 */
class LeaderBoard {
public:
    /**
     * @brief 排行榜条目
     */
    struct Entry {
        std::string name; ///< 名字
        int score;        ///< 分数
        int level;        ///< 等级
    };

private:
    std::vector<Entry> m_leaderBoardA; ///< A 类型排行榜
    std::vector<Entry> m_leaderBoardB; ///< B 类型排行榜

    int m_playerRank; ///< 玩家当前排名（-1 表示未上榜）
    std::array<int, Config::Rank::NAME_LEN> m_playerNameCharsetPos; ///< 玩家姓名各字符在字符集中的位置

public:
    /** @brief 构造并载入默认排行榜数据 */
    LeaderBoard();
    ~LeaderBoard() = default;

    LeaderBoard(const LeaderBoard& leaderBoard) = delete;
    LeaderBoard& operator=(const LeaderBoard& leaderBoard) = delete;
    LeaderBoard(LeaderBoard&& leaderBoard) = delete;
    LeaderBoard& operator=(LeaderBoard&& leaderBoard) = delete;

    /**
     * @brief 获取指定类型的排行榜
     * @param gameType 游戏类型
     * @return 对应排行榜副本
     */
    std::vector<Entry> GetLeaderBoard(Setting::GameType gameType) const;
    /**
     * @brief 获取指定类型的最高分
     * @param gameType 游戏类型
     * @return 最高分，空榜返回 0
     */
    int GetHiScore(Setting::GameType gameType) const noexcept;
    /** @brief 获取玩家当前排名 */
    int GetPlayerRank() const noexcept;

    /**
     * @brief 插入玩家成绩并按序更新排行榜
     * @param gameType 游戏类型
     * @param score 分数
     * @param level 等级
     * @return 上榜成功返回 true
     */
    bool Insert(Setting::GameType gameType, int score, int level);
    /**
     * @brief 调整玩家姓名某一字符
     * @param gameType 游戏类型
     * @param charIdx 字符下标
     * @param delta 字符集循环偏移量
     */
    void UpdatePlayerName(Setting::GameType gameType, int charIdx, int delta);

private:
    /**
     * @brief 向指定排行榜插入成绩
     * @param entries 目标排行榜
     * @param score 分数
     * @param level 等级
     * @return 上榜成功返回 true
     */
    bool InsertEntry(std::vector<Entry>& entries, int score, int level);
    /**
     * @brief 更新指定排行榜中玩家姓名的某一字符
     * @param entries 目标排行榜
     * @param charIdx 字符下标
     * @param delta 字符集循环偏移量
     */
    void UpdateName(std::vector<Entry>& entries, int charIdx, int delta);
};