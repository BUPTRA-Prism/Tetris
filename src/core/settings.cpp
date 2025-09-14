#include "core/settings.h"
#include "conf/resourceconf.h"

Settings& Settings::getInstance() {
    static Settings instance;
    return instance;
}

Settings::Settings()
    : m_curGameTypeIdx(0)
    , m_curMusicTypeIdx(0)
    , m_curLevel(0)
    , m_curHeight(0) {}

bool Settings::setGameType(int delta) {
    if (m_curGameTypeIdx + delta >= 0 && m_curGameTypeIdx + delta < GAME_TYPE.size()) {
        m_curGameTypeIdx += delta;
        return true;
    }
    return false;
}

bool Settings::setMusicType(int delta) {
    if (m_curMusicTypeIdx + delta >= 0 && m_curMusicTypeIdx + delta < MUSIC_TYPE.size()) {
        m_curMusicTypeIdx += delta;
        return true;
    }
    return false;
}

bool Settings::setLevel(int delta) {
    if (m_curLevel + delta >= 0 && m_curLevel + delta <= MAX_LEVEL) {
        m_curLevel += delta;
        return true;
    }
    return false;
}

bool Settings::setHeight(int delta) {
    if (m_curHeight + delta >= 0 && m_curHeight + delta <= MAX_HEIGHT) {
        m_curHeight += delta;
        return true;
    }
    return false;
}

bool Settings::setRecord(std::string name, int score, int lv) {
    return false;
}

int Settings::getGameTypeIdx() const { return m_curGameTypeIdx; }

int Settings::getMusicTypeIdx() const { return m_curMusicTypeIdx; }

int Settings::getLevel() const { return m_curLevel; }

int Settings::getHeight() const { return m_curHeight; }

std::string Settings::getGameType() const { return GAME_TYPE[m_curGameTypeIdx]; }

std::string Settings::getMusicPath() const { return MUSIC_TYPE[m_curMusicTypeIdx].path; }

std::string Settings::getRecordName(int order) const {
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_A && order >= 0 && order <= RECORD_A.size()) {
        return RECORD_A[order].name;
    }
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_B && order >= 0 && order <= RECORD_B.size()) {
        return RECORD_B[order].name;
    }
    return "";
}

int Settings::getRecordScore(int order) const {
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_A && order >= 0 && order <= RECORD_A.size()) {
        return RECORD_A[order].score;
    }
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_B && order >= 0 && order <= RECORD_B.size()) {
        return RECORD_B[order].score;
    }
    return 0;
}

int Settings::getRecordLv(int order) const {
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_A && order >= 0 && order <= RECORD_A.size()) {
        return RECORD_A[order].lv;
    }
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_B && order >= 0 && order <= RECORD_B.size()) {
        return RECORD_B[order].lv;
    }
    return 0;
}