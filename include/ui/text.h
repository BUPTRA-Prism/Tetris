#pragma once

#include "core/context.h"
#include "ui/layout.h"
#include <SDL.h>
#include <string>
#include <vector>

/**
 * @brief 文本类
 *
 * 封装 SDL 文本绘制逻辑，包括文本内容、位置、颜色等属性。
 */
class Text {
private:
    Context& m_ctx;     // 全局上下文
    std::string m_str;  // 文本内容
    SDL_Color m_color;  // 文本颜色

    std::unique_ptr<HorizontalLayout> m_layout; // 文本布局

public:
    /**
     * @brief 构造函数
     * @param ctx 全局上下文
     * @param str 文本内容
     * @param pos 文本位置
     * @param color 文本颜色（默认白色）
     */
    Text(Context& ctx, const std::string& str, SDL_Point pos, SDL_Color color = {255, 255, 255, 255});
    ~Text() = default;  // 析构函数

    /**
     * @brief 设置文本内容
     * @param str 新文本内容
     */
    void setStr(const std::string& str);
    /**
     * @brief 设置文本位置
     * @param pos 新位置
     */
    void setPos(SDL_Point pos);
    /**
     * @brief 设置文本颜色
     * @param color 新颜色
     */
    void setColor(SDL_Color color);

    /**
     * @brief 渲染文本到屏幕
     */
    void onRender();

    /**
     * @brief 获取文本布局
     * @return HorizontalLayout* 文本布局指针
     */
    HorizontalLayout* getLayout() const;
};