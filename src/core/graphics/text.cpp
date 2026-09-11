/**
 * @file text.cpp
 * @brief 文本组件实现
 */
#include "core/graphics/text.h"
#include "manager/resourcemanager.h"

/**
 * @brief 构造并生成文本纹理
 */
Text::Text(ResourceManager& resourceMgr, SDL_Renderer* renderer, std::string_view str, std::string_view fontPath)
    : m_active(true)
    , m_font(resourceMgr.GetFont(fontPath))
    , m_renderer(renderer) {
    SetStr(str);
}

/**
 * @brief 设置可见性
 * @param active 是否可见
 */
void Text::SetActive(bool active) {
    m_active = active;
}

/**
 * @brief 更新文本内容并重新生成纹理
 */
void Text::SetStr(std::string_view str) {
    m_texture = MySDL::Font2Texture(m_renderer, m_font, str);
    m_rect = {};
    if (m_texture) {
        SDL_QueryTexture(m_texture.get(), nullptr, nullptr, &m_rect.w, &m_rect.h);
    } else {
        m_rect = {};
    }
}

/**
 * @brief 渲染文本（仅当可见时）
 */
void Text::OnRender(const MySDL::RenderParams& params) {
    if (m_active) {
        MySDL::RenderTexture(m_renderer, m_texture.get(), m_rect, params);
    }
}