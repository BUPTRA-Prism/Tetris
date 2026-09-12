/**
 * @file logic.cpp
 * @brief 游戏核心逻辑实现
 */
#include "game/logic.h"
#include <algorithm>
#include <SDL2/SDL.h>

/**
 * @brief 构造并初始化各方块数据、游戏区与随机数引擎
 */
Logic::Logic()
    : m_linesCnt(0)
    , m_score(0)
    , m_level(0)
    , m_height(0)
    , m_pivot{}
    , m_curRotation(0)
    , m_curBlockPos{}
    , m_eraseLines{}
    , m_rng{ static_cast<unsigned int>(SDL_GetPerformanceCounter()) } {
    m_tetrominoTypes = {
        Rule::TetrominoType::T,
        Rule::TetrominoType::J,
        Rule::TetrominoType::Z,
        Rule::TetrominoType::O,
        Rule::TetrominoType::S,
        Rule::TetrominoType::L,
        Rule::TetrominoType::I
    };
    m_blockTypes = {
        Config::GameSceneUI::BlockType::DarkSolid,
        Config::GameSceneUI::BlockType::DarkHollow,
        Config::GameSceneUI::BlockType::LightSolid
    };

    m_tetrominoData = {
        { 
            Rule::TetrominoType::T, 
            TetrominoData{
                Config::GameSceneUI::BlockType::DarkHollow,
                Config::GameSceneUI::TETROMINO_T_ICON_POS,
                0,
                Rule::ROTATE_T
            }
        },
        { 
            Rule::TetrominoType::J, 
            TetrominoData{
                Config::GameSceneUI::BlockType::DarkSolid,
                Config::GameSceneUI::TETROMINO_J_ICON_POS,
                0,
                Rule::ROTATE_J
            }
        },
        { 
            Rule::TetrominoType::Z, 
            TetrominoData{
                Config::GameSceneUI::BlockType::LightSolid,
                Config::GameSceneUI::TETROMINO_Z_ICON_POS,
                0,
                Rule::ROTATE_Z
            }
        },
        { 
            Rule::TetrominoType::O, 
            TetrominoData{
                Config::GameSceneUI::BlockType::DarkHollow,
                Config::GameSceneUI::TETROMINO_O_ICON_POS,
                0,
                Rule::ROTATE_O
            }
        },
        { 
            Rule::TetrominoType::S, 
            TetrominoData{
                Config::GameSceneUI::BlockType::DarkSolid,
                Config::GameSceneUI::TETROMINO_S_ICON_POS,
                0,
                Rule::ROTATE_S
            }
        },
        { 
            Rule::TetrominoType::L, 
            TetrominoData{
                Config::GameSceneUI::BlockType::LightSolid,
                Config::GameSceneUI::TETROMINO_L_ICON_POS,
                0,
                Rule::ROTATE_L
            }
        },
        { 
            Rule::TetrominoType::I, 
            TetrominoData{
                Config::GameSceneUI::BlockType::DarkHollow,
                Config::GameSceneUI::TETROMINO_I_ICON_POS,
                0,
                Rule::ROTATE_I
            }
        }
    };

    for (auto& row: m_field) {
        row.fill(Config::GameSceneUI::BlockType::Blank);
    }

    m_curBlockPos.reserve(Rule::BLOCK_COUNT);
    m_eraseLines.reserve(Config::Game::ERASE_MAX_COUNT);

    m_tetrominoTypeDist = std::uniform_int_distribution<size_t>{ 0, m_tetrominoTypes.size() - 1 };
    m_blockTypeDist = std::uniform_int_distribution<size_t>{ 0, m_blockTypes.size() - 1 };
    m_handicapBlankDist = std::uniform_int_distribution<int>{
        Config::Game::HANDICAP_BLANK_BLOCK_MIN_NUM,
        Config::Game::HANDICAP_BLANK_BLOCK_MAX_NUM
    };

    for (int i = 0; i < Config::Game::FIELD_WIDTH; ++i) {
        m_blockColVec[i] = i;
    }
}

/** @brief 获取方块类型列表 */
const std::vector<Rule::TetrominoType>& Logic::GetTetrominoTypes() const noexcept {
    return m_tetrominoTypes;
}

