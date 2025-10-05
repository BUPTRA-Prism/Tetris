#pragma once

#include <string>
#include <vector>

/**
    * @brief 在指定范围内获取单个随机数
    * @param min 随机数下限
    * @param max 随机数上限
    * @return int 随机数（包括上下限）
*/
int getRandomInt(int min, int max);

/**
    * @brief 在指定范围内获取若干随机数
    * @param min 随机数下限
    * @param max 随机数上限
    * @param count 获取随机数个数
    * @param std::vector<int> 随机数列表（包括上下限）
*/
std::vector<int> getRandomIntList(int min, int max, int count);

/**
    * @brief 字符串左侧占位
    * @param str 源字符串
    * @param maxLen 占位后长度
    * @param ch 占位字符
*/
void padLeft(std::string& str, int maxLen, char ch);