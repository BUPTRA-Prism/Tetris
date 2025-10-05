#include "core/settings.h"
#include "conf/resourceconf.h"

Settings& Settings::getInstance() {
    static Settings instance;
    return instance;
}

Settings::Settings()
    : m_gameTypeIdx(0)
    , m_musicTypeIdx(0)
    , m_initLevel(0)
    , m_initHeight(0)
    , m_newRecordOrder(RECORD_COUNT) {}

bool Settings::setGameType(int delta) {
    // 检查调整后的索引是否在有效范围内
    if (m_gameTypeIdx + delta >= 0 && m_gameTypeIdx + delta < GAME_TYPE.size()) {
        m_gameTypeIdx += delta; // 更新索引
        return true;            // 设置成功
    }
    return false;   // 设置失败
}

bool Settings::setMusicType(int delta) {
    // 检查调整后的索引是否在有效范围内
    if (m_musicTypeIdx + delta >= 0 && m_musicTypeIdx + delta < MUSIC_TYPE.size()) {
        m_musicTypeIdx += delta;    // 更新索引
        return true;                // 设置成功
    }
    return false;   // 设置失败
}

bool Settings::setInitLevel(int delta) {
    // 检查调整后的初始等级是否在有效范围内
    if (m_initLevel + delta >= 0 && m_initLevel + delta <= MAX_INIT_LEVEL) {
        m_initLevel += delta;   // 更新初始等级
        return true;            // 设置成功
    }
    return false;   // 设置失败
}

bool Settings::setInitHeight(int delta) {
    // 检查调整后的初始高度是否在有效范围内
    if (m_initHeight + delta >= 0 && m_initHeight + delta <= MAX_INIT_HEIGHT) {
        m_initHeight += delta;  // 更新初始高度
        return true;            // 设置成功
    }
    return false;   // 设置失败
}

void Settings::insertRecord(int score, int lv) {
    int idx = RECORD_COUNT - 1; // 从纪录最后一名开始比较
    // 获取当前模式排行榜
    auto* records = getCurrentRecords();
    if (!records) {
        return ;
    }
    // 倒序比较，优先比较分数，分数相同比较等级
    for (; idx >= 0; --idx) {
        if ((*records)[idx].score > score || ((*records)[idx].score == score && (*records)[idx].lv > lv)) {
            break;
        }
    }
    // 如果新纪录能进入排行榜
    if (idx != RECORD_COUNT - 1) {
        // 将插入位置后面的纪录依次后移一位
        for (int i = RECORD_COUNT - 1; i > idx + 1; --i) {
            (*records)[i] = (*records)[i - 1];
        }
        // 插入新纪录
        (*records)[idx + 1] = Record { "", score, lv };
    }
    // 更新新纪录所在次序
    m_newRecordOrder = idx + 1;
}

void Settings::updateRecordName(std::string name) {
    // 获取当前模式排行榜
    auto* records = getCurrentRecords();
    if (records && m_newRecordOrder >= 0 && m_newRecordOrder < records->size() ) {
        // 更新新纪录姓名
        (*records)[m_newRecordOrder].name = name;
    }
}

int Settings::getGameTypeIdx() const { return m_gameTypeIdx; }

int Settings::getMusicTypeIdx() const { return m_musicTypeIdx; }

int Settings::getInitLevel() const { return m_initLevel; }

int Settings::getInitHeight() const { return m_initHeight; }

int Settings::getNewRecordOrder() const { return m_newRecordOrder; }

std::string Settings::getGameType() const { return GAME_TYPE[m_gameTypeIdx]; }

std::string Settings::getMusicPath() const { return MUSIC_TYPE[m_musicTypeIdx].path; }

Record Settings::getRecordInfo(int order) const {
    // 获取当前模式排行榜
    auto* records = getCurrentRecords();
    if (records && order >= 0 && order < records->size()) {
        return (*records)[order];
    }
    // 兜底
    return Record { "", 0, 0 };
}

decltype(&RECORD_A) Settings::getCurrentRecords() const {
    // 根据游戏模式返回排行榜
    if (GAME_TYPE[m_gameTypeIdx] == GAME_TYPE_A) {
        return &RECORD_A;
    } else if (GAME_TYPE[m_gameTypeIdx] == GAME_TYPE_B) {
        return &RECORD_B;
    }
    // 兜底
    return nullptr;
}