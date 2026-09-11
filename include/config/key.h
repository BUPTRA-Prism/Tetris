/**
 * @file key.h
 * @brief 按键映射配置，定义各操作对应的 SDL 扫描码
 */
#pragma once

#include <SDL2/SDL_scancode.h>

namespace Config {
    /**
     * @brief 按键配置常量集合
     */
    namespace Key {
        /** @brief 进入下一场景按键 */
        constexpr SDL_Scancode NEXT_SCENE_KEY = SDL_SCANCODE_RETURN;
        /** @brief 返回上一场景按键 */
        constexpr SDL_Scancode LAST_SCENE_KEY = SDL_SCANCODE_ESCAPE;
        /** @brief 切换选项按键 */
        constexpr SDL_Scancode CHANGE_OPTION_KEY = SDL_SCANCODE_I;
        /** @brief 暂停按键 */
        constexpr SDL_Scancode PAUSE_KEY = SDL_SCANCODE_SPACE;
        /** @brief 上方向按键 */
        constexpr SDL_Scancode UP_KEY = SDL_SCANCODE_W;
        /** @brief 下方向按键 */
        constexpr SDL_Scancode DOWN_KEY = SDL_SCANCODE_S;
        /** @brief 左方向按键 */
        constexpr SDL_Scancode LEFT_KEY = SDL_SCANCODE_A;
        /** @brief 右方向按键 */
        constexpr SDL_Scancode RIGHT_KEY = SDL_SCANCODE_D;
        /** @brief 顺时针旋转按键 */
        constexpr SDL_Scancode ROTATE_CW_KEY = SDL_SCANCODE_J;
        /** @brief 逆时针旋转按键 */
        constexpr SDL_Scancode ROTATE_CCW_KEY = SDL_SCANCODE_K;
    }
}