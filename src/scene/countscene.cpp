#include "scene/countscene.h"
#include "conf/keyconf.h"
#include "conf/sceneconf.h"
#include "util/common.h"
#include "util/render.h"

CountScene::CountScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    // 初始化场景框架
    setupFrame();

    // 初始化游戏模式区域
    setupGameTypeRegion();
    // 初始化结算文本
    setupCountText();
    // 初始化排行榜区域
    setupRecordRegion();
    // 初始化纪录姓名更新相关数据
    setupUpdateRecordNameData();

    // 初始化相关音频
    setupAudio();
}

void CountScene::onEnter() {
    // 激活场景框架
    enableGameTypeRegion();

    // 激活纪录姓名更新相关数据
    enableUpdateRecordNameData();
    // 激活排行榜区域
    enableRecordRegion();

    // 激活相关音频
    enableAudio();
}

void CountScene::onExit() {
    // 禁用排行榜区域
    disableRecordRegion();

    // 禁用相关音频
    disableAudio();
}

void CountScene::onUpdate() {
    // 更新新纪录姓名图标动画
    updateRecordNameIconAnimation();

    // 切换场景
    if (updateSceneSwitch()) {
        return ;
    }

    // 切换新纪录姓名更新字符位置/字符
    bool recordNamePosChanged = updateRecordNamePos();
    bool recordNameCharChanged = updateRecordNameChar();

    // 如果出现切换，播放选项切换音效
    if (recordNamePosChanged || recordNameCharChanged) {
        updateAudio();
    }
}

void CountScene::renderContent() {
    // 渲染场景框架
    renderFrame();

    // 渲染游戏模式区域
    renderGameTypeRegion();
    // 渲染结算文本
    renderCountText();
    // 渲染排行榜区域
    renderRecordRegion();
}

void CountScene::setupFrame() {
    ResourceManager& rm = m_ctx.resourceManager;

    // 初始化场景框架
    m_countFrameTexture = rm.getImage(SETTING_FRAME_IMAGE_PATH);
}

void CountScene::setupGameTypeRegion() {
    ResourceManager& rm = m_ctx.resourceManager;

    // 初始化游戏模式框架和标题（游戏模式框架固定为B模式的框架）
    m_typeFrameTexture = rm.getImage(TYPE_B_FRAME_IMAGE_PATH);
    m_gameTypeTitle = std::make_unique<Text>(
        m_ctx,
        "",
        SETTING_SCENE::GAME_TYPE_TITLE_POS
    );
}

void CountScene::setupCountText() {
    // 初始化结算文本
    for (int i = 0; i < COUNT_SCENE::COUNT_TEXT_STR.size(); ++i) {
        m_countText.emplace_back(std::make_unique<Text>(
            m_ctx,
            COUNT_SCENE::COUNT_TEXT_STR[i],
            COUNT_SCENE::COUNT_TEXT_POS[i]
        ));
    }
    // 第一条结算文本变色
    m_countText[0]->setColor(COUNT_SCENE::COUNT_TITLE_COLOR);
}

