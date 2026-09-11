/**
 * @file settingscene.cpp
 * @brief 设置场景实现
 */
#include "scene/settingscene.h"
#include "config/key.h"
#include "config/resource.h"
#include "config/ui.h"
#include "mysdl/render.h"
#include "game/setting.h"
#include "manager/audiomanager.h"
#include "manager/inputmanager.h"
#include "framework/game.h"
#include "framework/manager.h"
#include "framework/context.h"
#include <string>
#include <utility>
#include <vector>
#include <SDL2/SDL.h>

/**
 * @brief 构建设置场景，构建等级与高度选项组及排行榜预览
 */
SettingScene::SettingScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback)
    , m_state(SettingState::Level) {
    int maxLevel = ctx.game.setting.GetMaxLevel();
    int maxHeight = ctx.game.setting.GetMaxHeight();
    m_levelOptionCol = GetOptionCol(maxLevel + 1, Config::SettingSceneUI::OPTION_ROW);
    m_heightOptionCol = GetOptionCol(maxHeight + 1, Config::SettingSceneUI::OPTION_ROW);

    m_settingImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::SETTING_IMG);

    m_gameTypePanelImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, "");
    m_gameTypeText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");

    m_levelPanelImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, "");
    
    std::vector<std::string> levelOptionStr(maxLevel + 1);
    std::vector<OptionGroup::TextSpec> levelOptionSpec(maxLevel + 1);
    for (int i = 0; i <= maxLevel; ++i) {
        levelOptionStr[i] = std::to_string(i);
        levelOptionSpec[i] = OptionGroup::TextSpec{
            levelOptionStr[i],
            SDL_Point{
                Config::SettingSceneUI::LEVEL_OPTION_POS.x + Config::SettingSceneUI::OPTION_SPACING * (static_cast<int>(i) % m_levelOptionCol),
                Config::SettingSceneUI::LEVEL_OPTION_POS.y + Config::SettingSceneUI::OPTION_SPACING * (static_cast<int>(i) / m_levelOptionCol)
            },
            Config::SettingSceneUI::OPTION_COLOR
        };
    }
    m_levelOptionGroup = std::make_unique<OptionGroup>(
        ctx.manager.resourceMgr,
        ctx.renderer,
        OptionGroup::TextSpec{ Config::UICommon::LEVEL_TEXT_STR, Config::SettingSceneUI::LEVEL_TEXT_POS },
        std::move(levelOptionSpec),
        Resource::Image::SETTING_OPTION_ICON_IMG,
        std::vector<OptionGroup::IconLayout>{
            OptionGroup::IconLayout{ Config::SettingSceneUI::OPTION_ICON_OFFSET, Config::SettingSceneUI::OPTION_ICON_OFFSET }
        }
    );

    m_heightPanelImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::HEIGHT_PANEL_IMG);

    std::vector<std::string> heightOptionStr(maxHeight + 1);
    std::vector<OptionGroup::TextSpec> heightOptionSpec(maxHeight + 1);
    for (int i = 0; i <= maxHeight; ++i) {
        heightOptionStr[i] = std::to_string(i);
        heightOptionSpec[i] = OptionGroup::TextSpec{
            heightOptionStr[i],
            SDL_Point{
                Config::SettingSceneUI::HEIGHT_OPTION_POS.x + Config::SettingSceneUI::OPTION_SPACING * (i % m_heightOptionCol),
                Config::SettingSceneUI::HEIGHT_OPTION_POS.y + Config::SettingSceneUI::OPTION_SPACING * (i / m_heightOptionCol)
            },
            Config::SettingSceneUI::OPTION_COLOR
        };
    }
    m_heightOptionGroup = std::make_unique<OptionGroup>(
        ctx.manager.resourceMgr,
        ctx.renderer,
        OptionGroup::TextSpec{ Config::UICommon::HEIGHT_TEXT_STR, Config::SettingSceneUI::HEIGHT_TEXT_POS },
        std::move(heightOptionSpec),
        Resource::Image::SETTING_OPTION_ICON_IMG,
        std::vector<OptionGroup::IconLayout>{
            OptionGroup::IconLayout{ Config::SettingSceneUI::OPTION_ICON_OFFSET, Config::SettingSceneUI::OPTION_ICON_OFFSET }
        }
    );

    m_leaderBoardPanelImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::LEADER_BOARD_PANEL_IMG);
    m_leaderBoardView = std::make_unique<LeaderBoardView>(
        m_ctx.manager.resourceMgr,
        m_ctx.renderer,
        Config::UICommon::LEADER_BOARD_ORDER_COLUMN_WIDTH,
        Config::UICommon::LEADER_BOARD_NAME_COLUMN_WIDTH,
        Config::UICommon::LEADER_BOARD_SCORE_COLUMN_WIDTH,
        Config::UICommon::LEADER_BOARD_ENTRY_HEIGHT
    );
}

/**
 * @brief 进入场景，按当前游戏类型刷新面板与排行榜
 */
