#include "scene/menuscene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "conf/settingconf.h"
#include "util/render.h"

MenuScene::MenuScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback)
    , m_music(nullptr) {
    ResourceManager& rm = ctx.resourceManager;
    Settings& s = ctx.settings;

    m_menuFrameTexture = rm.getImage(MENU_FRAME_IMAGE_PATH);        // 载入菜单界面框架纹理
    m_optionIconTexture = rm.getImage(OPTION_ICON_IMAGE_PATH);      // 载入选项图标纹理
    m_optionChunk = rm.getChunk(OPTION_CHUNK_PATH);                 // 载入切换选项音效
    m_sceneChunk = rm.getChunk(SCENE_CHUNK_PATH);                   // 载入切换场景音效

    // 构造各区域组件
    constructGameTypeOptionUI();
    constructMusicTypeOptionUI();
}

void MenuScene::constructGameTypeOptionUI() {
    // 创建游戏类型选项与图标布局
    m_gameTypeOptionLayout = std::make_unique<HorizontalLayout>(
        MENU_SCENE::GAME_TYPE_OPTION_POS,
        MENU_SCENE::GAME_TYPE_OPTION_SPACING
    );
    m_gameTypeOptionIconLayout = std::make_unique<HorizontalLayout>(
        MENU_SCENE::GAME_TYPE_OPTION_ICON_POS,
        MENU_SCENE::GAME_TYPE_OPTION_ICON_OUTER_SPACING
    );

    // 创建游戏类型标题文本
    m_gameTypeTitle = std::make_unique<Text>(
        m_ctx,
        MENU_SCENE::GAME_TYPE_TITLE_STR,
        MENU_SCENE::GAME_TYPE_TITLE_POS
    );

    // 创建游戏类型选项文本
    int gameTypeCnt = GAME_TYPE.size();
    m_gameTypeOptionText.reserve(gameTypeCnt);
    for (int i = 0; i < gameTypeCnt; ++i) {
        m_gameTypeOptionText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                GAME_TYPE[i],
                m_gameTypeOptionLayout->getElementPos(i)
            )
        );
    }

    // 创建游戏类型选项图标（左右各一个，右侧的水平翻转）
    for (int i = 0; i < 2; ++i) {
        m_gameTypeOptionIcon[i] = std::make_unique<OptionIcon>(
            m_ctx, 
            m_optionIconTexture, 
            [layoutPtr = m_gameTypeOptionIconLayout.get(), i](int row, int col) { 
                SDL_Point pos = layoutPtr->getElementPos(col);
                pos.x += i * MENU_SCENE::GAME_TYPE_OPTION_ICON_INNER_SPACING;
                return pos;
            }, 
            MENU_SCENE::OPTION_ICON_SHOW_FRAME, 
            MENU_SCENE::OPTION_ICON_HIDE_FRAME, 
            (i & 1) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
        );
    }
}

void MenuScene::constructMusicTypeOptionUI() {
    // 创建音乐类型选项与图标布局
    m_musicTypeOptionLayout = std::make_unique<VerticalLayout>(
        MENU_SCENE::MUSIC_TYPE_OPTION_POS,
        MENU_SCENE::MUSIC_TYPE_OPTION_SPACING
    );
    m_musicTypeOptionIconLayout = std::make_unique<VerticalLayout>(
        MENU_SCENE::MUSIC_TYPE_OPTION_ICON_POS,
        MENU_SCENE::MUSIC_TYPE_OPTION_ICON_OUTER_SPACING
    );

    // 创建音乐类型标题文本
    m_musicTypeTitle = std::make_unique<Text>(
        m_ctx,
        MENU_SCENE::MUSIC_TYPE_TITLE_STR,
        MENU_SCENE::MUSIC_TYPE_TITLE_POS
    );

    // 创建音乐类型选项文本
    int musicTypeCnt = MUSIC_TYPE.size();
    m_musicTypeOptionText.reserve(musicTypeCnt);
    for (int i = 0; i < musicTypeCnt; ++i) {
        m_musicTypeOptionText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                MUSIC_TYPE[i].name,
                m_musicTypeOptionLayout->getElementPos(i)
            )
        );
    }

    // 创建游戏类型选项图标（左右各一个，右侧的水平翻转）
    for (int i = 0; i < 2; ++i) {
        m_musicTypeOptionIcon[i] = std::make_unique<OptionIcon>(
            m_ctx, 
            m_optionIconTexture, 
            [layoutPtr = m_musicTypeOptionIconLayout.get(), i](int row, int col) { 
                SDL_Point pos = layoutPtr->getElementPos(row);
                pos.x += i * MENU_SCENE::MUSIC_TYPE_OPTION_ICON_INNER_SPACING;
                return pos;
            }, 
            MENU_SCENE::OPTION_ICON_SHOW_FRAME, 
            MENU_SCENE::OPTION_ICON_HIDE_FRAME,
            (i & 1) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
        );
    }
}

