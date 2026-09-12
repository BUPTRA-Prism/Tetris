/**
 * @file image.h
 * @brief 图片组件，封装单张纹理的加载与渲染
 */
#pragma once

#include "mysdl/render.h"
#include <optional>
#include <string_view>
#include <SDL2/SDL_rect.h>

class ResourceManager;

/**
 * @brief 图片组件，持有纹理并支持按参数渲染
 */
class Image {
private:
    bool m_active;              ///< 是否可见
    SDL_Renderer* m_renderer;   ///< 渲染器
    SDL_Texture* m_texture;     ///< 纹理
    SDL_Rect m_rect;            ///< 源矩形

public:
    /**
     * @brief 构造并加载一张图片
     * @param resourceMgr 资源管理器
     * @param renderer 渲染器
     * @param path 图片资源路径
     * @param rect 可选的源矩形，缺省时按纹理尺寸
     */
    Image(const ResourceManager& resourceMgr, SDL_Renderer* renderer, std::string_view path, std::optional<SDL_Rect> rect = std::nullopt);
    ~Image() = default;

    /**
     * @brief 设置可见性
     * @param active 是否可见
     */
    void SetActive(bool active);

    /**
     * @brief 替换纹理
     * @param resourceMgr 资源管理器
     * @param path 图片资源路径
     * @param rect 可选的源矩形，缺省时按纹理尺寸
     */
    void SetTexture(const ResourceManager& resourceMgr, std::string_view path, std::optional<SDL_Rect> rect = std::nullopt);

    /**
     * @brief 渲染图片
     * @param params 渲染参数
     */
    void OnRender(const MySDL::RenderParams& params = {});
};