/**
 * @file settingscene.h
 * @brief 设置场景，提供等级、高度等选项调整
 */
#pragma once

#include "scene/scene.h"
#include "core/graphics/image.h"
#include "core/graphics/text.h"
#include "entity/optiongroup.h"
#include "entity/leaderboardview.h"
#include <functional>
#include <memory>
#include <string_view>

/**
 * @brief 设置场景，管理等级、高度选项与排行榜预览
 */
class SettingScene : public Scene {
private:
    /**
     * @brief 设置项切换状态
     */
    enum class SettingState {
        Level,  ///< 等级
        Height  ///< 高度
    };
    SettingState m_state;   ///< 当前设置状态
    int m_levelOptionCol;   ///< 等级选项列数
    int m_heightOptionCol;  ///< 高度选项列数

    std::unique_ptr<Image> m_settingImg;                 ///< 设置背景图片
    std::unique_ptr<Image> m_gameTypePanelImg;           ///< 游戏类型面板图片
    std::unique_ptr<Text> m_gameTypeText;                ///< 游戏类型文本
    std::unique_ptr<Image> m_levelPanelImg;              ///< 等级面板图片
    std::unique_ptr<OptionGroup> m_levelOptionGroup;     ///< 等级选项组
    std::unique_ptr<Image> m_heightPanelImg;             ///< 高度面板图片
    std::unique_ptr<OptionGroup> m_heightOptionGroup;    ///< 高度选项组
    std::unique_ptr<Image> m_leaderBoardPanelImg;        ///< 排行榜面板图片
    std::unique_ptr<LeaderBoardView> m_leaderBoardView;  ///< 排行榜视图

public:
    /**
     * @brief 构建设置场景
     * @param ctx 全局上下文
     * @param loadSceneCallback 场景切换回调
     */
    SettingScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback);
    ~SettingScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnUpdate() override;
    void RenderContent() override;

private:
    /**
     * @brief 计算给定数量与行数下的列数
     * @param optionCnt 选项总数
     * @param optionRow 行数
     * @return 列数
     */
    int GetOptionCol(int optionCnt, int optionRow);
};