/** @brief 获取当前行数 */
int Logic::GetLinesCnt() const noexcept {
    return m_linesCnt;
}

/** @brief 获取当前分数 */
int Logic::GetScore() const noexcept {
    return m_score;
}

/** @brief 获取当前等级 */
int Logic::GetLevel() const noexcept {
    return m_level;
}

/** @brief 获取当前初始高度 */
int Logic::GetHeight() const noexcept {
    return m_height;
}

/** @brief 获取某方块的显示类型，不存在时返回 Blank */
Config::GameSceneUI::BlockType Logic::GetTetrominoBlockType(Rule::TetrominoType tetrominoType) const noexcept {
    auto it = m_tetrominoData.find(tetrominoType);
    return it != m_tetrominoData.end() ? it->second.blockType : Config::GameSceneUI::BlockType::Blank;
}

/** @brief 获取某方块的图标位置 */
SDL_Point Logic::GetIconPos(Rule::TetrominoType tetrominoType) const noexcept {
    auto it = m_tetrominoData.find(tetrominoType);
    return it != m_tetrominoData.end() ? it->second.iconPos : SDL_Point{ 0, 0 };
}

/** @brief 获取某方块的使用计数 */
int Logic::GetTetrominoCnt(Rule::TetrominoType tetrominoType) const noexcept {
    auto it = m_tetrominoData.find(tetrominoType);
    return it != m_tetrominoData.end() ? it->second.count : 0;
}

/** @brief 获取游戏区只读引用 */
const Logic::Field& Logic::GetField() const noexcept {
    return m_field;
}

/** @brief 获取当前方块类型（可能为 nullopt） */
std::optional<Rule::TetrominoType> Logic::GetCurTetrominoType() const noexcept {
    return m_curTetrominoType;
}

/** @brief 获取下一个方块类型（可能为 nullopt） */
std::optional<Rule::TetrominoType> Logic::GetNextTetrominoType() const noexcept {
    return m_nextTetrominoType;
}

/** @brief 获取某方块默认（旋转态 0）的位置偏移 */
Rule::RotatePosDelta Logic::GetDefaultRotatePosDelta(Rule::TetrominoType tetrominoType) const noexcept {
    auto it = m_tetrominoData.find(tetrominoType);
    return it != m_tetrominoData.end() ? it->second.rotateData[0] : Rule::RotatePosDelta{};
}

/**
 * @brief 重置游戏状态
 *
 * B 类型会按初始高度预填障碍行：随机留空若干列，其余列填入随机小格显示类型
 */
void Logic::Reset(Setting::GameType gameType, int level, int height) {
    m_linesCnt = 0;
    if (gameType == Setting::GameType::TypeB) {
        m_linesCnt = Config::Game::GAME_TYPE_B_INIT_LINES_COUNT;
    }
    m_score = 0;
    m_level = level;
    m_height = height;

    for (auto& data: m_tetrominoData) {
        data.second.count = 0;
    }

    for (auto& row: m_field) {
        row.fill(Config::GameSceneUI::BlockType::Blank);
    }
    if (gameType == Setting::GameType::TypeB && height >= 0 && height <= Config::Setting::MAX_HEIGHT) {
        for (int row = 0; row < Config::Game::HANDICAP_LINES[height]; ++row) {
            std::shuffle(m_blockColVec.begin(), m_blockColVec.end(), m_rng);
            int blankNum = m_handicapBlankDist(m_rng);
            if (blankNum > Config::Game::FIELD_WIDTH) {
                blankNum = Config::Game::FIELD_WIDTH;
            }
            for (int idx = 0; idx < blankNum; ++idx) {
                m_field[row][m_blockColVec[idx]] = Config::GameSceneUI::BlockType::Blank;
            }
            for (int idx = blankNum; idx < Config::Game::FIELD_WIDTH; ++idx) {
                m_field[row][m_blockColVec[idx]] = static_cast<Config::GameSceneUI::BlockType>(m_blockTypeDist(m_rng));
            }
        }
    }

    m_curTetrominoType = std::nullopt;
    m_nextTetrominoType = std::nullopt;
    m_pivot = {};
    m_curRotation = 0;
    m_curBlockPos = {};
    m_eraseLines.clear();
}

