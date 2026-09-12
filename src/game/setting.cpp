/**
 * @file setting.cpp
 * @brief 游戏设置实现
 */
#include "game/setting.h"
#include "config/game.h"
#include "config/resource.h"
#include "config/ui.h"

/**
 * @brief 构造并初始化各选项列表与默认取值
 */
Setting::Setting()
    : m_gameTypeOptions({
        { Config::UICommon::GAME_TYPE_A_TEXT_STR, GameType::TypeA },
        { Config::UICommon::GAME_TYPE_B_TEXT_STR, GameType::TypeB }
    })
    , m_musicOptions({
        { Config::MenuSceneUI::MUSIC_1_TEXT_STR, Resource::Audio::BGM_1 },
        { Config::MenuSceneUI::MUSIC_2_TEXT_STR, Resource::Audio::BGM_2 },
        { Config::MenuSceneUI::MUSIC_3_TEXT_STR, Resource::Audio::BGM_3 },
        { Config::MenuSceneUI::MUSIC_OFF_TEXT_STR, std::nullopt }
    })
    , m_maxLevel(Config::Setting::MAX_LEVEL)
    , m_maxHeight(Config::Setting::MAX_HEIGHT)
    , m_gameTypeOptionIdx(0)
    , m_musicOptionIdx(0)
    , m_level(0)
    , m_height(0) {}

/**
 * @brief 获取游戏类型选项文本列表
 */
std::vector<std::string_view> Setting::GetGameTypeOptionStr() const {
    std::vector<std::string_view> gameTypeOptionText(m_gameTypeOptions.size());
    for (size_t i = 0; i < m_gameTypeOptions.size(); ++i) {
        gameTypeOptionText[i] = m_gameTypeOptions[i].first;
    }
    return gameTypeOptionText;
}

/**
 * @brief 获取音乐选项文本列表
 */
std::vector<std::string_view> Setting::GetMusicOptionStr() const {
    std::vector<std::string_view> musicOptionText(m_musicOptions.size());
    for (size_t i = 0; i < m_musicOptions.size(); ++i) {
        musicOptionText[i] = m_musicOptions[i].first;
    }
    return musicOptionText;
}

/** @brief 获取最大可选等级 */
int Setting::GetMaxLevel() const noexcept {
    return m_maxLevel;
}

/** @brief 获取最大可选高度 */
int Setting::GetMaxHeight() const noexcept {
    return m_maxHeight;
}

/** @brief 获取当前游戏类型下标 */
int Setting::GetGameTypeOptionIdx() const noexcept {
    return m_gameTypeOptionIdx;
}

/** @brief 获取当前游戏类型 */
Setting::GameType Setting::GetGameType() const noexcept {
    return m_gameTypeOptions[m_gameTypeOptionIdx].second;
}

/** @brief 获取当前音乐下标 */
int Setting::GetMusicOptionIdx() const noexcept {
    return m_musicOptionIdx;
}

/** @brief 获取当前音乐路径，OFF 状态时为 nullopt */
std::optional<std::string_view> Setting::GetMusic() const noexcept {
    return m_musicOptions[m_musicOptionIdx].second;
}

/** @brief 获取当前等级 */
int Setting::GetLevel() const noexcept {
    return m_level;
}

/** @brief 获取当前高度 */
int Setting::GetHeight() const noexcept {
    return m_height;
}

/**
 * @brief 调整游戏类型选项下标
 */
void Setting::AdjustGameTypeOptionIdx(int delta) {
    if (m_gameTypeOptions.empty()) {
        return;
    }

    AdjustIdx(m_gameTypeOptionIdx, delta, static_cast<int>(m_gameTypeOptions.size()) - 1);
}

/**
 * @brief 调整音乐选项下标
 */
void Setting::AdjustMusicOptionIdx(int delta) {
    if (m_musicOptions.empty()) {
        return;
    }
    
    AdjustIdx(m_musicOptionIdx, delta, static_cast<int>(m_musicOptions.size()) - 1);
}

/**
 * @brief 调整等级
 */
void Setting::AdjustLevel(int delta) {
    AdjustIdx(m_level, delta, m_maxLevel);
}

/**
 * @brief 调整高度
 */
void Setting::AdjustHeight(int delta) {
    AdjustIdx(m_height, delta, m_maxHeight);
}

/**
 * @brief 在 [0, max] 范围内调整下标，越界则忽略本次调整
 */
void Setting::AdjustIdx(int& idx, int delta, int max) noexcept {
    if (idx + delta >= 0 && idx + delta <= max) {
        idx += delta;
    }
}