void CountScene::setupRecordRegion() {
    SDL_Renderer* rdr = m_ctx.renderer;

    // 初始化新纪录姓名图标（纯色块）
    m_recordNameIconTexture = createSolidTexture(
        rdr, 
        COUNT_SCENE::RECORD_NAME_ICON_COLOR, 
        COUNT_SCENE::RECORD_NAME_ICON_SIZE, 
        COUNT_SCENE::RECORD_NAME_ICON_SIZE
    );

    // 创建排行榜名次布局
    m_recordOrderLayout = std::make_unique<VerticalLayout>(
        SETTING_SCENE::RECORD_ORDER_POS,
        SETTING_SCENE::RECORD_ROW_SPACING
    );
    // 创建排行榜布局
    m_recordLayout = std::make_unique<GridLayout>(
        SETTING_SCENE::RECORD_POS,
        SETTING_SCENE::RECORD_ROW_SPACING,
        SETTING_SCENE::RECORD_COL_SPACING
    );

    // 创建排行榜表头文本
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
    // 创建排行榜内容文本，包括名次、姓名、分数、等级
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

void CountScene::setupUpdateRecordNameData() {
    m_recordNameUpdateFrameTarget = COUNT_SCENE::RECORD_NAME_CHANGE_FRAME;
}

void CountScene::setupAudio() {
    ResourceManager& rm = m_ctx.resourceManager;

    // 初始化相关音频
    m_countMusic = rm.getMusic(COUNT_MUSIC_PATH);
    m_optionChunk = rm.getChunk(OPTION_CHUNK_PATH);
    m_sceneChunk = rm.getChunk(SCENE_CHUNK_PATH);
}

void CountScene::enableGameTypeRegion() {
    Settings& s = m_ctx.settings;

    // 游戏模式标题文本赋值
    m_gameTypeTitle->setStr(s.getGameType());
}

void CountScene::enableRecordRegion() {
    Settings& s = m_ctx.settings;

    // 激活新纪录姓名图标布局
    m_recordNameIconLayout = std::make_unique<HorizontalLayout>(
        // 布局位置就是新纪录姓名的位置，行：新纪录名次+1，列：0
        m_recordLayout->getElementPos(s.getNewRecordOrder() + 1, 0),
        COUNT_SCENE::RECORD_NAME_ICON_SPACING
    );

    // 排行榜内容文本赋值
    for (int i = 0; i < RECORD_COUNT; ++i) {
        Record record = s.getRecordInfo(i);
        // 如果是新纪录，姓名文本设置为m_updateRecordName，否则设置为record.name
        m_recordNameText[i]->setStr(i == s.getNewRecordOrder() ? m_updateRecordName : record.name);

        std::string scoreStr = std::to_string(record.score);
        padLeft(scoreStr, RECORD_SCORE_MAX_LEN, '0');
        m_recordScoreText[i]->setStr(scoreStr);

        std::string lvStr = std::to_string(record.lv);
        padLeft(lvStr, RECORD_LV_MAX_LEN, '0');
        m_recordLvText[i]->setStr(lvStr);
    }

    // 激活新纪录姓名图标
    m_recordNameIcon = std::make_unique<OptionIcon>(
        m_ctx, 
        m_recordNameIconTexture.get(), 
        [layoutPtr = m_recordNameIconLayout.get()](int row, int col) { 
            return layoutPtr->getElementPos(col);
        }, 
        COUNT_SCENE::RECORD_NAME_ICON_SHOW_FRAME, 
        COUNT_SCENE::RECORD_NAME_ICON_HIDE_FRAME
    );
    // 启动图标动画
    m_recordNameIcon->playAnim();
}

void CountScene::enableUpdateRecordNameData() {
    // 新纪录姓名重置为"------"
    m_updateRecordName = std::string(RECORD_NAME_MAX_LEN, COUNT_SCENE::RECORD_NAME_OPTIONAL_CHARS.back());
    m_recordNameCharIdx.assign(RECORD_NAME_MAX_LEN, COUNT_SCENE::RECORD_NAME_OPTIONAL_CHARS.size() - 1);
    // 姓名更新字符位置下标重置为0
    m_recordNamePosIdx = 0;
    // 姓名更新帧计数器重置为0
    m_recordNameUpdateFrameCount = 0;
}

void CountScene::enableAudio() {
    AudioManager& am = m_ctx.audioManager;

    // 激活背景音乐
    am.playMusic(m_countMusic, 0);
}

void CountScene::disableRecordRegion() {
    Settings& s = m_ctx.settings;
    // 更新新纪录姓名至排行榜中
    s.updateRecordName(m_updateRecordName);

    // 新纪录姓名图标停止动画
    m_recordNameIcon->stopAnim();
}

void CountScene::disableAudio() {
    AudioManager& am = m_ctx.audioManager;

    // 停止背景音乐
    am.stopMusic();
    // 播放场景切换音效
    am.playChunk(m_sceneChunk);
}

void CountScene::updateRecordNameIconAnimation() {
    // 新纪录姓名图标更新动画
    m_recordNameIcon->onUpdate();
}

bool CountScene::updateSceneSwitch() {
    InputManager& im = m_ctx.inputManager;

    bool updateSceneChanged = false;
    // 切换场景
    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        m_loadSceneCallback(SETTING_SCENE::NAME);
        updateSceneChanged = true;
    }

    return updateSceneChanged;
}