/**
 * @brief 生成新方块
 *
 * 复用上一个"下一个方块"，并以最多 GENERATE_ROLL 次重掷来降低连续相同类型的概率
 */
bool Logic::Generate() {
    m_curBlockPos.clear();

    if (m_nextTetrominoType.has_value()) {
        m_curTetrominoType = m_nextTetrominoType;
    } else {
        m_curTetrominoType = static_cast<Rule::TetrominoType>(m_tetrominoTypeDist(m_rng));
    }

    for (int i = 0; i < Config::Game::GENERATE_ROLL; ++i) {
        m_nextTetrominoType = static_cast<Rule::TetrominoType>(m_tetrominoTypeDist(m_rng));
        if (m_nextTetrominoType != m_curTetrominoType) {
            break;
        }
    }

    auto it = m_tetrominoData.find(m_curTetrominoType.value());
    if (it != m_tetrominoData.end()) {
        ++it->second.count;
    }

    return AdjustCurBlocks({ Config::Game::FIELD_VISIBLE_HEIGHT - 1, Config::Game::INIT_GENERATE_Y }, 0);
}

/**
 * @brief 方块下落一行
 * @return 下落成功返回 true，落地锁定返回 false
 */
bool Logic::Fall() {
    return AdjustCurBlocks({ m_pivot.first - 1, m_pivot.second }, m_curRotation);
}

/**
 * @brief 水平移动方块
 */
bool Logic::MoveHorizontal(int delta) {
    return AdjustCurBlocks({ m_pivot.first, m_pivot.second + delta }, m_curRotation);
}

/**
 * @brief 旋转方块（结果取模到 [0, ROTATE_COUNT)）
 */
bool Logic::Rotate(int delta) {
    return AdjustCurBlocks(m_pivot, (m_curRotation + Rule::ROTATE_COUNT + delta) % Rule::ROTATE_COUNT);
}

/**
 * @brief 获取当前方块最底小格的行，用于计算生成延迟
 */
int Logic::GetLockRow() const noexcept {
    int lockRow = Config::Game::FIELD_VISIBLE_HEIGHT + Config::Game::FIELD_HIDDEN_HEIGHT;
    for (auto& pos: m_curBlockPos) {
        if (pos.first < lockRow) {
            lockRow = pos.first;
        }
    }

    return lockRow;
}

/**
 * @brief 检测并记录所有可消除（整行非空）的行
 * @return 可消除的行数
 */
int Logic::CheckEraseLines() {
    m_eraseLines.clear();

    for (int row = 0; row < Config::Game::FIELD_VISIBLE_HEIGHT + Config::Game::FIELD_HIDDEN_HEIGHT; ++row) {
        bool full = true;
        for (int col = 0; col < Config::Game::FIELD_WIDTH; ++col) {
            if (m_field[row][col] == Config::GameSceneUI::BlockType::Blank) {
                full = false;
                break;
            }
        }
        if (full) {
            m_eraseLines.emplace_back(row);
        }
    }

    return m_eraseLines.size();
}

/**
 * @brief 执行一步逐块消除动画：从待消除行的中心向两侧挖空
 *
 * @return 仍需继续消除返回 true，否则返回 false（即已挖空整行）
 */
bool Logic::StepErase(int step) {
    if (step < 0 || step > (Config::Game::FIELD_WIDTH - 1) / 2) {
        return false;
    }

    for (auto& line: m_eraseLines) {
        m_field[line][(Config::Game::FIELD_WIDTH - 1) / 2 - step] = Config::GameSceneUI::BlockType::Blank;
        m_field[line][Config::Game::FIELD_WIDTH / 2 + step] = Config::GameSceneUI::BlockType::Blank;
    }
    return true;
}

/**
 * @brief 压实消除行并在顶部补空白
 *
 * 使用快慢指针：快指针逐行扫描，跳过待消除行，其余行下移到慢指针处，
 * 最终将顶部剩余行置空
 */
