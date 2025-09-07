#pragma once

#include "conf/resourceconf.h"

#include <string>
#include <vector>

// 音乐选项结构体
struct MusicOption {
    std::string name;   // 选项名
    std::string path;   // 音乐文件名
};

inline const std::string GAME_TYPE_A = "A-TYPE";    // 游戏模式 A
inline const std::string GAME_TYPE_B = "B-TYPE";    // 游戏模式 B
inline const std::vector<std::string> GAME_TYPE = { GAME_TYPE_A, GAME_TYPE_B }; // 游戏模式选项
// 音乐选项
inline const std::vector<MusicOption> MUSIC_TYPE = {
    {"MUSIC  1", BGM1_MUSIC_PATH}, 
    {"MUSIC  2", BGM2_MUSIC_PATH}, 
    {"MUSIC  3", BGM3_MUSIC_PATH},
    {"OFF", ""}
};
inline const int MAX_LEVEL = 9;     // 最大初始关卡
inline const int MAX_HEIGHT = 5;    // 最大启示高度