bool CountScene::updateRecordNamePos() {
    InputManager& im = m_ctx.inputManager;

    bool recordNamePosChanged = false;
    // 修改新纪录姓名更新字符下标
    if (im.isKeyJustPressed(LEFT_KEY) && !im.isKeyPressed(RIGHT_KEY)) {
        m_recordNamePosIdx = (m_recordNamePosIdx + RECORD_NAME_MAX_LEN - 1) % RECORD_NAME_MAX_LEN;
        recordNamePosChanged = true;
    } else if (im.isKeyJustPressed(RIGHT_KEY) && !im.isKeyPressed(LEFT_KEY)) {
        m_recordNamePosIdx = (m_recordNamePosIdx + 1) % RECORD_NAME_MAX_LEN;
        recordNamePosChanged = true;
    }

    return recordNamePosChanged;
}

bool CountScene::updateRecordNameChar() {
    InputManager& im = m_ctx.inputManager;

    bool recordNameCharChanged = false;
    // 如果姓名更新帧计数器到达阈值
    if (m_recordNameUpdateFrameCount >= m_recordNameUpdateFrameTarget) {
        // 根据上下键按键情况确定偏移量
        int changeDelta = 0;
        if (im.isKeyPressed(UP_KEY)) {
            ++changeDelta;
        }
        if (im.isKeyPressed(DOWN_KEY)) {
            --changeDelta;
        }
        // 如果偏移量不为0，说明字符变更了
        if (changeDelta != 0) {
            // 更新新纪录姓名对应位置字符
            m_recordNameCharIdx[m_recordNamePosIdx] = 
            (m_recordNameCharIdx[m_recordNamePosIdx] + COUNT_SCENE::RECORD_NAME_OPTIONAL_CHARS.size() + changeDelta) % COUNT_SCENE::RECORD_NAME_OPTIONAL_CHARS.size();
            m_updateRecordName[m_recordNamePosIdx] = COUNT_SCENE::RECORD_NAME_OPTIONAL_CHARS[m_recordNameCharIdx[m_recordNamePosIdx]];
            // 更新新纪录姓名文本
            m_recordNameText[m_ctx.settings.getNewRecordOrder()]->setStr(m_updateRecordName);

            recordNameCharChanged = true;
            
            // 姓名更新帧计数器归0
            m_recordNameUpdateFrameCount = 0;
        }
    } else {
        // 姓名更新帧计数器累加
        ++m_recordNameUpdateFrameCount;
    }

    return recordNameCharChanged;
}

void CountScene::updateAudio() {
    AudioManager& am = m_ctx.audioManager;

    // 播放选项切换音效
    am.playChunk(m_optionChunk);
}

void CountScene::renderFrame() {
    SDL_Renderer* rdr = m_ctx.renderer;

    // 渲染场景框架
    renderTexture(rdr, m_countFrameTexture);
}

void CountScene::renderGameTypeRegion() {
    SDL_Renderer* rdr = m_ctx.renderer;

    // 渲染游戏模式框架和标题
    renderTexture(rdr, m_typeFrameTexture, SETTING_SCENE::GAME_TYPE_FRAME_POS);
    m_gameTypeTitle->onRender();
}

void CountScene::renderCountText() {
    // 渲染结算文本
    for (int i = 0; i < COUNT_SCENE::COUNT_TEXT_STR.size(); ++i) {
        m_countText[i]->onRender();
    }
}

void CountScene::renderRecordRegion() {
    // 渲染新纪录姓名图标
    m_recordNameIcon->onRender(0, m_recordNamePosIdx);

    // 渲染排行榜
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