/**
 * @file logic.h
 * @brief 游戏核心逻辑，管理方块移动、旋转、消行与计分
 */
#pragma once

#include "config/game.h"
#include "config/rule.h"
#include "config/ui.h"
#include "game/setting.h"
#include <array>
#include <optional>
#include <random>
#include <unordered_map>
#include <utility>
#include <vector>
#include <SDL2/SDL_rect.h>

/**
 * @brief 游戏核心逻辑类
 */
class Logic {
public:
    /**
     * @brief 单一方块类型的静态数据
     */
    struct TetrominoData {
        Config::GameSceneUI::BlockType blockType; ///< 方块显示类型
        SDL_Point iconPos;                        ///< 图标位置
        int count;                                ///< 使用计数
        Rule::RotateData rotateData;              ///< 旋转位置偏移表
    };

    /** @brief 游戏区二维数组（含隐藏行），元素为方块显示类型 */
    using Field = std::array<
        std::array<Config::GameSceneUI::BlockType, Config::Game::FIELD_WIDTH>,
        Config::Game::FIELD_VISIBLE_HEIGHT + Config::Game::FIELD_HIDDEN_HEIGHT
    >;

private:
    std::vector<Rule::TetrominoType> m_tetrominoTypes;                ///< 方块类型列表
    std::vector<Config::GameSceneUI::BlockType> m_blockTypes;         ///< 方块小格显示类型列表

    int m_linesCnt; ///< 当前行数
    int m_score;    ///< 当前分数
    int m_level;    ///< 当前等级
    int m_height;   ///< 当前初始高度

    std::unordered_map<Rule::TetrominoType, TetrominoData> m_tetrominoData; ///< 各方块类型静态数据
    Field m_field; ///< 游戏区

    std::optional<Rule::TetrominoType> m_curTetrominoType;   ///< 当前方块类型
    std::optional<Rule::TetrominoType> m_nextTetrominoType;  ///< 下一个方块类型
    std::pair<int, int> m_pivot;                              ///< 当前方块旋转中心
    int m_curRotation;                                        ///< 当前旋转状态
    std::vector<std::pair<int, int>> m_curBlockPos;           ///< 当前方块各小格位置
    std::vector<int> m_eraseLines;                            ///< 待消除行

    std::mt19937 m_rng;                                              ///< 随机数引擎
    std::uniform_int_distribution<size_t> m_tetrominoTypeDist;       ///< 方块类型分布
    std::uniform_int_distribution<size_t> m_blockTypeDist;           ///< 方块小格显示类型分布
    std::uniform_int_distribution<int> m_handicapBlankDist;          ///< 障碍留空数分布
    std::array<int, Config::Game::FIELD_WIDTH> m_blockColVec;        ///< 障碍行洗牌用的列索引

public:
    /** @brief 构造并初始化各方块数据与随机数引擎 */
    Logic();
    ~Logic() = default;

    Logic(const Logic& logic) = delete;
    Logic& operator=(const Logic& logic) = delete;
    Logic(Logic&& logic) = delete;
    Logic& operator=(Logic&& logic) = delete;

    /** @brief 获取方块类型列表 */
    const std::vector<Rule::TetrominoType>& GetTetrominoTypes() const noexcept;
    /** @brief 获取当前行数 */
    int GetLinesCnt() const noexcept;
    /** @brief 获取当前分数 */
    int GetScore() const noexcept;
    /** @brief 获取当前等级 */
    int GetLevel() const noexcept;
    /** @brief 获取当前初始高度 */
    int GetHeight() const noexcept;
    /**
     * @brief 获取某方块的显示类型
     * @param tetrominoType 方块类型
     * @return 对应显示类型，不存在时返回 Blank
     */
    Config::GameSceneUI::BlockType GetTetrominoBlockType(Rule::TetrominoType tetrominoType) const noexcept;
    /**
     * @brief 获取某方块的图标位置
     * @param tetrominoType 方块类型
     * @return 图标位置
     */
    SDL_Point GetIconPos(Rule::TetrominoType tetrominoType) const noexcept;
    /**
     * @brief 获取某方块的使用计数
     * @param tetrominoType 方块类型
     * @return 使用计数
     */
    int GetTetrominoCnt(Rule::TetrominoType tetrominoType) const noexcept;
    /** @brief 获取游戏区只读引用 */
    const Field& GetField() const noexcept;
    /** @brief 获取当前方块类型（可能为 nullopt） */
    std::optional<Rule::TetrominoType> GetCurTetrominoType() const noexcept;
    /** @brief 获取下一个方块类型（可能为 nullopt） */
    std::optional<Rule::TetrominoType> GetNextTetrominoType() const noexcept;
    /**
     * @brief 获取某方块默认（旋转态 0）的位置偏移
     * @param tetrominoType 方块类型
     * @return 位置偏移集合
     */
    Rule::RotatePosDelta GetDefaultRotatePosDelta(Rule::TetrominoType tetrominoType) const noexcept;

    /**
     * @brief 重置游戏状态
     * @param gameType 游戏类型
     * @param level 初始等级
     * @param height 初始高度（B 类型有效）
     */
    void Reset(Setting::GameType gameType, int level, int height = 0);
    /**
     * @brief 生成新方块
     * @return 生成成功返回 true（失败通常意味着判定死亡）
     */
    bool Generate();
    /**
     * @brief 方块下落一行
     * @return 下落成功返回 true，落地锁定返回 false
     */
    bool Fall();
    /**
     * @brief 水平移动方块
     * @param delta 列偏移（±1）
     * @return 移动成功返回 true
     */
    bool MoveHorizontal(int delta);
    /**
     * @brief 旋转方块
     * @param delta 旋转方向（1 顺时针，-1 逆时针）
     * @return 旋转成功返回 true
     */
    bool Rotate(int delta);
    /** @brief 获取当前方块最底小格的行，用于计算生成延迟 */
    int GetLockRow() const noexcept;

    /**
     * @brief 检测并记录可消除的行
     * @return 可消除的行数
     */
    int CheckEraseLines();
    /**
     * @brief 执行一步逐块消除动画
     * @param step 当前消除步数
     * @return 动画成功返回 true，否则（例如本帧方块越界）返回 false
     */
    bool StepErase(int step);
    /** @brief 压实消除行并在顶部补空白 */
    void Erase();
    /**
     * @brief 结算分数与等级/行数
     * @param gameType 游戏类型
     * @param softFallLines 本次软降累计行数
     */
    void Calculate(Setting::GameType gameType, int softFallLines);
    /**
     * @brief 追加通关加成分数
     * @param level 等级
     * @param height 初始高度
     */
    void AddBuffScore(int level, int height);

private:
    /**
     * @brief 尝试将当前方块调整到指定枢轴与旋转态
     * @param pivot 目标旋转中心
     * @param rotation 目标旋转态
     * @return 无冲突并调整成功返回 true
     */
    bool AdjustCurBlocks(std::pair<int, int> pivot, int rotation);
};