/**
 * @file gamescene.h
 * @brief 游戏场景，驱动对局主循环与渲染
 */
#pragma once

#include "scene/scene.h"
#include "config/ui.h"
#include "core/graphics/image.h"
#include "core/graphics/text.h"
#include <functional>
#include <memory>
#include <string_view>
#include <vector>
#include <SDL2/SDL_rect.h>

/**
 * @brief 游戏场景，以状态机驱动一局的生成、移动、消行与结算全流程
 */
class GameScene : public Scene {
private:
    /**
     * @brief 对局状态
     */
    enum class State {
        Generate,      ///< 生成新方块
        Move,          ///< 移动/下落
        CheckErase,    ///< 检测消行
        Erase,         ///< 逐块消除
        Calculate,     ///< 结算
        GenerateDelay, ///< 生成延迟
        Win,           ///< 通关
        Lose           ///< 失败
    };
    State m_state;        ///< 当前对局状态
    bool m_paused;        ///< 是否暂停

    std::unique_ptr<Text> m_pauseText;       ///< 暂停文本
    std::unique_ptr<Image> m_gameImg;         ///< 游戏背景图片
    std::unique_ptr<Text> m_gameTypeText;     ///< 游戏类型文本
    std::vector<std::unique_ptr<Text>> m_countText; ///< 各方块使用计数文本
    std::unique_ptr<Text> m_linesText;        ///< "LINES-" 文本
    std::unique_ptr<Text> m_linesNumText;     ///< 行数数字
    std::unique_ptr<Text> m_hiScoreText;      ///< "TOP" 文本
    std::unique_ptr<Text> m_hiScoreNumText;   ///< 最高分数字
    std::unique_ptr<Text> m_scoreText;        ///< "SCORE" 文本
    std::unique_ptr<Text> m_scoreNumText;     ///< 分数数字
    std::unique_ptr<Text> m_nextTetrominoText; ///< "NEXT" 文本
    std::unique_ptr<Text> m_levelText;        ///< "LEVEL" 文本
    std::unique_ptr<Text> m_levelNumText;     ///< 等级数字
    std::unique_ptr<Text> m_heightText;       ///< "HEIGHT" 文本
    std::unique_ptr<Text> m_heightNumText;    ///< 高度数字
    std::unique_ptr<Image> m_blockBaseImg;           ///< 方块底色图片
    std::unique_ptr<Image> m_blockSolidPatternImg;   ///< 方块实心纹样图片
    std::unique_ptr<Image> m_blockHollowPatternImg;  ///< 方块空心纹样图片
    std::unique_ptr<Image> m_blockIconBaseImg;          ///< 方块图标底色图片
    std::unique_ptr<Image> m_blockIconSolidPatternImg;  ///< 方块图标实心纹样图片
    std::unique_ptr<Image> m_blockIconHollowPatternImg; ///< 方块图标空心纹样图片
    std::unique_ptr<Image> m_finishOuterPanelImg;  ///< 结束外层面板图片
    std::unique_ptr<Image> m_finishInnerPanelImg;  ///< 结束内层面板图片
    std::unique_ptr<Text> m_finishText;            ///< 结束文本

    int m_fallTotalFrame;             ///< 下落总帧数
    int m_fallCompletedFrame;         ///< 下落已累计帧数
    bool m_softFall;                  ///< 是否软降
    int m_softFallLines;              ///< 软降累计行数
    int m_moveHorizontalTotalFrame;   ///< 水平移动总帧数
    int m_moveHorizontalCompletedFrame; ///< 水平移动已累计帧数
    int m_curHorizontalDelta;         ///< 当前水平移动方向
    int m_generateDelayTotalFrame;    ///< 生成延迟总帧数
    int m_generateDelayCompletedFrame; ///< 生成延迟已累计帧数
    int m_eraseStep;                  ///< 当前消除动画步数
    int m_stepEraseTotalFrame;        ///< 消除动画单步帧数
    int m_stepEraseCompletedFrame;    ///< 消除动画已累计帧数

public:
    /**
     * @brief 构造游戏场景
     * @param ctx 全局上下文
     * @param loadSceneCallback 场景切换回调
     */
    GameScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback);
    ~GameScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnUpdate() override;
    void RenderContent() override;

private:
    /**
     * @brief 在指定位置渲染一个方块
     * @param type 方块显示类型
     * @param pos 绘制位置
     * @param color 等级配色
     * @param baseImg 底色图片
     * @param solidImg 实心纹样图片
     * @param hollowImg 空心纹样图片
     */
    static void RenderBlock(
        Config::GameSceneUI::BlockType type,
        SDL_Point pos,
        Config::GameSceneUI::LevelColor color,
        Image* baseImg,
        Image* solidImg,
        Image* hollowImg
    );
};