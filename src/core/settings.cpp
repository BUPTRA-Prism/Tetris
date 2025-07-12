#include "core/settings.h"
#include "conf/resourceconf.h"
#include "conf/settingconf.h"

Settings& Settings::getInstance() {
    static Settings instance;
    return instance;
}

Settings::Settings()
    : m_musicType({ BGM1_MUSIC_PATH, BGM2_MUSIC_PATH, BGM3_MUSIC_PATH, "" })
    , m_curGameType(0)
    , m_curLevel(0)
    , m_curHeight(0)
    , m_curMusicTypeIdx(0) {}

bool Settings::setGameType(int delta) {
    if (m_curGameType + delta >= 0 && m_curGameType + delta < GAME_TYPE_COUNT) {
        m_curGameType += delta;
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

bool Settings::setMusicType(int delta) {
    if (m_curMusicTypeIdx + delta >= 0 && m_curMusicTypeIdx + delta < m_musicType.size()) {
        m_curMusicTypeIdx += delta;
        return true;
    }
    return false;
}

int Settings::getGameType() const { return m_curGameType; }

int Settings::getLevel() const { return m_curLevel; }

int Settings::getHeight() const { return m_curHeight; }

std::string Settings::getMusicType() const { return m_musicType[m_curMusicTypeIdx]; }