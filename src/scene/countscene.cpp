#include "scene/countscene.h"
#include "conf/keyconf.h"
#include "conf/sceneconf.h"
#include "util/common.h"
#include "util/render.h"

CountScene::CountScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    ResourceManager& rm = ctx.resourceManager;
    SDL_Renderer* rdr = ctx.renderer;

    m_countFrameTexture = rm.getImage(SETTING_FRAME_IMAGE_PATH);
    m_typeFrameTexture = rm.getImage(TYPE_B_FRAME_IMAGE_PATH);
    m_gameTypeTitle = std::make_unique<Text>(
        m_ctx,
        "",
        SETTING_SCENE::GAME_TYPE_TITLE_POS
    );
    for (int i = 0; i < COUNT_SCENE::COUNT_TEXT_STR.size(); ++i) {
        m_countText.emplace_back(std::make_unique<Text>(
            m_ctx,
            COUNT_SCENE::COUNT_TEXT_STR[i],
            COUNT_SCENE::COUNT_TEXT_POS[i]
        ));
    }
    m_countText[0]->setColor(COUNT_SCENE::COUNT_TITLE_COLOR);

    m_recordNameIconTexture = createSolidTexture(
        rdr, 
        COUNT_SCENE::RECORD_NAME_ICON_COLOR, 
        COUNT_SCENE::RECORD_NAME_ICON_SIZE, 
        COUNT_SCENE::RECORD_NAME_ICON_SIZE
    );

    m_countMusic = rm.getMusic(COUNT_MUSIC_PATH);
    m_optionChunk = rm.getChunk(OPTION_CHUNK_PATH);
    m_sceneChunk = rm.getChunk(SCENE_CHUNK_PATH);

    m_recordNameUpdateFrameTarget = COUNT_SCENE::RECORD_NAME_CHANGE_FRAME;

    // 创建记录表布局
    m_recordOrderLayout = std::make_unique<VerticalLayout>(
        SETTING_SCENE::RECORD_ORDER_POS,
        SETTING_SCENE::RECORD_ROW_SPACING
    );
    // 创建记录表布局
    m_recordLayout = std::make_unique<GridLayout>(
        SETTING_SCENE::RECORD_POS,
        SETTING_SCENE::RECORD_ROW_SPACING,
        SETTING_SCENE::RECORD_COL_SPACING
    );

    // 创建记录表头文本
    m_recordTitle.reserve(SETTING_SCENE::RECORD_TITLE_STR.size());
    for (int i = 0; i < SETTING_SCENE::RECORD_TITLE_STR.size(); ++i) {
        m_recordTitle.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                SETTING_SCENE::RECORD_TITLE_STR[i],
                m_recordLayout->getElementPos(0, i)
            )
        );
    }
    // 创建记录表内容文本，包括排名、姓名、分数、关卡数
    m_recordOrderText.reserve(RECORD_COUNT);
    m_recordNameText.reserve(RECORD_COUNT);
    m_recordScoreText.reserve(RECORD_COUNT);
    m_recordLvText.reserve(RECORD_COUNT);
    for (int i = 0; i < RECORD_COUNT; ++i) {
        m_recordOrderText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                std::to_string(i + 1),
                m_recordOrderLayout->getElementPos(i)
            )
        );
        m_recordNameText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                "",
                m_recordLayout->getElementPos(i + 1, 0)
            )
        );
        m_recordScoreText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                "",
                m_recordLayout->getElementPos(i + 1, 1)
            )
        );
        m_recordLvText.emplace_back(
            std::make_unique<Text>(
                m_ctx,
                "",
                m_recordLayout->getElementPos(i + 1, 2)
            )
        );
    }
}

