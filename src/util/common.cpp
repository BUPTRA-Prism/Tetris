#include "util/common.h"
#include <random>

int getRandomInt(int min, int max) {
    // 使用静态变量，只初始化一次
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis;
    
    // 每次调用时使用相同的生成器，但重新设置分布范围
    return dis(gen, std::uniform_int_distribution<>::param_type(min, max));
}

void padLeft(std::string& str, int maxLen, char ch) {
    if (str.length() < maxLen) {
        str = std::string(maxLen - str.length(), ch) + str;
    }
}