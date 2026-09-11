/**
 * @file rankscene.h
 * @brief 排行榜场景，展示排名并录入玩家姓名。
 */
#pragma once

#include "scene/scene.h"
#include "core/graphics/image.h"
#include "core/graphics/text.h"
#include "entity/leaderboardview.h"
#include "entity/optionicon.h"
#include <functional>
#include <memory>
#include <string_view>

/**
 * @brief 排行榜场景，展示祝贺信息与排行榜，并支持录入姓名。
 */
class RankScene : public Scene {
private:
    std::unique_ptr<Image> m_rankImg;                ///< 排行榜背景图片
    std::unique_ptr<Image> m_gameTypePanelImg;       ///< 游戏类型面板图片
    std::unique_ptr<Text> m_gameTypeText;            ///< 游戏类型文本
    std::unique_ptr<Text> m_congratulationText;      ///< 祝贺文本
    std::unique_ptr<Text> m_praiseText1;             ///< 称赞文本第一行
    std::unique_ptr<Text> m_praiseText2;             ///< 称赞文本第二行
    std::unique_ptr<Text> m_enterNameText;           ///< 输入姓名提示文本
    std::unique_ptr<Image> m_leaderBoardPanelImg;    ///< 排行榜面板图片
    std::unique_ptr<LeaderBoardView> m_leaderBoardView; ///< 排行榜视图
    std::unique_ptr<OptionIcon> m_optionIcon;        ///< 姓名编辑光标图标

    int m_charIdx; ///< 当前编辑的姓名字符下标

public:
    /**
     * @brief 构造排行榜场景。
     * @param ctx 全局上下文。
     * @param loadSceneCallback 场景切换回调。
     */
    RankScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback);
    ~RankScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnUpdate() override;
    void RenderContent() override;
};