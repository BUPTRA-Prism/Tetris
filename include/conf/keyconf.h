#pragma once

#include <SDL.h>

/* 场景切换键 */
inline const SDL_Scancode NEXT_SCENE_KEY = SDL_SCANCODE_RETURN;     // 前往下一场景 - Enter
inline const SDL_Scancode ABOVE_SCENE_KEY = SDL_SCANCODE_ESCAPE;    // 返回上一场景 - ESC
inline const SDL_Scancode PAUSE_KEY = SDL_SCANCODE_SPACE;           // 暂停键 - Space

/* 移动键 */
inline const SDL_Scancode LEFT_KEY = SDL_SCANCODE_A;    // 左 - A
inline const SDL_Scancode RIGHT_KEY = SDL_SCANCODE_D;   // 右 - D
inline const SDL_Scancode UP_KEY = SDL_SCANCODE_W;      // 上 - W
inline const SDL_Scancode DOWN_KEY = SDL_SCANCODE_S;    // 下 - S

/* 旋转键 */
inline const SDL_Scancode LEFT_ROTATE_KEY = SDL_SCANCODE_J;     // 逆时针旋转 - J
inline const SDL_Scancode RIGHT_ROTATE_KEY = SDL_SCANCODE_L;    // 顺时针旋转 - L