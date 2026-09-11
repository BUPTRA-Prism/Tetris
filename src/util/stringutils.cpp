/**
 * @file stringutils.cpp
 * @brief 字符串工具函数实现
 */
#include "util/stringutils.h"
#include <array>
#include <charconv>

/**
 * @brief 将整数转换为定长字符串，不足位数前补零
 *
 * 使用 std::to_chars 避免分配，数字位数未超 target 时在高位补零
 */
std::string Util::Int2String(int num, int digits) {
    std::array<char, 32> buffer;

    auto result = std::to_chars(buffer.data(), buffer.data() + buffer.size(), num);
    
    if (result.ec != std::errc()) return std::string(digits, '0');
    
    int len = static_cast<int>(result.ptr - buffer.data());
    if (len >= digits) {
        return std::string(buffer.data(), len);
    }
    
    std::string str(digits, '0');
    std::copy(buffer.data(), result.ptr, str.begin() + (digits - len));
    return str;
}