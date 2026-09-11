/**
 * @file game.h
 * @brief 游戏配置与排行榜的数值配置
 */
#pragma once

#include <array>
#include <string_view>

namespace Config {
    /**
     * @brief 设置项相关配置
     */
    namespace Setting {
        /** @brief 可选的最大等级 */
        constexpr int MAX_LEVEL = 9;
        /** @brief 可选的最大初始高度（仅 B 类型） */
        constexpr int MAX_HEIGHT = 5;
    }

    /**
     * @brief 游戏核心配置
     */
    namespace Game {
        /** @brief B 类型游戏开局时的初始行数 */
        constexpr int GAME_TYPE_B_INIT_LINES_COUNT = 25;

        /** @brief 游戏区可见行数 */
        constexpr int FIELD_VISIBLE_HEIGHT = 20;
        /** @brief 游戏区隐藏行数（位于顶部，仅用于生成/判死） */
        constexpr int FIELD_HIDDEN_HEIGHT = 4;
        /** @brief 游戏区列数 */
        constexpr int FIELD_WIDTH = 10;
        /** @brief 各初始高度对应的预填行数（B 类型障碍） */
        constexpr std::array<int, Setting::MAX_HEIGHT + 1> HANDICAP_LINES = { 0, 3, 5, 8, 10, 12 };
        /** @brief 新方块生成时旋转中心的初始列 */
        constexpr int INIT_GENERATE_Y = 4;

        /** @brief 障碍行中随机留空小格的最少数目 */
        constexpr int HANDICAP_BLANK_BLOCK_MIN_NUM = 4;
        /** @brief 障碍行中随机留空小格的最多数目 */
        constexpr int HANDICAP_BLANK_BLOCK_MAX_NUM = 6;

        /** @brief 生成下一个方块时最多随机重掷次数（用于避免连续相同） */
        constexpr int GENERATE_ROLL = 2;

        /**
         * @brief 根据锁定行计算生成新方块的延迟帧数
         * @param row 锁定行索引
         * @return 生成延迟帧数
         */
        constexpr int CalculateGenerateDelayFrame(int row) {
            return 10 + ((row + 2) / 4) * 2;
        }

        /** @brief 单次可消除的最大行数 */
        constexpr int ERASE_MAX_COUNT = 4;
        /** @brief 消除 1~4 行对应的基础得分 */
        constexpr std::array<int, ERASE_MAX_COUNT> ERASE_SCORE = { 40, 100, 300, 1200 };

        /**
         * @brief 计算消除得分
         * @param level 当前等级
         * @param eraseCnt 消除行数
         * @return 消除得分，非法消除行数返回 0
         */
        constexpr int CalculateEraseScore(int level, int eraseCnt) {
            if (eraseCnt <= 0 || eraseCnt > ERASE_MAX_COUNT) {
                return 0;
            }
            return (level + 1) * ERASE_SCORE[eraseCnt - 1];
        }

        /**
         * @brief 计算 B 类型通关的加成得分
         * @param num 加成基数
         * @return 加成得分
         */
        constexpr int CalculateBuffScore(int num) {
            return 1000 * num;
        }

        /** @brief 下落速度表的最大等级（即表中元素个数） */
        constexpr int DEAD_LEVEL = 30;
        /** @brief 各等级的下落总帧数（值越小下落越快） */
        constexpr std::array<int, DEAD_LEVEL> FALL_TOTAL_FRAME = {
            48, 43, 38, 33, 28, 23, 18, 13, 8, 6,
            5, 5, 5, 4, 4, 4, 3, 3, 3, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 1
        };

        /**
         * @brief 获取指定等级的下落总帧数
         * @param level 等级
         * @return 下落总帧数，越界时返回表中最后一档
         */
        constexpr int GetFallTotalFrame(int level) {
            if (level >= 0 && level < DEAD_LEVEL) {
                return FALL_TOTAL_FRAME[level];
            }
            return FALL_TOTAL_FRAME.back();
        }
        /** @brief 软降（按住下键）时的下落总帧数 */
        constexpr int SOFT_FALL_TOTAL_FRAME = 2;
        /** @brief 按住左右键首次移动前的延迟帧数（DAS） */
        constexpr int DAS_TOTAL_FRAME = 16;
        /** @brief 按住左右键后续自动重复移动的间隔帧数（ARR） */
        constexpr int ARR_TOTAL_FRAME = 6;
        /** @brief 逐块消除动画的单步帧数 */
        constexpr int STEP_ERASE_TOTAL_FRAME = 4;
    }

    /**
     * @brief 排行榜相关的默认数据与规则
     */
    namespace Rank {
        /** @brief A 类型排行榜第一名默认名字 */
        constexpr std::string_view RANK_A_NAME_1 = "HOWARD";
        /** @brief A 类型排行榜第二名默认名字 */
        constexpr std::string_view RANK_A_NAME_2 = "OTASAN";
        /** @brief A 类型排行榜第三名默认名字 */
        constexpr std::string_view RANK_A_NAME_3 = "LANCE";
        /** @brief B 类型排行榜第一名默认名字 */
        constexpr std::string_view RANK_B_NAME_1 = "ALEX";
        /** @brief B 类型排行榜第二名默认名字 */
        constexpr std::string_view RANK_B_NAME_2 = "TONY";
        /** @brief B 类型排行榜第三名默认名字 */
        constexpr std::string_view RANK_B_NAME_3 = "NINTEN";
        /** @brief A 类型排行榜第一名默认分数 */
        constexpr int RANK_A_SCORE_1 = 10000;
        /** @brief A 类型排行榜第二名默认分数 */
        constexpr int RANK_A_SCORE_2 = 7500;
        /** @brief A 类型排行榜第三名默认分数 */
        constexpr int RANK_A_SCORE_3 = 5000;
        /** @brief B 类型排行榜第一名默认分数 */
        constexpr int RANK_B_SCORE_1 = 2000;
        /** @brief B 类型排行榜第二名默认分数 */
        constexpr int RANK_B_SCORE_2 = 1000;
        /** @brief B 类型排行榜第三名默认分数 */
        constexpr int RANK_B_SCORE_3 = 500;
        /** @brief 排行榜条目第一名默认等级 */
        constexpr int RANK_LEVEL_1 = 9;
        /** @brief 排行榜条目第二名默认等级 */
        constexpr int RANK_LEVEL_2 = 5;
        /** @brief 排行榜条目第三名默认等级 */
        constexpr int RANK_LEVEL_3 = 0;
        /** @brief 玩家姓名最大长度 */
        constexpr int NAME_LEN = 6;
        /** @brief 姓名可用的字符集，首个字符用于占位初始化 */
        constexpr std::string_view NAME_CHARSET = "-ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,/()\". ";
    }
}