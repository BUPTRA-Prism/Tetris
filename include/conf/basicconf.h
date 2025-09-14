#pragma once

#include <string>

/* 屏幕相关配置 */
inline const int SCREEN_WIDTH = 1024;               // 窗口宽度（像素）
inline const int SCREEN_HEIGHT = 896;               // 窗口高度（像素）
inline const std::string SCREEN_TITLE = "Tetris";   // 窗口标题
inline const int MSPF = 16;                         // 每帧延迟时间（ms）

/* 字体渲染配置 */
inline const int FONT_SIZE = 28;    // 字符大小（像素）
inline const int FONT_SPACING = 4;  // 字符间隔（像素）