/**
 * @file game.h
 * @brief 游戏共享数据结构，聚合设置、排行榜与游戏逻辑
 */
#pragma once

class Setting;
class LeaderBoard;
class Logic;

/**
 * @brief 游戏共享数据集合
 */
struct Game {
    Setting& setting;        ///< 设置
    LeaderBoard& leaderBoard; ///< 排行榜
    Logic& logic;            ///< 游戏逻辑
};