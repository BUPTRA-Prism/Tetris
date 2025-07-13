#pragma once

#include <string>
#include <vector>

class Settings {
private:
    std::vector<std::string> m_musicType;
    int m_curGameType;
    int m_curLevel;
    int m_curHeight;
    int m_curMusicTypeIdx;

public:
    static Settings& getInstance();

    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;

    bool setGameType(int delta);
    bool setLevel(int delta);
    bool setHeight(int delta);
    bool setMusicType(int delta);

    int getGameType() const;
    int getLevel() const;
    int getHeight() const;
    int getMusicTypeIdx() const;
    std::string getMusicType() const;

private:
    Settings();
    ~Settings() = default;
};