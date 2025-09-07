#include "scene/menuscene.h"
#include "conf/keyconf.h"
#include "conf/resourceconf.h"
#include "conf/sceneconf.h"
#include "conf/settingconf.h"
#include "util/util.h"

MenuScene::MenuScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback)
    , m_music(nullptr) {
    ResourceManager& rm = ctx.resourceManager;
    Settings& s = ctx.settings;

    // 载入菜单框架与选项图标纹理
    m_menuFrameTexture = rm.getImage(MENU_FRAME_IMAGE_PATH);
    m_optionIconTexture = rm.getImage(OPTION_ICON_IMAGE_PATH);

    // 创建游戏模式和音乐模式标题文本
    m_gameTypeText = std::make_unique<Text>(
        ctx,
        MENU_SCENE::GAME_TYPE_TEXT_STR,
        MENU_SCENE::GAME_TYPE_TEXT_POS
    );
    m_musicTypeText = std::make_unique<Text>(
        ctx,
        MENU_SCENE::MUSIC_TYPE_TEXT_STR,
        MENU_SCENE::MUSIC_TYPE_TEXT_POS
    );

    // 初始化游戏模式与音乐模式选项文本
    int gameTypeCnt = GAME_TYPE.size();
    int musicTypeCnt = MUSIC_TYPE.size();
    m_gameTypeOptionText.reserve(gameTypeCnt);
    m_musicTypeOptionText.reserve(musicTypeCnt);
    for (int i = 0; i < gameTypeCnt; ++i) {
        m_gameTypeOptionText.emplace_back(
            std::make_unique<Text>(
                ctx,
                GAME_TYPE[i],
                MENU_SCENE::GAME_TYPE_OPTION_TEXT_POS[i]
            )
        );
    }
    for (int i = 0; i < musicTypeCnt; ++i) {
        m_musicTypeOptionText.emplace_back(
            std::make_unique<Text>(
                ctx,
                MUSIC_TYPE[i].name,
                MENU_SCENE::MUSIC_TYPE_OPTION_TEXT_POS[i]
            )
        );
    }

    // 初始化选项指示图标（左右两个动画图标）
    for (int i = 0; i < 2; ++i) {
        m_gameTypeOptionIcon[i] = std::make_unique<OptionIcon>(
            ctx, 
            m_optionIconTexture, 
            MENU_SCENE::GAME_TYPE_OPTION_ICON_POS[i], 
            MENU_SCENE::OPTION_ICON_SHOW_FRAME, 
            MENU_SCENE::OPTION_ICON_HIDE_FRAME
        );
        m_musicTypeOptionIcon[i] = std::make_unique<OptionIcon>(
            ctx, 
            m_optionIconTexture, 
            MENU_SCENE::MUSIC_TYPE_OPTION_ICON_POS[i], 
            MENU_SCENE::OPTION_ICON_SHOW_FRAME, 
            MENU_SCENE::OPTION_ICON_HIDE_FRAME
        );
    }

    // 载入选项切换音效
    m_optionChunk = rm.getChunk(OPTION_CHUNK_PATH);
}

void MenuScene::onEnter() {
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

    // 启动光标动画
    for (int i = 0; i < 2; ++i) {
        m_gameTypeOptionIcon[i]->playAnim();
        m_musicTypeOptionIcon[i]->playAnim();
    }
}

void MenuScene::onExit() {
    // 停止播放音乐
    m_ctx.audioManager.stopMusic();

    // 停止光标动画
    for (int i = 0; i < 2; ++i) {
        m_gameTypeOptionIcon[i]->stopAnim();
        m_musicTypeOptionIcon[i]->stopAnim();
    }
}

void MenuScene::onUpdate() {
    // 更新光标动画
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

    // 绘制标题文本
    m_gameTypeText->onRender();
    m_musicTypeText->onRender();

    // 绘制选项文本
    for (auto& text: m_gameTypeOptionText) {
        text->onRender();
    }
    for (auto& text: m_musicTypeOptionText) {
        text->onRender();
    }

    // 根据当前设置绘制选项图标位置，每一组图标中，第二个图标水平翻转
    Settings& s = m_ctx.settings;
    int gameTypeIdx = s.getGameTypeIdx();
    int musicTypeIdx = s.getMusicTypeIdx();
    m_gameTypeOptionIcon[0]->onRender(gameTypeIdx);
    m_gameTypeOptionIcon[1]->onRender(gameTypeIdx, true);
    m_musicTypeOptionIcon[0]->onRender(musicTypeIdx);
    m_musicTypeOptionIcon[1]->onRender(musicTypeIdx, true);
}