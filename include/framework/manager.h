/**
 * @file manager.h
 * @brief 管理器集合结构，聚合各子系统管理器引用
 */
#pragma once

class ResourceManager;
class AudioManager;
class InputManager;

/**
 * @brief 管理器集合，作为依赖注入容器聚合各管理器
 */
struct Manager {
    ResourceManager& resourceMgr; ///< 资源管理器
    AudioManager& audioMgr;       ///< 音频管理器
    InputManager& inputMgr;       ///< 输入管理器
};