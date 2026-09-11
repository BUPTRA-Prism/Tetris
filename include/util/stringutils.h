/**
 * @file stringutils.h
 * @brief 字符串工具函数
 */
#pragma once

#include <string>

namespace Util {
    /**
     * @brief 将整数转换为定长字符串，不足位数前补零
     * @param num 整数
     * @param digits 目标位数
     * @return 定长字符串；数字位数超过 target 时返回完整数字
     */
    std::string Int2String(int num, int digits);
}