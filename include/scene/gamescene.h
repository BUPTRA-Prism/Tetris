#pragma once

#include "scene/scene.h"
#include "core/game.h"
#include "ui/layout.h"
#include "ui/text.h"

/**
 * @brief 游戏场景类
 */
class GameScene : public Scene {
private:
    // 游戏流程状态
    enum class Status {
        Generate,   // 生成方块
        Move,       // 移动方块
        Check,      // 检测
        Erase,      // 清除整行
        Calculate,  // 分数计算
        Win,        // 游戏胜利
        Lose        // 游戏失败
    };

    SDL_Texture* m_gameFrameTexture;                    // 游戏框架纹理
    UniqueTexture m_tetrisBasicTexture;                 // 方块基底纹理
    UniqueTexture m_tetrisPreviewBasicTexture;          // 方块预览基底纹理
    SDL_Texture* m_tetrisSolidPatternTexture;           // 方块实心花纹纹理
    SDL_Texture* m_tetrisHollowPatternTexture;          // 方块空心花纹纹理
    SDL_Texture* m_tetrisPreviewSolidPatternTexture;    // 方块预览实心花纹纹理
    SDL_Texture* m_tetrisPreviewHollowPatternTexture;   // 方块预览空心花纹纹理
    SDL_Texture* m_resultOuterFrameTexture;             // 结束外框架纹理
    SDL_Texture* m_resultInnerFrameTexture;             // 结束内框架纹理

    std::unique_ptr<VerticalLayout> m_tetrisPreviewLayout;  // 方块预览布局
    std::unique_ptr<VerticalLayout> m_tetrisCountLayout;    // 方块计数布局
    std::unique_ptr<GridLayout> m_tetrisFieldLayout;        // 游戏场地布局

    std::unique_ptr<Text> m_gameTypeTitle;          // 游戏模式标题
    std::unordered_map<TetrisMode, std::unique_ptr<Text>> m_tetrisCountText;    // 方块计数文本
    std::unique_ptr<Text> m_lineCountText;          // 消除行文本
    std::unique_ptr<Text> m_topScoreTitle;          // 最高分标题
    std::unique_ptr<Text> m_topScoreText;           // 最高分文本
    std::unique_ptr<Text> m_scoreTitle;             // 分数标题
    std::unique_ptr<Text> m_scoreText;              // 分数文本
    std::unique_ptr<Text> m_nextTetrisTitle;        // 下一个方块标题
    std::unique_ptr<Text> m_levelTitle;             // 等级标题
    std::unique_ptr<Text> m_levelText;              // 等级文本
    std::unique_ptr<Text> m_heightTitle;            // 高度标题
    std::unique_ptr<Text> m_heightText;             // 高度文本
    std::unique_ptr<Text> m_resultText;             // 结束文本
    std::unique_ptr<Text> m_pauseText;              // 暂停文本

    Mix_Music* m_music;             // 背景音乐
    Mix_Music* m_winMusic;          // 胜利音乐
    Mix_Music* m_loseMusic;         // 失败音乐
    Mix_Chunk* m_moveChunk;         // 方块移动音效
    Mix_Chunk* m_rotateChunk;       // 方块旋转音效
    Mix_Chunk* m_dropChunk;         // 方块下落音效
    Mix_Chunk* m_eraseChunk;        // 消除音效
    Mix_Chunk* m_eraseFourChunk;    // 消除4行音效
    Mix_Chunk* m_upgradeChunk;      // 升级音效

    std::unique_ptr<Game> m_game;   // 游戏

    int m_generateDelayFrameTarget; // 方块生成延迟帧阈值
    int m_generateDelayFrameCount;  // 方块生成延迟帧计数器
    int m_dasFrameTarget;           // DAS
    int m_arrFrameTarget;           // ARR
    int m_moveFrameCnt;             // 方块移动帧计数器
    int m_dropFrameTarget;          // 方块下落帧阈值
    int m_accelerateFrameTarget;    // 方块加速下落帧阈值
    int m_dropFrameCnt;             // 方块下落帧计数器
    int m_eraseFrameTarget;         // 方块消除帧阈值
    int m_eraseFrameCnt;            // 方块消除帧计数器