void MenuScene::onEnter() {
    initGameTypeOptionUI();
    initMusicTypeOptionUI();
}

void MenuScene::initGameTypeOptionUI() {
    for (int i = 0; i < 2; ++i) {
        m_gameTypeOptionIcon[i]->playAnim();
    }
}

void MenuScene::initMusicTypeOptionUI() {
    ResourceManager& rm = m_ctx.resourceManager;
    AudioManager& am = m_ctx.audioManager;
    Settings& s = m_ctx.settings;

    // 根据设置加载并播放音乐
    m_music = rm.getMusic(s.getMusicPath());
    if (m_music) {
        am.playMusic(m_music);
    } else {
        am.stopMusic();
    }

    // 选项图标启动动画
    for (int i = 0; i < 2; ++i) {
        m_musicTypeOptionIcon[i]->playAnim();
    }
}

void MenuScene::onExit() {
    // 停止播放音乐
    m_ctx.audioManager.stopMusic();
    // 播放切换场景音效
    m_ctx.audioManager.playChunk(m_sceneChunk);

    // 选项图标停止动画
    for (int i = 0; i < 2; ++i) {
        m_gameTypeOptionIcon[i]->stopAnim();
        m_musicTypeOptionIcon[i]->stopAnim();
    }
}

void MenuScene::onUpdate() {
    // 选项图标动画更新
    for (int i = 0; i < 2; ++i) {
        m_gameTypeOptionIcon[i]->onUpdate();
        m_musicTypeOptionIcon[i]->onUpdate();
    }

    bool gameTypeChanged = false;
    bool musicTypeChanged = false;
    InputManager& im = m_ctx.inputManager;
    Settings& s = m_ctx.settings;

    // 场景切换
    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(SETTING_SCENE::NAME);
    } else if (im.isKeyJustPressed(ABOVE_SCENE_KEY)) {
        m_loadSceneCallback(TITLE_SCENE::NAME);
    } else {
        // 游戏模式切换
        if (im.isKeyJustPressed(LEFT_KEY) && !im.isKeyPressed(RIGHT_KEY)) {
            gameTypeChanged = s.setGameType(-1);
        } else if (im.isKeyJustPressed(RIGHT_KEY) && !im.isKeyPressed(LEFT_KEY)) {
            gameTypeChanged = s.setGameType(1);
        }
        // 音乐模式切换
        if (im.isKeyJustPressed(UP_KEY) && !im.isKeyPressed(DOWN_KEY)) {
            musicTypeChanged = s.setMusicType(-1);
        } else if (im.isKeyJustPressed(DOWN_KEY) && !im.isKeyPressed(UP_KEY)) {
            musicTypeChanged = s.setMusicType(1);
        }
    }

    ResourceManager& rm = m_ctx.resourceManager;
    AudioManager& am = m_ctx.audioManager;
    // 如果游戏模式和音乐模式中任一项发生了切换，播放选项切换音效
    if (gameTypeChanged || musicTypeChanged) {
        am.playChunk(m_optionChunk);
    }
    // 如果音乐模式中发生了切换，播放切换后的音乐，如果是OFF则停止播放音乐
    if (musicTypeChanged) {
        m_music = rm.getMusic(s.getMusicPath());
        if (m_music) {
            am.playMusic(m_music);
        } else {
            am.stopMusic();
        }
    }
}

void MenuScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;

    // 绘制菜单框架
    renderTexture(rdr, m_menuFrameTexture);

    // 渲染游戏类型选项区域
    renderGameTypeOptionUI();
    // 渲染音乐类型选项区域
    renderMusicTypeOptionUI();
}

void MenuScene::renderGameTypeOptionUI() {
    // 渲染游戏类型标题
    m_gameTypeTitle->onRender();
    // 渲染游戏类型选项文本
    for (auto& text: m_gameTypeOptionText) {
        text->onRender();
    }

    // 渲染游戏类型选项图标
    Settings& s = m_ctx.settings;
    int gameTypeIdx = s.getGameTypeIdx();
    for (int i = 0; i < 2; ++i) {
        m_gameTypeOptionIcon[i]->onRender(0, gameTypeIdx);
    }
}

void MenuScene::renderMusicTypeOptionUI() {
    // 渲染音乐类型标题
    m_musicTypeTitle->onRender();
    // 渲染音乐类型选项文本
    for (auto& text: m_musicTypeOptionText) {
        text->onRender();
    }

    // 渲染音乐类型选项文本
    Settings& s = m_ctx.settings;
    int musicTypeIdx = s.getMusicTypeIdx();
    for (int i = 0; i < 2; ++i) {
        m_musicTypeOptionIcon[i]->onRender(musicTypeIdx, 0);
    }
}