void CountScene::onEnter() {
    Settings& s = m_ctx.settings;
    m_gameTypeTitle->setStr(s.getGameType());

    m_recordNameIconLayout = std::make_unique<HorizontalLayout>(
        m_recordLayout->getElementPos(s.getNewRecordOrder() + 1, 0),
        COUNT_SCENE::RECORD_NAME_ICON_SPACING
    );
    m_recordNameIcon = std::make_unique<OptionIcon>(
        m_ctx, 
        m_recordNameIconTexture.get(), 
        [layoutPtr = m_recordNameIconLayout.get()](int row, int col) { 
            return layoutPtr->getElementPos(col);
        }, 
        COUNT_SCENE::RECORD_NAME_ICON_SHOW_FRAME, 
        COUNT_SCENE::RECORD_NAME_ICON_HIDE_FRAME
    );
    m_recordNameIcon->playAnim();

    m_updateRecordName = s.getRecordName(s.getNewRecordOrder());
    m_recordNameCharIdx.assign(RECORD_DEFAULT_NAME.size(), COUNT_SCENE::RECORD_NAME_OPTIONAL_CHARS.size() - 1);
    m_recordNamePosIdx = 0;
    m_recordNameUpdateFrameCount = 0;

    for (int i = 0; i < RECORD_COUNT; ++i) {
        m_recordNameText[i]->setStr(s.getRecordName(i));

        std::string scoreStr = std::to_string(s.getRecordScore(i));
        padLeft(scoreStr, SETTING_SCENE::RECORD_SCORE_MAX_LEN, '0');
        m_recordScoreText[i]->setStr(scoreStr);

        std::string lvStr = std::to_string(s.getRecordLv(i));
        padLeft(lvStr, SETTING_SCENE::RECORD_LV_MAX_LEN, '0');
        m_recordLvText[i]->setStr(lvStr);
    }

    m_ctx.audioManager.playMusic(m_countMusic, 0);
}

void CountScene::onExit() {
    Settings& s = m_ctx.settings;
    s.updateRecordName(m_updateRecordName);

    m_recordNameIcon->stopAnim();

    m_ctx.audioManager.stopMusic();
    m_ctx.audioManager.playChunk(m_sceneChunk);
}

void CountScene::onUpdate() {
    m_recordNameIcon->onUpdate();

    InputManager& im = m_ctx.inputManager;

    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(SETTING_SCENE::NAME);
    }

    if (im.isKeyJustPressed(LEFT_KEY) && !im.isKeyPressed(RIGHT_KEY)) {
        m_recordNamePosIdx = (m_recordNamePosIdx + RECORD_DEFAULT_NAME.length() - 1) % RECORD_DEFAULT_NAME.length();
        m_ctx.audioManager.playChunk(m_optionChunk);
    } else if (im.isKeyJustPressed(RIGHT_KEY) && !im.isKeyPressed(LEFT_KEY)) {
        m_recordNamePosIdx = (m_recordNamePosIdx + 1) % RECORD_DEFAULT_NAME.length();
        m_ctx.audioManager.playChunk(m_optionChunk);
    }

    if (m_recordNameUpdateFrameCount >= m_recordNameUpdateFrameTarget) {
        int changeDelta = 0;
        if (im.isKeyPressed(UP_KEY)) {
            ++changeDelta;
        }
        if (im.isKeyPressed(DOWN_KEY)) {
            --changeDelta;
        }
        if (changeDelta != 0) {
            m_ctx.audioManager.playChunk(m_optionChunk);
            
            m_recordNameCharIdx[m_recordNamePosIdx] = 
            (m_recordNameCharIdx[m_recordNamePosIdx] + COUNT_SCENE::RECORD_NAME_OPTIONAL_CHARS.size() + changeDelta) % COUNT_SCENE::RECORD_NAME_OPTIONAL_CHARS.size();
            m_updateRecordName[m_recordNamePosIdx] = COUNT_SCENE::RECORD_NAME_OPTIONAL_CHARS[m_recordNameCharIdx[m_recordNamePosIdx]];
            m_recordNameText[m_ctx.settings.getNewRecordOrder()]->setStr(m_updateRecordName);
            
            m_recordNameUpdateFrameCount = 0;
        }
    } else {
        ++m_recordNameUpdateFrameCount;
    }
}

void CountScene::renderContent() {
    SDL_Renderer* rdr = m_ctx.renderer;
    Settings& s = m_ctx.settings;

    renderTexture(rdr, m_countFrameTexture);
    renderTexture(rdr, m_typeFrameTexture, SETTING_SCENE::GAME_TYPE_FRAME_POS);
    m_gameTypeTitle->onRender();

    for (int i = 0; i < COUNT_SCENE::COUNT_TEXT_STR.size(); ++i) {
        m_countText[i]->onRender();
    }

    m_recordNameIcon->onRender(0, m_recordNamePosIdx);

    for (auto& text: m_recordTitle) {
        text->onRender();
    }
    for (auto& text: m_recordOrderText) {
        text->onRender();
    }
    for (auto& text: m_recordNameText) {
        text->onRender();
    }
    for (auto& text: m_recordScoreText) {
        text->onRender();
    }
    for (auto& text: m_recordLvText) {
        text->onRender();
    }
}