    Status m_curStatus;             // 游戏当前流程状态
    int m_preMoveDir;               // 方块前一帧移动方向
    int m_curMoveDir;               // 方块当前帧移动方向
    bool m_justMove;                // 方块是否刚开始移动
    int m_accelerateLineCount;      // 方块不间断加速下落行数
    int m_eraseOrder;               // 方块消除步骤数
    bool m_resultMusicStarted;      // 结束音乐是否开始

    bool m_paused;                  // 游戏是否暂停

public:
    GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~GameScene() = default;

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
     * @brief 渲染游戏场景具体内容
     */
    void renderContent() override;

private:
    /**
     * @brief 初始化游戏模式区域
     */
    void setupGameTypeRegion();
    /**
     * @brief 初始化方块计数区域
     */
    void setupTetrisCountRegion();
    /**
     * @brief 初始化消除行区域
     */
    void setupLineCountRegion();
    /**
     * @brief 初始化分数区域
     */
    void setupScoreRegion();
    /**
     * @brief 初始化下一个方块区域
     */
    void setupNextTetrisRegion();
    /**
     * @brief 初始化等级区域
     */
    void setupLevelRegion();
    /**
     * @brief 初始化高度区域
     */
    void setupHeightRegion();
    /**
     * @brief 初始化游戏场地区域
     */
    void setupField();
    /**
     * @brief 初始化方块相关纹理
     */
    void setupTetrisTexture();
    /**
     * @brief 初始化结束区域
     */
    void setupResultRegion();
    /**
     * @brief 初始化暂停文本
     */
    void setupPauseText();
    /**
     * @brief 初始化俄罗斯方块相关数据
     */
    void setupTetrisData();
    /**
     * @brief 初始化相关音频
     */
    void setupAudio();

    /**
     * @brief 激活游戏模式区域
     */
    void enableGameTypeRegion();
    /**
     * @brief 激活方块计数区域
     */
    void enableTetrisCountRegion();
    /**
     * @brief 激活消除行区域
     */
    void enableLineCountRegion();
    /**
     * @brief 激活分数区域
     */
    void enableScoreRegion();
    /**
     * @brief 激活等级区域
     */
    void enableLevelRegion();
    /**
     * @brief 激活高度区域
     */
    void enableHeightRegion();
    /**
     * @brief 激活俄罗斯方块相关数据
     */
    void enableTetrisData();
    /**
     * @brief 激活相关音频
     */
    void enableAudio();

    /**
     * @brief 禁用相关音频
     */
    void disableAudio();

    /**
     * @brief 生成方块
     */
    void generate();
    /**
     * @brief 方块移动
     */
    void move();
    /**
     * @brief 方块旋转
     */
    void rotate();
    /**
     * @brief 方块下落
     */
    void drop();
    /**
     * @brief 场地检测
     */
    void check();
    /**
     * @brief 消除
     */
    void erase();
    /**
     * @brief 分数计算
     */
    void calculate();
    /**
     * @brief 更新结束区域
     * @param win 游戏是否胜利
     */
    void resultUpdate(bool win);

    /**
     * @brief 渲染暂停文本
     */
    void renderPauseText();
    /**
     * @brief 渲染游戏模式区域
     */
    void renderGameTypeRegion();
    /**
     * @brief 渲染所有游戏数据区域（包括方块计数、消除行、分数、下一个方块、等级、B模式下的高度）
     */
    void renderTetrisGameDataRegions();
    /**
     * @brief 渲染游戏场地
     */
    void renderField();
    /**
     * @brief 渲染结束区域
     */
    void renderResultRegion();

    /**
     * @brief 渲染单个方块
     * @param pos 方块位置
     * @param style 方块样式
     * @param isPreview 是否为预览
     */
    void renderSingleSquare(SDL_Point pos, TetrisStyle style, bool isPreview);
    /**
     * @brief 渲染整组方块
     * @param centerPos 整组方块中心位置
     * @param mode 方块类型
     * @param isPreview 是否为预览
     */
    void renderTetrisMode(SDL_Point centerPos, TetrisMode mode, bool isPreview);
};