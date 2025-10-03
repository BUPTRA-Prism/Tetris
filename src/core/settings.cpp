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
    , m_curHeight(0)
    , m_newRecordOrder(RECORD_COUNT) {}

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

void Settings::insertRecord(int score, int lv) {
    int idx = RECORD_COUNT - 1;
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_A) {
        for (; idx >= 0; --idx) {
            if (RECORD_A[idx].score > score || 
                (RECORD_A[idx].score == score && RECORD_A[idx].lv > lv)) {
                break;
            }
        }
        if (idx != RECORD_COUNT - 1) {
            for (int i = RECORD_COUNT - 1; i > idx + 1; --i) {
                RECORD_A[i] = RECORD_A[i - 1];
            }
            RECORD_A[idx + 1] = Record { RECORD_DEFAULT_NAME, score, lv };
        }
    }
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_B) {
        for (; idx >= 0; --idx) {
            if (RECORD_B[idx].score > score || 
                (RECORD_B[idx].score == score && RECORD_B[idx].lv > lv)) {
                break;
            }
        }
        if (idx != RECORD_COUNT - 1) {
            for (int i = RECORD_COUNT - 1; i > idx + 1; --i) {
                RECORD_B[i] = RECORD_B[i - 1];
            }
            RECORD_B[idx + 1] = Record { RECORD_DEFAULT_NAME, score, lv };
        }
    }
    m_newRecordOrder = idx + 1;
}

void Settings::updateRecordName(std::string name) {
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_A) {
        RECORD_A[m_newRecordOrder].name = name;
    }
    if (GAME_TYPE[m_curGameTypeIdx] == GAME_TYPE_B) {
        RECORD_B[m_newRecordOrder].name = name;
    }
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

int Settings::getNewRecordOrder() const { return m_newRecordOrder; }