void Logic::Erase() {
    if (m_eraseLines.empty()) {
        return;
    }

    int height = Config::Game::FIELD_VISIBLE_HEIGHT + Config::Game::FIELD_HIDDEN_HEIGHT;
    int slowRow = 0;
    int eraseCnt = static_cast<int>(m_eraseLines.size());
    int eraseIdx = 0;
    for (int fastRow = 0; fastRow < height; ++fastRow) {
        if (eraseIdx < eraseCnt && fastRow == m_eraseLines[eraseIdx]) {
            ++eraseIdx;
        } else {
            for (int col = 0; col < Config::Game::FIELD_WIDTH; ++col) {
                m_field[slowRow][col] = m_field[fastRow][col];
            }
            ++slowRow;
        }
    }
    for (; slowRow < height; ++slowRow) {
        m_field[slowRow].fill(Config::GameSceneUI::BlockType::Blank);
    }
}

/**
 * @brief 结算分数与等级/行数
 *
 * A 类型累计消除行并按 10 行一级升级；B 类型递减剩余行数直至通关
 */
void Logic::Calculate(Setting::GameType gameType, int softFallLines) {
    int eraseCnt = static_cast<int>(m_eraseLines.size());
    m_score += Config::Game::CalculateEraseScore(m_level, eraseCnt) + softFallLines;

    switch (gameType) {
        case Setting::GameType::TypeA: {
            m_linesCnt += eraseCnt;
            if (m_linesCnt >= 10 * (m_level + 1)) {
                ++m_level;
            }
            break;
        }
        case Setting::GameType::TypeB: {
            m_linesCnt -= eraseCnt;
            if (m_linesCnt < 0) {
                m_linesCnt = 0;
            }
            break;
        }
        default: break;
    }
}

/**
 * @brief 追加通关加成分数
 */
void Logic::AddBuffScore(int level, int height) {
    m_score += Config::Game::CalculateBuffScore(level + height);
}

/**
 * @brief 尝试将当前方块调整到指定枢轴与旋转态
 *
 * 采用"先赋值、后检测"策略：先完整构造期望位置集合 expectedBlockPos，
 * 再统一判断越界/占用冲突；当无冲突（或当前尚无方块）时才提交新位置，
 * 最后将方块写回游戏区
 *
 * @return 无冲突并调整成功返回 true
 */
bool Logic::AdjustCurBlocks(std::pair<int, int> pivot, int rotation) {
    if (rotation < 0 || rotation >= Rule::ROTATE_COUNT) {
        return false;
    }

    if (!m_curTetrominoType.has_value()) {
        return false;
    }

    auto it = m_tetrominoData.find(m_curTetrominoType.value());
    if (it == m_tetrominoData.end()) {
        return false;
    }

    // 先清空旧位置
    for (auto& pos: m_curBlockPos) {
        m_field[pos.first][pos.second] = Config::GameSceneUI::BlockType::Blank;
    }
    
    std::vector<std::pair<int, int>> expectedBlockPos{};
    expectedBlockPos.reserve(Rule::BLOCK_COUNT);
    bool conflict = false;
    for (int i = 0; i < Rule::BLOCK_COUNT; ++i) {
        int row = pivot.first + (it->second.rotateData)[rotation][i].first;
        int col = pivot.second + (it->second.rotateData)[rotation][i].second;
        bool outOfBounds = 
            row < 0 || row >= Config::Game::FIELD_VISIBLE_HEIGHT + Config::Game::FIELD_HIDDEN_HEIGHT ||
            col < 0 || col >= Config::Game::FIELD_WIDTH;
        if (outOfBounds || m_field[row][col] != Config::GameSceneUI::BlockType::Blank) {
            conflict = true;
        }
        if (conflict && !m_curBlockPos.empty()) {
            break;
        }
        if (outOfBounds && m_curBlockPos.empty()) {
            continue;
        }
        expectedBlockPos.emplace_back( std::pair{ row, col } );
    }

    if (!conflict || m_curBlockPos.empty()) {
        m_pivot = pivot;
        m_curRotation = rotation;
        m_curBlockPos = std::move(expectedBlockPos);
    }
    
    for (auto& pos: m_curBlockPos) {
        m_field[pos.first][pos.second] = it->second.blockType;
    }
    return !conflict;
}