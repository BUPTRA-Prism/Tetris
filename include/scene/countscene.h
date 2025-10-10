#pragma once

#include "scene/scene.h"
#include "ui/optionicon.h"
#include "ui/text.h"

/**
 * @brief 结算场景类，用于游戏结束后结算
 */
class CountScene : public Scene {
private:
    SDL_Texture* m_countFrameTexture;       // 结算界面框架纹理
    SDL_Texture* m_typeFrameTexture;        // 游戏模式框架纹理
    UniqueTexture m_recordNameIconTexture;  // 新纪录姓名图标纹理

    std::unique_ptr<VerticalLayout> m_recordOrderLayout;        // 排行榜排名布局
    std::unique_ptr<GridLayout> m_recordLayout;                 // 排行榜布局

    std::unique_ptr<Text> m_gameTypeTitle;                  // 游戏模式标题
    std::vector<std::unique_ptr<Text>> m_countText;         // 结算文本
    std::vector<std::unique_ptr<Text>> m_recordTitle;       // 排行榜表头标题
    std::vector<std::unique_ptr<Text>> m_recordOrderText;   // 排行榜排名
    std::vector<std::unique_ptr<Text>> m_recordNameText;    // 排行榜姓名
    std::vector<std::unique_ptr<Text>> m_recordScoreText;   // 排行榜分数
    std::vector<std::unique_ptr<Text>> m_recordLvText;      // 排行榜等级

    std::unique_ptr<OptionIcon> m_recordNameIcon;   // 新纪录姓名图标

    Mix_Music* m_countMusic;    // 结算界面音乐
    Mix_Chunk* m_optionChunk;   // 选项切换音效
    Mix_Chunk* m_sceneChunk;    // 场景切换音效

    std::string m_updateRecordName;         // 待更新纪录姓名
    std::vector<int> m_recordNameCharIdx;   // 姓名更新字符下标
    int m_recordNamePosIdx;                 // 姓名更新字符位置下标
    int m_recordNameUpdateFrameCount;       // 姓名更新帧计数器
    int m_recordNameUpdateFrameTarget;      // 姓名更新帧阈值

public:
    CountScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~CountScene() = default;

    /**
     * @brief 进入场景
     */
    void onEnter() override;
    /**
     * @brief 退出场景
     */
    void onExit() override;
    /**
     * @brief 每帧更新
     */
    void onUpdate() override;
    /**
     * @brief 渲染结算场景具体内容
     */
    void renderContent() override;

private:
    /**
     * @brief 初始化场景框架
     */
    void setupFrame();
    /**
     * @brief 初始化游戏模式区域
     */
    void setupGameTypeRegion();
    /**
     * @brief 初始化结算文本
     */
    void setupCountText();
    /**
     * @brief 初始化排行榜区域
     */
    void setupRecordRegion();
    /**
     * @brief 初始化新纪录姓名相关数据
     */
    void setupUpdateRecordNameData();
    /**
     * @brief 初始化相关音频
     */
    void setupAudio();

    /**
     * @brief 激活游戏模式区域
     */
    void enableGameTypeRegion();
    /**
     * @brief 激活排行榜区域
     */
    void enableRecordRegion();
    /**
     * @brief 激活新纪录姓名相关数据
     */
    void enableUpdateRecordNameData();
    /**
     * @brief 激活相关音频
     */
    void enableAudio();

    /**
     * @brief 禁用排行榜区域
     */
    void disableRecordRegion();
    /**
     * @brief 禁用相关音频
     */
    void disableAudio();

    /**
     * @brief 更新新纪录姓名图标动画
     */
    void updateRecordNameIconAnimation();
    /**
     * @brief 切换场景
     * @return 切换场景成功返回 true ，否则返回 false
     */
    bool updateSceneSwitch();
    /**
     * @brief 切换新纪录姓名字符位置
     * @return 切换新纪录姓名字符位置成功返回 true ，否则返回 false
     */
    bool updateRecordNamePos();
    /**
     * @brief 切换新纪录姓名字符
     * @return 切换新纪录姓名字符成功返回 true ，否则返回 false
     */
    bool updateRecordNameChar();
    /**
     * @brief 更新相关音效
     * @return 更新相关音效成功返回 true ，否则返回 false
     */
    void updateAudio();

    /**
     * @brief 渲染场景框架
     */
    void renderFrame();
    /**
     * @brief 渲染游戏模式区域
     */
    void renderGameTypeRegion();
    /**
     * @brief 渲染结算文本
     */
    void renderCountText();
    /**
     * @brief 渲染排行榜
     */
    void renderRecordRegion();
};