/**
 * @file image.cpp
 * @brief 图片组件实现
 */
#include "core/graphics/image.h"
#include "manager/resourcemanager.h"

/**
 * @brief 构造并加载一张图片
 */
Image::Image(ResourceManager& resourceMgr, SDL_Renderer* renderer, std::string_view path, std::optional<SDL_Rect> rect)
    : m_active(true)
    , m_renderer(renderer) {
    SetTexture(resourceMgr, path, rect);
}

/**
 * @brief 设置可见性
 * @param active 是否可见
 */
void Image::SetActive(bool active) {
    m_active = active;
}

/**
 * @brief 替换纹理，并根据源矩形参数确定绘制尺寸
 */
void Image::SetTexture(ResourceManager& resourceMgr, std::string_view path, std::optional<SDL_Rect> rect) {
    m_texture = resourceMgr.GetImage(path);
    m_rect = {};
    if (m_texture) {
        if (!rect.has_value()) {
            SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h);
        } else {
            m_rect = rect.value();
        }
    }
}

/**
 * @brief 渲染图片（仅当可见时）
 */
void Image::OnRender(const MySDL::RenderParams& params) {
    if (m_active) {
        MySDL::RenderTexture(m_renderer, m_texture, m_rect, params);
    }
}