/**
 * @file leaderboardview.cpp
 * @brief 排行榜视图实现
 */
#include "entity/leaderboardview.h"
#include "config/ui.h"
#include "util/stringutils.h"
#include <string>

/**
 * @brief 构造排行榜视图，创建三个表头文本
 */
LeaderBoardView::LeaderBoardView(
    const ResourceManager& resourceMgr,
    SDL_Renderer* renderer,
    int orderColumnWidth,
    int nameColumnWidth,
    int scoreColumnWidth,
    int entryHeight
)
    : m_resourceMgr(resourceMgr)
    , m_renderer(renderer)
    , m_orderColumnWidth(orderColumnWidth)
    , m_nameColumnWidth(nameColumnWidth)
    , m_scoreColumnWidth(scoreColumnWidth)
    , m_entryHeight(entryHeight) {
    m_nameHeaderText = std::make_unique<Text>(resourceMgr, renderer, Config::UICommon::LEADER_BOARD_COLUMN_NAME_TEXT_STR);
    m_scoreHeaderText = std::make_unique<Text>(resourceMgr, renderer, Config::UICommon::SCORE_TEXT_STR);
    m_levelHeaderText = std::make_unique<Text>(resourceMgr, renderer, Config::UICommon::LEADER_BOARD_COLUMN_LEVEL_TEXT_STR);
}

/**
 * @brief 载入指定游戏类型的排行榜内容
 */
void LeaderBoardView::Load(
    const LeaderBoard& leaderBoard,
    Setting::GameType gameType
) {
    const std::vector<LeaderBoard::Entry> entries = leaderBoard.GetLeaderBoard(gameType);
    LoadEntries(entries);
}

/**
 * @brief 更新玩家姓名的某一字符并刷新对应文本
 */
void LeaderBoardView::UpdatePlayerName(
    LeaderBoard& leaderBoard,
    Setting::GameType gameType,
    int charIdx,
    int delta
) {
    if (delta != 0) {
        leaderBoard.UpdatePlayerName(gameType, charIdx, delta);

        const std::vector<LeaderBoard::Entry> entries = leaderBoard.GetLeaderBoard(gameType);
        int playerRank = leaderBoard.GetPlayerRank();
        if (playerRank >= 0 && playerRank < static_cast<int>(entries.size())) {
            m_nameText[playerRank]->SetStr(entries[playerRank].name);
        }
    }
}

/**
 * @brief 获取玩家姓名相对排行榜面板的偏移
 */
SDL_Point LeaderBoardView::GetPlayerNameRelativePos(const LeaderBoard& leaderBoard) const noexcept {
    return SDL_Point{ m_orderColumnWidth, m_entryHeight * (leaderBoard.GetPlayerRank() + 1) };
}

/**
 * @brief 渲染排行榜（序号、姓名、分数、等级四列）
 */
void LeaderBoardView::OnRender(SDL_Point pos) {
    int offsetX = 0;
    RenderColumn(pos, offsetX, nullptr, m_orderText);

    offsetX += m_orderColumnWidth;
    RenderColumn(pos, offsetX, m_nameHeaderText.get(), m_nameText);

    offsetX += m_nameColumnWidth;
    RenderColumn(pos, offsetX, m_scoreHeaderText.get(), m_scoreText);

    offsetX += m_scoreColumnWidth;
    RenderColumn(pos, offsetX, m_levelHeaderText.get(), m_levelText);
}

/**
 * @brief 根据条目列表重建各列文本
 */
void LeaderBoardView::LoadEntries(const std::vector<LeaderBoard::Entry>& entries) {
    size_t entryCnt = entries.size();

    m_orderText.resize(entryCnt);
    m_nameText.resize(entryCnt);
    m_scoreText.resize(entryCnt);
    m_levelText.resize(entryCnt);

    for (size_t i = 0; i < entryCnt; ++i) {
        m_orderText[i] = std::make_unique<Text>(m_resourceMgr, m_renderer, std::to_string(i + 1));
        m_nameText[i] = std::make_unique<Text>(m_resourceMgr, m_renderer, entries[i].name);
        m_scoreText[i] = std::make_unique<Text>(m_resourceMgr, m_renderer, Util::Int2String(entries[i].score, Config::UICommon::SCORE_NUM_DIGITS));
        m_levelText[i] = std::make_unique<Text>(m_resourceMgr, m_renderer, Util::Int2String(entries[i].level, Config::UICommon::LEVEL_NUM_DIGITS));
    }
}

/**
 * @brief 渲染一列（可选表头 + 内容行）
 */
void LeaderBoardView::RenderColumn(
    SDL_Point pos,
    int offsetX,
    Text* headerText,
    const std::vector<std::unique_ptr<Text>>& contentText
) {
    if (headerText) {
        headerText->OnRender(MySDL::RenderParams{ 
            SDL_Point{ pos.x + offsetX, pos.y } 
        });
    }

    for (size_t i = 0; i < contentText.size(); ++i) {
        contentText[i]->OnRender(MySDL::RenderParams{ 
            SDL_Point{
                pos.x + offsetX,
                pos.y + m_entryHeight * (static_cast<int>(i) + 1)
            } 
        });
    }
}