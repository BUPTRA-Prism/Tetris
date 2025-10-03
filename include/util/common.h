#pragma once

#include <string>
#include <vector>

int getRandomInt(int min, int max);

std::vector<int> getRandomIntList(int min, int max, int count);

void padLeft(std::string& str, int maxLen, char ch);