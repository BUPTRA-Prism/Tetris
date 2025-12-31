#pragma once

class Settings {
private:
    int m_modeIdx;
    int m_levelIdx;
    int m_handicapIdx;
    int m_musicIdx;

public:
    Settings();
    ~Settings() = default;

    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;

    int getModeIdx() const;
    int getLevelIdx() const;
    int getHandicapIdx() const;
    int getMusicIdx() const;

    void setModeIdx(int delta);
    void setLevelIdx(int delta);
    void setHandicapIdx(int delta);
    void setMusicIdx(int delta);
};