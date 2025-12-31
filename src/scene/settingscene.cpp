#include "scene/settingscene.h"
#include "conf/keyconf.h"
#include "conf/settingconf.h"
#include "conf/resourceconf.h"
#include "conf/uiconf.h"
#include "util/render.h"

SettingScene::SettingScene(Context& ctx, Core& core, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, core, loadSceneCallback) {
    ResourceManager& rm = ctx.resourceManager;
    SDL_Renderer* rdr = ctx.renderer;

    m_settingFrame = rm.getImage(SETTING_FRAME_PATH);
    m_scoreboard = rm.getImage(VERSUS_BOARD_PATH);
    m_logo = rm.getImage(LOGO_PATH);
    m_arrow = rm.getImage(ARROW_PATH);

    m_scoreText = std::make_unique<Text>(
        ctx, 
        SCOREBOARD::SCORE_TEXT_STR, 
        SCOREBOARD::SCORE_TEXT_POS
    );
    m_lineText = std::make_unique<Text>(
        ctx, 
        SCOREBOARD::LINE_TEXT_STR, 
        SCOREBOARD::LINE_TEXT_POS
    );
    m_levelText = std::make_unique<Text>(
        ctx, 
        SCOREBOARD::LEVEL_TEXT_STR, 
        SETTING_SCENE::LEVEL_TEXT_POS
    );

    m_gameSelectText = std::make_unique<Text>(
        ctx, 
        SETTING_SCENE::GAME_SELECT_TEXT_STR, 
        SETTING_SCENE::GAME_SELECT_TEXT_POS,
        SETTING_SCENE::SETTING_TEXT_COLOR
    );
    for (int i = 0; i < MODE_OPTIONS.size(); ++i) {
        m_gameSelectOptionText.emplace_back(
            std::make_unique<Text>(
                ctx, 
                MODE_OPTIONS[i], 
                SDL_Point {
                    SETTING_SCENE::GAME_SELECT_OPTION_TEXT_START_POS.x, 
                    SETTING_SCENE::GAME_SELECT_OPTION_TEXT_START_POS.y + i * SETTING_SCENE::SELECT_OPTION_SPACING
                },
                SETTING_SCENE::SETTING_TEXT_COLOR
            )
        );
    }

    m_levelSelectText = std::make_unique<Text>(
        ctx, 
        SETTING_SCENE::LEVEL_SELECT_TEXT_STR, 
        SETTING_SCENE::LEVEL_SELECT_TEXT_POS,
        SETTING_SCENE::SETTING_TEXT_COLOR
    );
    for (int i = 0; i < LEVEL_OPTIONS.size(); ++i) {
        m_levelSelectOptionText.emplace_back(
            std::make_unique<Text>(
                ctx, 
                std::to_string(LEVEL_OPTIONS[i]), 
                SDL_Point {
                    SETTING_SCENE::LEVEL_SELECT_OPTION_TEXT_START_POS.x, 
                    SETTING_SCENE::LEVEL_SELECT_OPTION_TEXT_START_POS.y + i * SETTING_SCENE::SELECT_OPTION_SPACING
                },
                SETTING_SCENE::SETTING_TEXT_COLOR
            )
        );
    }

    m_handicapSelectText = std::make_unique<Text>(
        ctx, 
        SETTING_SCENE::HANDICAP_SELECT_TEXT_STR, 
        SETTING_SCENE::HANDICAP_SELECT_TEXT_POS,
        SETTING_SCENE::SETTING_TEXT_COLOR
    );
    for (int i = 0; i < HANDICAP_OPTIONS.size(); ++i) {
        std::string optionStr = std::to_string(HANDICAP_OPTIONS[i]);
        m_handicapSelectOptionText.emplace_back(
            std::make_unique<Text>(
                ctx, 
                std::string(2 - optionStr.length(), ' ') + optionStr, 
                SDL_Point {
                    SETTING_SCENE::HANDICAP_SELECT_OPTION_TEXT_START_POS.x, 
                    SETTING_SCENE::HANDICAP_SELECT_OPTION_TEXT_START_POS.y + i * SETTING_SCENE::SELECT_OPTION_SPACING
                },
                SETTING_SCENE::SETTING_TEXT_COLOR
            )
        );
    }

    m_musicSelectText = std::make_unique<Text>(
        ctx, 
        SETTING_SCENE::MUSIC_SELECT_TEXT_STR, 
        SETTING_SCENE::MUSIC_SELECT_TEXT_POS,
        SETTING_SCENE::SETTING_TEXT_COLOR
    );
    for (int i = 0; i < MUSIC_OPTIONS.size(); ++i) {
        m_musicSelectOptionText.emplace_back(
            std::make_unique<Text>(
                ctx, 
                MUSIC_OPTIONS[i], 
                SDL_Point {
                    SETTING_SCENE::MUSIC_SELECT_OPTION_TEXT_START_POS.x, 
                    SETTING_SCENE::MUSIC_SELECT_OPTION_TEXT_START_POS.y + i * SETTING_SCENE::SELECT_OPTION_SPACING
                },
                SETTING_SCENE::SETTING_TEXT_COLOR
            )
        );
    }

    m_selectChunk = rm.getChunk(SELECT_CHUNK_PATH);
    m_nextSceneChunk = rm.getChunk(NEXT_SCENE_CHUNK_PATH);
}

