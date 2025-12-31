#include "framework/inputmanager.h"

InputManager::InputManager() {
    m_preKey.fill(false);
    m_curKey.fill(false);
}

void InputManager::beginFrame() {
    m_preKey = m_curKey;
}

void InputManager::processEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_KEYDOWN: {
            if (!event.key.repeat) {
                m_curKey[event.key.keysym.scancode] = true;
            }
            break;
        }
        case SDL_KEYUP: {
            m_curKey[event.key.keysym.scancode] = false;
            break;
        }
        default: break;
    }
}

bool InputManager::isKeyPressed(SDL_Scancode key) const {
    return m_curKey[key];
}

bool InputManager::isKeyJustPressed(SDL_Scancode key) const {
    return m_curKey[key] && !m_preKey[key];
}

bool InputManager::isKeyReleased(SDL_Scancode key) const {
    return !m_curKey[key] && m_preKey[key];
}