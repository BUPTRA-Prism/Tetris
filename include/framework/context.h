/**
 * @file context.h
 * @brief 全局上下文结构，作为纯依赖注入容器聚合各服务与共享数据
 */
#pragma once

class Manager;
class Game;

struct SDL_Renderer;

/**
 * @brief 全局上下文，聚合管理器集合、游戏共享数据与渲染器
 */
struct Context {
    Manager& manager;       ///< 管理器集合
    Game& game;             ///< 游戏共享数据
    SDL_Renderer* renderer; ///< SDL 渲染器
};