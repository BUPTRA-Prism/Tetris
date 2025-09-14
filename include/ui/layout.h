#pragma once

#include <SDL.h>

/**
 * @brief 网格布局类，提供基于行列的位置计算
 * 
 * 用于将UI元素按照网格方式排列，支持自定义行间距和列间距
 */
class GridLayout {
protected:
    SDL_Point m_pos;    // 布局起始位置（左上角坐标）
    int m_rowSpacing;   // 行间距
    int m_colSpacing;   // 列间距

public:
    /**
     * @brief 构造函数
     * @param pos 布局起始位置
     * @param rowSpacing 行间距
     * @param colSpacing 列间距
     */
    GridLayout(SDL_Point pos, int rowSpacing, int colSpacing);
    virtual ~GridLayout() = default;    // 析构函数

    /**
     * @brief 获取指定行列元素的位置
     * @param row 行索引（从0开始）
     * @param col 列索引（从0开始）
     * @return SDL_Point 元素的位置坐标
     */
    SDL_Point getElementPos(int row, int col) const;
};

/**
 * @brief 水平布局类，继承自 GridLayout
 * 
 * 将元素水平排列，相当于只有一行的网格布局
 */
class HorizontalLayout : private GridLayout {
public:
    /**
     * @brief 构造函数
     * @param pos 布局起始位置
     * @param colSpacing 列间距
     */
    HorizontalLayout(SDL_Point pos, int colSpacing);
    ~HorizontalLayout() = default;  // 析构函数

    /**
     * @brief 获取指定列元素的位置
     * @param col 列索引（从0开始）
     * @return SDL_Point 元素的位置坐标
     */
    SDL_Point getElementPos(int col) const;
};

/**
 * @brief 垂直布局类，继承自 GridLayout
 * 
 * 将元素垂直排列，相当于只有一列的网格布局
 */
class VerticalLayout : private GridLayout {
public:
    /**
     * @brief 构造函数
     * @param pos 布局起始位置
     * @param rowSpacing 行间距
     */
    VerticalLayout(SDL_Point pos, int rowSpacing);
    ~VerticalLayout() = default;    // 析构函数

    /**
     * @brief 获取指定行元素的位置
     * @param row 行索引（从0开始）
     * @return SDL_Point 元素的位置坐标
     */
    SDL_Point getElementPos(int row) const;
};