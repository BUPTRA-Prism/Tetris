#include "core/game.h"
#include "util/util.h"

Game::Game() {
    m_count.emplace(TetrisMode::T, 0);
    m_count.emplace(TetrisMode::J, 0);
    m_count.emplace(TetrisMode::Z, 0);
    m_count.emplace(TetrisMode::O, 0);
    m_count.emplace(TetrisMode::S, 0);
    m_count.emplace(TetrisMode::L, 0);
    m_count.emplace(TetrisMode::I, 0);
}

void Game::resetGame(int level, int height) {
    for (int row = 0; row < m_field.size(); ++row) {
        m_field[row].fill(TetrisStyle::Blank);
    }
    m_level = level;
    m_height = height;
    m_score = 0;
    m_lines = 0;

    for (auto it = m_count.begin(); it != m_count.end(); ++it) {
        it->second = 0;
    }

    m_nextMode = static_cast<TetrisMode>(getRandomInt(0, m_count.size() - 1));
}

TetrisStyle Game::getFieldStyle(int row, int col) const { 
    if (row < 0 || row >= m_field.size() || col < 0 || col >= m_field[0].size() ) {
        return TetrisStyle::Blank;
    }
    return m_field[row][col];
}

int Game::getLevel() const { return m_level; }

int Game::getHeight() const { return m_height; }

int Game::getScore() const { return m_score; }

int Game::getLines() const { return m_lines; }

const std::unordered_map<TetrisMode, int>& Game::getCount() { return m_count; }

void Game::move(int delta) {

}

void Game::rotate(int delta) {

}

void Game::generate() {

}

int Game::erase() {

}

int Game::calculate() {

}

bool Game::win() {

}

bool Game::lose() {
    
}