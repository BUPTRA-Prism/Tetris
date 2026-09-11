/**
 * @file leaderboardview.h
 * @brief 排行榜视图组件，渲染序号/姓名/分数/等级列表
 */
#pragma once

#include "game/setting.h"
#include "game/leaderboard.h"
#include "core/graphics/text.h"
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

class ResourceManager;
class LeaderBoard;

/**
 * @brief 排行榜视图，负责渲染排行榜表头与各列内容
 */
class LeaderBoardView {
private:
    ResourceManager& m_resourceMgr; ///< 资源管理器
    SDL_Renderer* m_renderer;       ///< 渲染器

    std::unique_ptr<Text> m_nameHeaderText;  ///< 姓名表头
    std::unique_ptr<Text> m_scoreHeaderText; ///< 分数表头
    std::unique_ptr<Text> m_levelHeaderText; ///< 等级表头
    std::vector<std::unique_ptr<Text>> m_orderText;  ///< 序号列
    std::vector<std::unique_ptr<Text>> m_nameText;   ///< 姓名列
    std::vector<std::unique_ptr<Text>> m_scoreText;  ///< 分数列
    std::vector<std::unique_ptr<Text>> m_levelText;  ///< 等级列

    int m_orderColumnWidth; ///< 序号列宽
    int m_nameColumnWidth;  ///< 姓名列宽
    int m_scoreColumnWidth; ///< 分数列宽
    int m_entryHeight;      ///< 条目行高

public:
    /**
     * @brief 构造排行榜视图
     * @param resourceMgr 资源管理器
     * @param renderer 渲染器
     * @param orderColumnWidth 序号列宽
     * @param nameColumnWidth 姓名列宽
     * @param scoreColumnWidth 分数列宽
     * @param entryHeight 条目行高
     */
    LeaderBoardView(
        ResourceManager& resourceMgr,
        SDL_Renderer* renderer,
        int orderColumnWidth,
        int nameColumnWidth,
        int scoreColumnWidth,
        int entryHeight
    );
    ~LeaderBoardView() = default;

    /**
     * @brief 载入指定游戏类型的排行榜内容
     * @param leaderBoard 排行榜
     * @param gameType 游戏类型
     */
    void Load(LeaderBoard& leaderBoard, Setting::GameType gameType);

    /**
     * @brief 更新玩家姓名的某一字符
     * @param leaderBoard 排行榜
     * @param gameType 游戏类型
     * @param charIdx 字符下标
     * @param delta 字符集循环偏移量
     */
    void UpdatePlayerName(
        LeaderBoard& leaderBoard,
        Setting::GameType gameType,
        int charIdx,
        int delta
    );

    /**
     * @brief 获取玩家姓名相对排行榜面板的偏移
     * @param leaderBoard 排行榜
     * @return 相对位置
     */
    SDL_Point GetPlayerNameRelativePos(LeaderBoard& leaderBoard) const;

    /**
     * @brief 渲染排行榜
     * @param pos 排行榜面板左上角
     */
    void OnRender(SDL_Point pos);

private:
    /**
     * @brief 根据条目列表重建各列文本
     * @param entries 条目列表
     */
    void LoadEntries(const std::vector<LeaderBoard::Entry>& entries);

    /**
     * @brief 渲染一列（表头 + 内容）
     * @param pos 面板位置
     * @param offsetX 列 X 偏移
     * @param headerText 表头（可为空）
     * @param contentText 内容文本
     */
    void RenderColumn(
        SDL_Point pos,
        int offsetX,
        Text* headerText,
        const std::vector<std::unique_ptr<Text>>& contentText
    );
};