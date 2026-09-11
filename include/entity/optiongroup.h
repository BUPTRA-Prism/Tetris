/**
 * @file optiongroup.h
 * @brief 选项组组件，组合标题、选项文本与选项图标
 */
#pragma once

#include "core/graphics/text.h"
#include "entity/optionicon.h"
#include <memory>
#include <string_view>
#include <vector>
#include <SDL2/SDL.h>

class ResourceManager;

/**
 * @brief 选项组，管理一组文本选项与一个可移动图标
 */
class OptionGroup {
public:
    /**
     * @brief 图标相对选项的布局信息
     */
    struct IconLayout {
        int offsetX;        ///< X 偏移
        int offsetY;        ///< Y 偏移
        bool flip = false;  ///< 是否水平翻转
    };

    /**
     * @brief 文本选项描述
     */
    struct TextSpec {
        std::string_view str;                    ///< 文本内容
        SDL_Point pos;                           ///< 绘制位置
        SDL_Color color = { 255, 255, 255, 255 }; ///< 颜色
    };

private:
    /**
     * @brief 内部文本条目
     */
    struct TextItem {
        std::unique_ptr<Text> text; ///< 文本组件
        SDL_Point pos;              ///< 绘制位置
        SDL_Color color;            ///< 颜色
    };

    TextItem m_title;                     ///< 标题
    std::vector<TextItem> m_options;      ///< 选项文本列表
    std::unique_ptr<OptionIcon> m_icon;   ///< 选项图标
    std::vector<IconLayout> m_iconLayout; ///< 图标布局列表

public:
    /**
     * @brief 构造选项组
     * @param resourceMgr 资源管理器
     * @param renderer 渲染器
     * @param titleSpec 标题描述
     * @param optionSpec 选项文本描述列表
     * @param iconPath 图标资源路径
     * @param iconLayout 图标布局列表
     */
    OptionGroup(
        ResourceManager& resourceMgr,
        SDL_Renderer* renderer,
        TextSpec titleSpec,
        std::vector<TextSpec> optionSpec,
        std::string_view iconPath,
        std::vector<IconLayout> iconLayout
    );
    ~OptionGroup() = default;

    /** @brief 更新选项组动画 */
    void OnUpdate();
    /** @brief 渲染标题 */
    void RenderTitle();
    /** @brief 渲染全部选项文本 */
    void RenderOptions();
    /**
     * @brief 在指定选项上渲染图标
     * @param idx 选项下标
     */
    void RenderIcons(int idx);

    /** @brief 播放图标动画 */
    void PlayIconAnim();
    /** @brief 停止图标动画 */
    void StopIconAnim();
};