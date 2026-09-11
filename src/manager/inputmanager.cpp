/**
 * @file inputmanager.cpp
 * @brief 输入管理器实现
 */
#include "manager/inputmanager.h"

/**
 * @brief 构造并将按键状态清零
 */
InputManager::InputManager() {
    m_preKey.fill(false);
    m_curKey.fill(false);
}

/**
 * @brief 帧开始，将当前状态滚动为上一帧状态
 */
void InputManager::BeginFrame() {
    m_preKey = m_curKey;
}

/**
 * @brief 处理单个 SDL 事件以更新按键状态
 *
 * 窗口失焦时清空当前按键状态，避免切换窗口后按键被持续判定为按下
 */
void InputManager::ProcessEvent(const SDL_Event& event) {
    switch(event.type) {
        case SDL_WINDOWEVENT: {
            if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                m_curKey.fill(false);
            }
            break;
        }
        case SDL_KEYDOWN: {
            m_curKey[event.key.keysym.scancode] = true;
            break;
        }
        case SDL_KEYUP: {
            m_curKey[event.key.keysym.scancode] = false;
            break;
        }
        default: break;
    }
}

/**
 * @brief 判断按键当前是否被按住
 */
bool InputManager::IsKeyDown(SDL_Scancode key) const noexcept {
    return m_curKey[key];
}

/**
 * @brief 判断按键是否在本帧刚按下
 */
bool InputManager::IsKeyPressed(SDL_Scancode key) const noexcept {
    return !m_preKey[key] && m_curKey[key];
}

/**
 * @brief 判断按键是否在本帧刚释放
 */
bool InputManager::IsKeyReleased(SDL_Scancode key) const noexcept {
    return m_preKey[key] && !m_curKey[key];
}