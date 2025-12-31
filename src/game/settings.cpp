#include "game/settings.h"
#include "conf/settingconf.h"

Settings::Settings()
    : m_modeIdx(0)
    , m_levelIdx(0)
    , m_handicapIdx(0)
    , m_musicIdx(0) {}

int Settings::getModeIdx() const { return m_modeIdx; }

int Settings::getLevelIdx() const { return m_levelIdx; }

int Settings::getHandicapIdx() const { return m_handicapIdx; }

int Settings::getMusicIdx() const { return m_musicIdx; }

void Settings::setModeIdx(int delta) { 
    m_modeIdx = (m_modeIdx + delta + MODE_OPTIONS.size()) % MODE_OPTIONS.size(); 
}

void Settings::setLevelIdx(int delta) { 
    m_levelIdx = (m_levelIdx + delta + LEVEL_OPTIONS.size()) % LEVEL_OPTIONS.size(); 
}

void Settings::setHandicapIdx(int delta) { 
    m_handicapIdx = (m_handicapIdx + delta + HANDICAP_OPTIONS.size()) % HANDICAP_OPTIONS.size(); 
}

void Settings::setMusicIdx(int delta) { 
    m_musicIdx = (m_musicIdx + delta + MUSIC_OPTIONS.size()) % MUSIC_OPTIONS.size(); 
}