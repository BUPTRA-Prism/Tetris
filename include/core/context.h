#pragma once

#include "manager/audiomanager.h"
#include "manager/inputmanager.h"
#include "manager/resourcemanager.h"
#include "core/settings.h"

/**
 * @brief 全局上下文结构体
 *
 * 保存各个管理器、游戏设置数据和 SDL_Renderer 的引用，用于在游戏各模块间统一访问资源、音频、输入和设置
 */
struct Context {
    ResourceManager& resourceManager;   // 资源管理器引用
    AudioManager& audioManager;         // 音频管理器引用
    InputManager& inputManager;         // 输入管理器引用
    Settings& settings;                 // 设置数据引用
    SDL_Renderer* renderer;             // SDL 渲染器指针

    /**
     * @brief 构造函数，初始化上下文
     * @param rm 资源管理器引用
     * @param am 音频管理器引用
     * @param im 输入管理器引用
     * @param s 设置数据引用
     * @param rdr SDL 渲染器指针
     */
    Context(ResourceManager& rm, AudioManager& am, InputManager& im, Settings& s, SDL_Renderer* rdr);
};