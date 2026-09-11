/**
 * @file inputmanager.h
 * @brief 输入管理器，缓存键盘状态并提供按下/释放查询
 */
#pragma once

#include <array>
#include <SDL2/SDL.h>

/**
 * @brief 输入管理器，维护上一帧与当前帧的键盘状态
 */
class InputManager {
private:
    std::array<bool, SDL_NUM_SCANCODES> m_preKey; ///< 上一帧按键状态
    std::array<bool, SDL_NUM_SCANCODES> m_curKey; ///< 当前帧按键状态

public:
    /** @brief 构造并将按键状态清零 */
    InputManager();
    ~InputManager() = default;

    InputManager(const InputManager& manager) = delete;
    InputManager& operator=(const InputManager& manager) = delete;
    InputManager(InputManager&& manager) = delete;
    InputManager& operator=(InputManager&& manager) = delete;

    /** @brief 帧开始，将当前状态滚动为上一帧状态 */
    void BeginFrame();
    /**
     * @brief 处理单个 SDL 事件以更新按键状态
     * @param event SDL 事件
     */
    void ProcessEvent(const SDL_Event& event);

    /**
     * @brief 判断按键当前是否被按住
     * @param key 扫描码
     * @return 按住返回 true
     */
    bool IsKeyDown(SDL_Scancode key) const noexcept;
    /**
     * @brief 判断按键是否在本帧刚按下
     * @param key 扫描码
     * @return 本帧刚按下返回 true
     */
    bool IsKeyPressed(SDL_Scancode key) const noexcept;
    /**
     * @brief 判断按键是否在本帧刚释放
     * @param key 扫描码
     * @return 本帧刚释放返回 true
     */
    bool IsKeyReleased(SDL_Scancode key) const noexcept;
};