void SettingScene::OnEnter() {
    m_state = SettingState::Level;
    m_levelOptionGroup->PlayIconAnim();

    switch (m_ctx.game.setting.GetGameType()) {
        case Setting::GameType::TypeA: {
            m_gameTypePanelImg->SetTexture(m_ctx.manager.resourceMgr, Resource::Image::GAME_TYPE_A_PANEL_IMG);
            m_gameTypeText->SetStr(Config::UICommon::GAME_TYPE_A_TEXT_STR);
            m_levelPanelImg->SetTexture(m_ctx.manager.resourceMgr, Resource::Image::LEVEL_A_PANEL_IMG);
            break;
        }
        case Setting::GameType::TypeB: {
            m_gameTypePanelImg->SetTexture(m_ctx.manager.resourceMgr, Resource::Image::GAME_TYPE_B_PANEL_IMG);
            m_gameTypeText->SetStr(Config::UICommon::GAME_TYPE_B_TEXT_STR);
            m_levelPanelImg->SetTexture(m_ctx.manager.resourceMgr, Resource::Image::LEVEL_B_PANEL_IMG);
            break;
        }
        default: {
            m_gameTypePanelImg->SetTexture(m_ctx.manager.resourceMgr, "");
            m_gameTypeText->SetStr("");
            m_levelPanelImg->SetTexture(m_ctx.manager.resourceMgr, "");
            break;
        }
    }

    m_leaderBoardView->Load(m_ctx.game.leaderBoard, m_ctx.game.setting.GetGameType());
}

/**
 * @brief 退出场景，停止图标动画
 */
void SettingScene::OnExit() {
    m_levelOptionGroup->StopIconAnim();
    m_heightOptionGroup->StopIconAnim();
}

/**
 * @brief 更新：处理场景切换、状态切换与选项移动
 */
void SettingScene::OnUpdate() {
    m_levelOptionGroup->OnUpdate();
    m_heightOptionGroup->OnUpdate();

    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::NEXT_SCENE_KEY)) {
        m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::LOAD_SCENE_CHUNK);
        m_loadSceneCallback(Config::GameSceneUI::NAME);
        return;
    }

    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::LAST_SCENE_KEY)) {
        m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::LOAD_SCENE_CHUNK);
        m_loadSceneCallback(Config::MenuSceneUI::NAME);
        return;
    }

    // B 类型下按切换键在等级/高度间切换
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::CHANGE_OPTION_KEY)) {
        if (m_ctx.game.setting.GetGameType() == Setting::GameType::TypeB) {
            m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::OPTION_CHUNK);
            switch (m_state) {
                case SettingState::Level: {
                    m_state = SettingState::Height;
                    m_levelOptionGroup->StopIconAnim();
                    m_heightOptionGroup->PlayIconAnim();
                    break;
                }
                case SettingState::Height: {
                    m_state = SettingState::Level;
                    m_heightOptionGroup->StopIconAnim();
                    m_levelOptionGroup->PlayIconAnim();
                    break;
                }
                default: break;
            }
        }
        return;
    }

    int optionDelta = 0;
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::LEFT_KEY)) {
        --optionDelta;
    }
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::RIGHT_KEY)) {
        ++optionDelta;
    }
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::UP_KEY)) {
        switch (m_state) {
            case SettingState::Level: {
                optionDelta -= m_levelOptionCol;
                break;
            }
            case SettingState::Height: {
                optionDelta -= m_heightOptionCol;
                break;
            }
            default: break;
        }
    }
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::DOWN_KEY)) {
        switch (m_state) {
            case SettingState::Level: {
                optionDelta += m_levelOptionCol;
                break;
            }
            case SettingState::Height: {
                optionDelta += m_heightOptionCol;
                break;
            }
            default: break;
        }
    }

    switch (m_state) {
        case SettingState::Level: {
            m_ctx.game.setting.AdjustLevel(optionDelta);
            break;
        }
        case SettingState::Height: {
            m_ctx.game.setting.AdjustHeight(optionDelta);
            break;
        }
        default: break;
    }

    if (optionDelta != 0) {
        m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::OPTION_CHUNK);
    }
}

/**
 * @brief 渲染背景、选项组与排行榜
 */
void SettingScene::RenderContent() {
    m_settingImg->OnRender();

    m_gameTypePanelImg->OnRender(MySDL::RenderParams{ Config::SettingSceneUI::GAME_TYPE_PANEL_POS });
    m_gameTypeText->OnRender(MySDL::RenderParams{ Config::SettingSceneUI::GAME_TYPE_TEXT_POS });
    
    m_levelOptionGroup->RenderTitle();
    m_levelOptionGroup->RenderIcons(m_ctx.game.setting.GetLevel());
    m_levelOptionGroup->RenderOptions();
    m_levelPanelImg->OnRender(MySDL::RenderParams{ Config::SettingSceneUI::LEVEL_PANEL_POS });

    if (m_ctx.game.setting.GetGameType() == Setting::GameType::TypeB) {
        m_heightOptionGroup->RenderTitle();
        m_heightOptionGroup->RenderIcons(m_ctx.game.setting.GetHeight());
        m_heightOptionGroup->RenderOptions();
        m_heightPanelImg->OnRender(MySDL::RenderParams{ Config::SettingSceneUI::HEIGHT_PANEL_POS });
    }

    m_leaderBoardPanelImg->OnRender(MySDL::RenderParams{ Config::SettingSceneUI::LEADER_BOARD_PANEL_POS });
    m_leaderBoardView->OnRender(Config::SettingSceneUI::LEADER_BOARD_POS);
}

/**
 * @brief 计算给定数量与行数下的列数（向上取整）
 */
int SettingScene::GetOptionCol(int optionCnt, int optionRow) {
    int optionCol = optionCnt / optionRow;
    if (optionCnt % optionRow != 0) {
        ++optionCol;
    }
    return optionCol;
}