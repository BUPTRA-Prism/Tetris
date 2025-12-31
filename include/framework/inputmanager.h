#pragma once

#include <array>
#include <SDL.h>

class InputManager {
private:
    std::array<bool, SDL_NUM_SCANCODES> m_preKey;
    std::array<bool, SDL_NUM_SCANCODES> m_curKey;

public:
    InputManager();
    ~InputManager() = default;

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    InputManager(InputManager&&) = delete;
    InputManager& operator=(InputManager&&) = delete;

    void beginFrame();
    void processEvent(const SDL_Event& event);

    bool isKeyPressed(SDL_Scancode key) const;
    bool isKeyJustPressed(SDL_Scancode key) const;
    bool isKeyReleased(SDL_Scancode key) const;
};