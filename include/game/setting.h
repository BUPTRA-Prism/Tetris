/**
 * @file setting.h
 * @brief 游戏设置，管理游戏类型、音乐、等级与高度等选项
 */
#pragma once

#include <optional>
#include <string_view>
#include <utility>
#include <vector>

/**
 * @brief 游戏设置，维护各选项列表与当前取值
 */
class Setting {
public:
    /**
     * @brief 游戏类型
     */
    enum class GameType {
        TypeA, ///< A 类型（标准模式）
        TypeB  ///< B 类型（障碍模式）
    };

private:
    std::vector<std::pair<std::string_view, GameType>> m_gameTypeOptions; ///< 游戏类型选项
    std::vector<std::pair<std::string_view, std::optional<std::string_view>>> m_musicOptions; ///< 音乐选项
    int m_maxLevel;  ///< 可选最大等级
    int m_maxHeight; ///< 可选最大高度

    int m_gameTypeOptionIdx; ///< 当前游戏类型下标
    int m_musicOptionIdx;    ///< 当前音乐下标
    int m_level;             ///< 当前等级
    int m_height;            ///< 当前高度

public:
    /** @brief 构造并初始化各选项与默认取值 */
    Setting();
    ~Setting() = default;

    Setting(const Setting& setting) = delete;
    Setting& operator=(const Setting& setting) = delete;
    Setting(Setting&& setting) = delete;
    Setting& operator=(Setting&& setting) = delete;

    /** @brief 获取游戏类型选项文本列表 */
    std::vector<std::string_view> GetGameTypeOptionStr() const;
    /** @brief 获取音乐选项文本列表 */
    std::vector<std::string_view> GetMusicOptionStr() const;
    /** @brief 获取最大可选等级 */
    int GetMaxLevel() const noexcept;
    /** @brief 获取最大可选高度 */
    int GetMaxHeight() const noexcept;

    /** @brief 获取当前游戏类型下标 */
    int GetGameTypeOptionIdx() const noexcept;
    /** @brief 获取当前游戏类型 */
    GameType GetGameType() const noexcept;
    /** @brief 获取当前音乐下标 */
    int GetMusicOptionIdx() const noexcept;
    /** @brief 获取当前音乐路径，OFF 状态时为 nullopt */
    std::optional<std::string_view> GetMusic() const noexcept;
    /** @brief 获取当前等级 */
    int GetLevel() const noexcept;
    /** @brief 获取当前高度 */
    int GetHeight() const noexcept;

    /**
     * @brief 调整游戏类型选项下标
     * @param delta 偏移量（±1）
     */
    void AdjustGameTypeOptionIdx(int delta);
    /**
     * @brief 调整音乐选项下标
     * @param delta 偏移量（±1）
     */
    void AdjustMusicOptionIdx(int delta);
    /**
     * @brief 调整等级
     * @param delta 偏移量
     */
    void AdjustLevel(int delta);
    /**
     * @brief 调整高度
     * @param delta 偏移量
     */
    void AdjustHeight(int delta);

private:
    /**
     * @brief 在 [0, max] 范围内调整下标，越界则忽略
     * @param idx 待调整下标
     * @param delta 偏移量
     * @param max 上限
     */
    static void AdjustIdx(int& idx, int delta, int max) noexcept;
};