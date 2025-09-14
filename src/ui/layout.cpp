#include "ui/layout.h"

GridLayout::GridLayout(SDL_Point pos, int rowSpacing, int colSpacing)
    : m_pos(pos)
    , m_rowSpacing(rowSpacing)
    , m_colSpacing(colSpacing)
{}

SDL_Point GridLayout::getElementPos(int row, int col) const {
    return { m_pos.x + col * m_colSpacing, m_pos.y + row * m_rowSpacing };
}

HorizontalLayout::HorizontalLayout(SDL_Point pos, int colSpacing) : GridLayout(pos, 0, colSpacing) {}

SDL_Point HorizontalLayout::getElementPos(int col) const {
    return GridLayout::getElementPos(0, col);
}

VerticalLayout::VerticalLayout(SDL_Point pos, int rowSpacing): GridLayout(pos, rowSpacing, 0) {}

SDL_Point VerticalLayout::getElementPos(int row) const {
    return GridLayout::getElementPos(row, 0);
}