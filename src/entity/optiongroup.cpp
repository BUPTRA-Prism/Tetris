/**
 * @file optiongroup.cpp
 * @brief 选项组实现
 */
#include "entity/optiongroup.h"
#include <utility>

/**
 * @brief 构造选项组，构建标题、选项文本与图标
 */
OptionGroup::OptionGroup(
    const ResourceManager& resourceMgr,
    SDL_Renderer* renderer,
    TextSpec titleSpec, 
    std::vector<TextSpec> optionSpec, 
    std::string_view iconPath,
    std::vector<IconLayout> iconLayout
) {
    m_title = TextItem{
        std::make_unique<Text>(resourceMgr, renderer, titleSpec.str),
        titleSpec.pos,
        titleSpec.color
    };

    m_options.resize(optionSpec.size());
    for (size_t i = 0; i < optionSpec.size(); ++i) {
        m_options[i] = TextItem{
            std::make_unique<Text>(resourceMgr, renderer, optionSpec[i].str),
            optionSpec[i].pos,
            optionSpec[i].color
        };
    }

    m_icon = std::make_unique<OptionIcon>(resourceMgr, renderer, iconPath);
    m_iconLayout = std::move(iconLayout);
}

/** @brief 更新图标动画 */
void OptionGroup::OnUpdate() {
    m_icon->OnUpdate();
}

/** @brief 渲染标题 */
void OptionGroup::RenderTitle() {
    m_title.text->OnRender(MySDL::RenderParams{ m_title.pos, m_title.color });
}

/** @brief 渲染全部选项文本 */
void OptionGroup::RenderOptions() {
    for(auto& option: m_options) {
        option.text->OnRender(MySDL::RenderParams{ option.pos, option.color });
    }
}

/**
 * @brief 在指定选项上按布局列表渲染图标
 * @param idx 选项下标
 */
void OptionGroup::RenderIcons(int idx) {
    if (idx >= 0 && idx < static_cast<int>(m_options.size())) {
        for (auto& layout: m_iconLayout) {
            m_icon->OnRender(MySDL::RenderParams{
                SDL_Point{
                    m_options[idx].pos.x + layout.offsetX,
                    m_options[idx].pos.y + layout.offsetY
                },
                SDL_Color{ 255, 255, 255, 255 },
                layout.flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
            });
        }
    }
}

/** @brief 播放图标动画 */
void OptionGroup::PlayIconAnim() {
    m_icon->PlayAnim();
}

/** @brief 停止图标动画 */
void OptionGroup::StopIconAnim() {
    m_icon->StopAnim();
}