/**
 * @file basic.h
 * @brief 基础配置，定义窗口标题、分辨率与帧时长等全局常量
 */
#pragma once

#include <string_view>

namespace Config {
    /**
     * @brief 基础配置常量集合
     */
    namespace Basic {
        /** @brief 窗口标题 */
        constexpr std::string_view WINDOW_TITLE = "Tetris";
        /** @brief 窗口宽度（像素） */
        constexpr int WINDOW_WIDTH = 1024;
        /** @brief 窗口高度（像素） */
        constexpr int WINDOW_HEIGHT = 896;
        /** @brief 单帧目标时长（毫秒），约合 60 FPS */
        constexpr unsigned int FRAME_TIME = 16;
    }
}