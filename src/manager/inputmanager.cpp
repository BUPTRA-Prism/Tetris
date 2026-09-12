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
 * @brief 设置单个按键的按下状态
 */
void InputManager::SetKeyState(SDL_Scancode key, bool down) {
    m_curKey[key] = down;
}

/**
 * @brief 清空全部按键状态（窗口失焦时由 main 调用）
 */
void InputManager::ResetKeys() {
    m_curKey.fill(false);
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