/**
 * @file text.h
 * @brief 文本组件，封装字符串到纹理的转换与渲染
 */
#pragma once

#include "mysdl/render.h"
#include "config/resource.h"
#include <string_view>
#include <SDL2/SDL_rect.h>

class ResourceManager;

/**
 * @brief 文本组件，将字符串渲染为纹理供场景复用
 */
class Text {
private:
    bool m_active;                  ///< 是否可见
    TTF_Font* m_font;               ///< 字体
    SDL_Renderer* m_renderer;       ///< 渲染器
    MySDL::UniqueTexture m_texture; ///< 文本纹理
    SDL_Rect m_rect;                ///< 源矩形

public:
    /**
     * @brief 构造并生成文本纹理
     * @param resourceMgr 资源管理器
     * @param renderer 渲染器
     * @param str 文本内容
     * @param fontPath 字体资源路径
     */
    Text(const ResourceManager& resourceMgr, SDL_Renderer* renderer, std::string_view str, std::string_view fontPath = Resource::Font::DEFAULT_FONT);
    ~Text() = default;

    /**
     * @brief 设置可见性
     * @param active 是否可见
     */
    void SetActive(bool active);

    /**
     * @brief 更新文本内容并重新生成纹理
     * @param str 新的文本内容
     */
    void SetStr(std::string_view str);

    /**
     * @brief 渲染文本
     * @param params 渲染参数
     */
    void OnRender(const MySDL::RenderParams& params);
};