void SettingScene::onEnter() {
    m_setting = Setting::Game;
}

void SettingScene::onExit() {
    AudioManager& am = m_ctx.audioManager;

    am.stopMusic();
}

void SettingScene::onUpdate() {
    AudioManager& am = m_ctx.audioManager;
    InputManager& im = m_ctx.inputManager;
    ResourceManager& rm = m_ctx.resourceManager;
    Settings& s = m_core.settings;

    if (im.isKeyJustPressed(NEXT_SCENE_KEY)) {
        am.playChunk(m_nextSceneChunk);
        switch (m_setting) {
            case Setting::Game: m_setting = Setting::Level; break;
            case Setting::Level: m_setting = Setting::Handicap; break;
            case Setting::Handicap: m_setting = Setting::Music; break;
            case Setting::Music: m_loadSceneCallback(GAME_SCENE::NAME); break;
            default: break;
        }
    }

    int delta = 0;
    if (im.isKeyJustPressed(UP_KEY) && !im.isKeyPressed(DOWN_KEY)) {
        delta = -1;
    } else if (im.isKeyJustPressed(DOWN_KEY) && !im.isKeyPressed(UP_KEY)) {
        delta = 1;
    }

    if (delta != 0) {
        am.playChunk(m_selectChunk);
        switch (m_setting) {
            case Setting::Game: { 
                s.setModeIdx(delta); 
                break; 
            }
            case Setting::Level: { 
                s.setLevelIdx(delta); 
                break; 
            }
            case Setting::Handicap: { 
                s.setHandicapIdx(delta); 
                break; 
            }
            case Setting::Music: { 
                s.setMusicIdx(delta);
                std::string musicOption = MUSIC_OPTIONS[s.getMusicIdx()];
                if (musicOption == SILENCE) {
                    am.stopMusic();
                } else {
                    for (auto& c: musicOption) {
                        c = std::tolower(c);
                    }
                    am.playMusic(rm.getMusic(musicOption + ".ogg"));
                }
                break;
            }
            default: break;
        }
    }
}

void SettingScene::renderContent() {
    Settings& s = m_core.settings;
    SDL_Renderer* rdr = m_ctx.renderer;

    renderTexture(rdr, m_settingFrame);
    renderTexture(rdr, m_scoreboard, SCOREBOARD::POS);

    m_scoreText->onRender();
    m_lineText->onRender();
    m_levelText->onRender();

    switch (m_setting) {
        case Setting::Game: {
            renderTexture(rdr, m_logo, SETTING_SCENE::LOGO_POS);
            m_gameSelectText->onRender(); 
            for (int i = 0; i < m_gameSelectOptionText.size(); ++i) {
                m_gameSelectOptionText[i]->onRender();
            }
            renderTexture(
                rdr, 
                m_arrow, 
                SDL_Point {
                    SETTING_SCENE::GAME_SELECT_OPTION_ARROW_START_POS.x,
                    SETTING_SCENE::GAME_SELECT_OPTION_ARROW_START_POS.y + s.getModeIdx() * SETTING_SCENE::SELECT_OPTION_SPACING
                }
            );
            break;
        }
        case Setting::Level: {
            m_levelSelectText->onRender();
            for (int i = 0; i < m_levelSelectOptionText.size(); ++i) {
                m_levelSelectOptionText[i]->onRender();
            }
            renderTexture(
                rdr, 
                m_arrow, 
                SDL_Point {
                    SETTING_SCENE::LEVEL_SELECT_OPTION_ARROW_START_POS.x,
                    SETTING_SCENE::LEVEL_SELECT_OPTION_ARROW_START_POS.y + s.getLevelIdx() * SETTING_SCENE::SELECT_OPTION_SPACING
                }
            );
            break;
        }
        case Setting::Handicap: {
            m_handicapSelectText->onRender();
            for (int i = 0; i < m_handicapSelectOptionText.size(); ++i) {
                m_handicapSelectOptionText[i]->onRender();
            }
            renderTexture(
                rdr, 
                m_arrow, 
                SDL_Point {
                    SETTING_SCENE::HANDICAP_SELECT_OPTION_ARROW_START_POS.x,
                    SETTING_SCENE::HANDICAP_SELECT_OPTION_ARROW_START_POS.y + s.getHandicapIdx() * SETTING_SCENE::SELECT_OPTION_SPACING
                }
            );
            break;
        }
        case Setting::Music: {
            m_musicSelectText->onRender();
            for (int i = 0; i < m_musicSelectOptionText.size(); ++i) {
                m_musicSelectOptionText[i]->onRender();
            }
            renderTexture(
                rdr, 
                m_arrow, 
                SDL_Point {
                    SETTING_SCENE::MUSIC_SELECT_OPTION_ARROW_START_POS.x,
                    SETTING_SCENE::MUSIC_SELECT_OPTION_ARROW_START_POS.y + s.getMusicIdx() * SETTING_SCENE::SELECT_OPTION_SPACING
                }
            );
            break;
        }
        default: break;
    }
}