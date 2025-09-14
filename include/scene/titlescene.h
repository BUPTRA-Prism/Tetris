#pragma once

#include "scene/scene.h"
#include "ui/text.h"

/**
 * @brief 游戏标题场景
 */
class TitleScene : public Scene {
private:
    SDL_Texture* m_titleFrameTexture;   // 标题框纹理
    SDL_Texture* m_copyrightTexture;    // 版权图标纹理
    std::unique_ptr<Text> m_startText;  // 开始游戏文本
    std::unique_ptr<Text> m_yearText;   // 年份文本
    Mix_Music* m_titleMusic;            // 背景音乐
    Mix_Chunk* m_sceneChunk;           // 切换场景音效

public:
    /**
     * @brief 构造函数
     * @param ctx 全局上下文
     * @param loadSceneCallback 场景切换回调函数
     */
    TitleScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~TitleScene() = default;    // 析构函数

    /**
     * @brief 进入标题场景
     */
    void onEnter() override;
    /**
     * @brief 退出标题场景
     */
    void onExit() override;
    /**
     * @brief 每帧更新
     */
    void onUpdate() override;
    /**
     * @brief 渲染标题场景具体内容
     */
    void renderContent() override;
};