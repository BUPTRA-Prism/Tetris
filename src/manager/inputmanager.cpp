#include "manager/inputmanager.h"

InputManager::InputManager() {
    // 初始化按键状态数组为全false
    m_preKey.fill(false);
    m_curKey.fill(false);
}

void InputManager::beginFrame() {
    // 每帧开始时，将当前帧状态保存到上一帧
    m_preKey = m_curKey;
}

void InputManager::processEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            // 按键按下且不是重复事件，更新当前帧状态
            if (!event.key.repeat) {
                m_curKey[event.key.keysym.scancode] = true;
            }
            break;
        }
        case SDL_KEYUP: {
            // 按键释放，更新当前帧状态
            m_curKey[event.key.keysym.scancode] = false;
            break;
        }
        default: break;
    }
}

bool InputManager::isKeyPressed(SDL_Scancode key) const {
    // 当前帧按下
    return m_curKey[key];
}

bool InputManager::isKeyJustPressed(SDL_Scancode key) const {
    // 当前帧按下且上一帧未按下
    return m_curKey[key] && !m_preKey[key];
}

bool InputManager::isKeyReleased(SDL_Scancode key) const {
    // 当前帧未按下且上一帧按下
    return !m_curKey[key] && m_preKey[key];
}