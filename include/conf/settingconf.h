#pragma once

#include <vector>
#include <string>

inline const std::string SINGLE_PLAYER_MODE = "1 PLAYER";
inline const std::string DOUBLE_PLAYER_MODE = "2 PLAYER";
inline const std::string COOPERATIVE_MODE = "COOPERATIVE";
inline const std::string VERSUS_COMPUTER_MODE = "VERSUS COMPUTER";
inline const std::string WITH_COMPUTER_MODE = "WITH COMPUTER";

inline const std::string SILENCE = "SILENCE";

inline const std::vector<std::string> MODE_OPTIONS = {
    SINGLE_PLAYER_MODE,
    DOUBLE_PLAYER_MODE,
    COOPERATIVE_MODE,
    VERSUS_COMPUTER_MODE,
    WITH_COMPUTER_MODE
};
inline const std::vector<int> LEVEL_OPTIONS = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
inline const std::vector<int> HANDICAP_OPTIONS = { 0, 3, 6, 9, 12 };
inline const std::vector<std::string> MUSIC_OPTIONS = {
    SILENCE,
    "KOROBEINIKI",
    "KARINKA",
    "TROIKA"
};
