#pragma once

#include <array>
#include <SDL.h>

/**
 * @brief 输入管理器类，用于管理游戏中的输入状态
 *
 * 使用单例模式，保证全局唯一实例
 */
class InputManager {
private:
    std::array<bool, SDL_NUM_SCANCODES> m_preKey;   // 上一帧按键状态
    std::array<bool, SDL_NUM_SCANCODES> m_curKey;   // 当前帧按键状态

public:
    /**
     * @brief 获取输入管理器单例
     * @return InputManager& 全局唯一实例
     */
    static InputManager& getInstance();

    // 禁用拷贝与移动
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    InputManager(InputManager&&) = delete;
    InputManager& operator=(InputManager&&) = delete;

    /**
     * @brief 每帧开始时调用，更新上一帧输入状态
     */
    void beginFrame();
    /**
     * @brief 处理 SDL 事件，更新当前输入状态
     * @param event SDL_Event 事件对象
     */
    void processEvent(const SDL_Event& event);

    /**
     * @brief 检查按键是否按下
     * @param key SDL_Scancode 按键扫描码
     * @return bool 当前帧按下返回 true ，否则返回 false
     */
    bool isKeyPressed(SDL_Scancode key) const;
    /**
     * @brief 检查按键是否刚刚按下（上一帧未按下，当前帧按下）
     * @param key SDL_Scancode 按键扫描码
     * @return bool 刚刚按下返回 true ，否则返回 false
     */
    bool isKeyJustPressed(SDL_Scancode key) const;
    /**
     * @brief 检查按键是否刚刚松开（上一帧按下，当前帧未按下）
     * @param key SDL_Scancode 按键扫描码
     * @return bool 刚刚松开返回 true ，否则返回 false
     */
    bool isKeyReleased(SDL_Scancode key) const;

private:
    InputManager();             // 私有构造函数
    ~InputManager() = default;  // 私有析构函数
};