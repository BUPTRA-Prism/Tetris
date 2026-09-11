/**
 * @file titlescene.h
 * @brief 标题场景
 */
#pragma once

#include "scene/scene.h"
#include "core/graphics/image.h"
#include "core/graphics/text.h"
#include <functional>
#include <memory>
#include <string_view>

/**
 * @brief 标题场景，展示标题与开始提示
 */
class TitleScene : public Scene {
private:
    std::unique_ptr<Image> m_titleImg;     ///< 标题图片
    std::unique_ptr<Image> m_copyrightImg; ///< 版权图片
    std::unique_ptr<Text> m_startText;     ///< 开始提示文本
    std::unique_ptr<Text> m_yearText;      ///< 年份文本

public:
    /**
     * @brief 构造标题场景
     * @param ctx 全局上下文
     * @param loadSceneCallback 场景切换回调
     */
    TitleScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback);
    ~TitleScene() = default;

    void OnEnter() override;
    void OnExit() override;
    void OnUpdate() override;
    void RenderContent() override;
};