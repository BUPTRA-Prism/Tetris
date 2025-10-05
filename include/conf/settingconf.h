#pragma once

#include "conf/resourceconf.h"

#include <array>
#include <string>
#include <vector>

// 音乐选项结构体
struct MusicOption {
    std::string name;   // 选项名
    std::string path;   // 音乐文件名
};

// 纪录结构体
struct Record {
    std::string name;   // 姓名
    int score;          // 分数
    int lv;             // 等级
};

inline const std::string GAME_TYPE_A = "A-TYPE";    // 游戏模式 A
inline const std::string GAME_TYPE_B = "B-TYPE";    // 游戏模式 B
inline const std::vector<std::string> GAME_TYPE = { GAME_TYPE_A, GAME_TYPE_B }; // 游戏模式选项
// 音乐选项
inline const std::vector<MusicOption> MUSIC_TYPE = {
    {"MUSIC  1", BGM1_MUSIC_PATH}, 
    {"MUSIC  2", BGM2_MUSIC_PATH}, 
    {"MUSIC  3", BGM3_MUSIC_PATH},
    {"  OFF", ""}
};
inline const int MAX_INIT_LEVEL = 9;     // 最大初始等级
inline const int MAX_INIT_HEIGHT = 5;    // 最大初始高度
inline const int RECORD_COUNT = 3;       // 纪录数量
// A模式排行榜
inline std::array<Record, RECORD_COUNT> RECORD_A = {
    Record { "HOWARD", 10000, 9 },
    Record { "OTASAN", 7500, 5 },
    Record { "LANCE", 5000, 0 }
};
// B模式排行榜
inline std::array<Record, RECORD_COUNT> RECORD_B = {
    Record { "ALEX", 2000, 9 },
    Record { "TONY", 1000, 5 },
    Record { "NINTEN", 500, 0 }
};

inline const int RECORD_NAME_MAX_LEN = 6;
inline const int RECORD_SCORE_MAX_LEN = 6;
inline const int RECORD_LV_MAX_LEN = 2;