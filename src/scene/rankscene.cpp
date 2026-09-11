/**
 * @file rankscene.cpp
 * @brief 排行榜场景实现
 */
#include "scene/rankscene.h"
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
#include <SDL2/SDL.h>

/**
 * @brief 构造排行榜场景，创建祝贺信息、排行榜视图与姓名编辑光标
 */
RankScene::RankScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback)
    , m_charIdx(0) {
    m_rankImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::SETTING_IMG);

    m_gameTypePanelImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::GAME_TYPE_B_PANEL_IMG);
    m_gameTypeText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");

    m_congratulationText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::RankSceneUI::CONGRATULATION_TEXT_STR);
    m_praiseText1 = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::RankSceneUI::PRAISE_TEXT_1_STR);
    m_praiseText2 = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::RankSceneUI::PRAISE_TEXT_2_STR);
    m_enterNameText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::RankSceneUI::ENTER_NAME_TEXT_STR);

    m_leaderBoardPanelImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::LEADER_BOARD_PANEL_IMG);
    m_leaderBoardView = std::make_unique<LeaderBoardView>(
        m_ctx.manager.resourceMgr,
        m_ctx.renderer,
        Config::UICommon::LEADER_BOARD_ORDER_COLUMN_WIDTH,
        Config::UICommon::LEADER_BOARD_NAME_COLUMN_WIDTH,
        Config::UICommon::LEADER_BOARD_SCORE_COLUMN_WIDTH,
        Config::UICommon::LEADER_BOARD_ENTRY_HEIGHT
    );

    m_optionIcon = std::make_unique<OptionIcon>(m_ctx.manager.resourceMgr, m_ctx.renderer, Resource::Image::RANK_OPTION_ICON_IMG);
}

/**
 * @brief 进入场景，刷新提示文本与排行榜并播放音乐
 */
void RankScene::OnEnter() {
    m_charIdx = 0;

    switch (m_ctx.game.setting.GetGameType()) {
        case Setting::GameType::TypeA: {
            m_gameTypeText->SetStr(Config::UICommon::GAME_TYPE_A_TEXT_STR);
            break;
        }
        case Setting::GameType::TypeB: {
            m_gameTypeText->SetStr(Config::UICommon::GAME_TYPE_B_TEXT_STR);
            break;
        }
        default: {
            m_gameTypeText->SetStr("");
            break;
        }
    }

    m_leaderBoardView->Load(m_ctx.game.leaderBoard, m_ctx.game.setting.GetGameType());
    m_optionIcon->PlayAnim();
    
    m_ctx.manager.audioMgr.PlayMusic(m_ctx.manager.resourceMgr, Resource::Audio::RANK_MUSIC, 1);
}

/**
 * @brief 退出场景，停止图标动画与音乐
 */
void RankScene::OnExit() {
    m_optionIcon->StopAnim();
    m_ctx.manager.audioMgr.StopMusic();
}

/**
 * @brief 更新：处理姓名录入与场景切换
 */
void RankScene::OnUpdate() {
    m_optionIcon->OnUpdate();

    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::NEXT_SCENE_KEY)) {
        m_loadSceneCallback(Config::SettingSceneUI::NAME);
        return;
    }

    int charIdxDelta = 0;
    int charDelta = 0;
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::LEFT_KEY)) {
        --charIdxDelta;
    }
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::RIGHT_KEY)) {
        ++charIdxDelta;
    }
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::UP_KEY)) {
        ++charDelta;
    }
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::DOWN_KEY)) {
        --charDelta;
    }

    m_charIdx = (m_charIdx + charIdxDelta + Config::Rank::NAME_LEN) % Config::Rank::NAME_LEN;

    m_leaderBoardView->UpdatePlayerName(
        m_ctx.game.leaderBoard,
        m_ctx.game.setting.GetGameType(),
        m_charIdx,
        charDelta
    );
}

/**
 * @brief 渲染祝贺信息、排行榜与姓名编辑光标
 */
void RankScene::RenderContent() {
    m_rankImg->OnRender();

    m_gameTypePanelImg->OnRender(MySDL::RenderParams{ Config::RankSceneUI::GAME_TYPE_PANEL_POS });
    m_gameTypeText->OnRender(MySDL::RenderParams{ Config::RankSceneUI::GAME_TYPE_TEXT_POS });

    m_congratulationText->OnRender(MySDL::RenderParams{
        Config::RankSceneUI::CONGRATULATION_TEXT_POS,
        Config::RankSceneUI::CONGRATULATION_TEXT_COLOR
    });
    m_praiseText1->OnRender(MySDL::RenderParams{ Config::RankSceneUI::PRAISE_TEXT_1_POS });
    m_praiseText2->OnRender(MySDL::RenderParams{ Config::RankSceneUI::PRAISE_TEXT_2_POS });
    m_enterNameText->OnRender(MySDL::RenderParams{ Config::RankSceneUI::ENTER_NAME_TEXT_POS });

    m_leaderBoardPanelImg->OnRender(MySDL::RenderParams{ Config::RankSceneUI::LEADER_BOARD_PANEL_POS });
    
    // 上榜时在姓名字符位置绘制编辑光标
    if (m_ctx.game.leaderBoard.GetPlayerRank() >= 0) {
        SDL_Point playerNameRelativePos = m_leaderBoardView->GetPlayerNameRelativePos(m_ctx.game.leaderBoard);
        m_optionIcon->OnRender(MySDL::RenderParams{
            SDL_Point{
                Config::RankSceneUI::LEADER_BOARD_POS.x + playerNameRelativePos.x + m_charIdx * Resource::Font::DEFAULT_FONT_SIZE,
                Config::RankSceneUI::LEADER_BOARD_POS.y + playerNameRelativePos.y
            }
        });
    }
    
    m_leaderBoardView->OnRender(Config::RankSceneUI::LEADER_BOARD_POS);
}