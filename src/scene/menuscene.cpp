/**
 * @file menuscene.cpp
 * @brief 菜单场景实现
 */
#include "scene/menuscene.h"
#include "config/key.h"
#include "config/resource.h"
#include "config/ui.h"
#include "game/setting.h"
#include "manager/audiomanager.h"
#include "manager/inputmanager.h"
#include "framework/game.h"
#include "framework/manager.h"
#include "framework/context.h"
#include <utility>
#include <vector>
#include <SDL2/SDL.h>

/**
 * @brief 构造菜单场景，构建游戏类型与音乐两个选项组
 */
MenuScene::MenuScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {
    m_menuImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::MENU_IMG);

    const auto gameTypeOptionStr = ctx.game.setting.GetGameTypeOptionStr();
    std::vector<OptionGroup::TextSpec> gameTypeOptionSpec(gameTypeOptionStr.size());
    for (size_t i = 0; i < gameTypeOptionStr.size(); ++i) {
        gameTypeOptionSpec[i] = OptionGroup::TextSpec{
            gameTypeOptionStr[i],
            SDL_Point{
                Config::MenuSceneUI::GAME_TYPE_OPTION_POS.x + Config::MenuSceneUI::GAME_TYPE_OPTION_SPACING_X * static_cast<int>(i),
                Config::MenuSceneUI::GAME_TYPE_OPTION_POS.y
            }
        };
    }

    m_gameTypeOptionGroup = std::make_unique<OptionGroup>(
        ctx.manager.resourceMgr,
        ctx.renderer,
        OptionGroup::TextSpec{ Config::MenuSceneUI::GAME_TYPE_TEXT_STR, Config::MenuSceneUI::GAME_TYPE_TEXT_POS },
        std::move(gameTypeOptionSpec),
        Resource::Image::MENU_OPTION_ICON_IMG,
        std::vector<OptionGroup::IconLayout>{
            OptionGroup::IconLayout{ Config::MenuSceneUI::GAME_TYPE_OPTION_ICON_OFFSET_X, 0 },
            OptionGroup::IconLayout{ Config::MenuSceneUI::GAME_TYPE_OPTION_FLIP_ICON_OFFSET_X, 0, true }
        }
    );

    const auto musicOptionStr = ctx.game.setting.GetMusicOptionStr();
    std::vector<OptionGroup::TextSpec> musicOptions(musicOptionStr.size());
    for (size_t i = 0; i < musicOptionStr.size(); ++i) {
        musicOptions[i] = OptionGroup::TextSpec{ 
            musicOptionStr[i],
            SDL_Point{
                Config::MenuSceneUI::MUSIC_OPTION_POS.x,
                Config::MenuSceneUI::MUSIC_OPTION_POS.y + Config::MenuSceneUI::MUSIC_OPTION_SPACING_Y * static_cast<int>(i)
            }
        };
    }

    m_musicOptionGroup = std::make_unique<OptionGroup>(
        ctx.manager.resourceMgr,
        ctx.renderer,
        OptionGroup::TextSpec{ Config::MenuSceneUI::MUSIC_TYPE_TEXT_STR, Config::MenuSceneUI::MUSIC_TYPE_TEXT_POS },
        std::move(musicOptions),
        Resource::Image::MENU_OPTION_ICON_IMG,
        std::vector<OptionGroup::IconLayout>{
            OptionGroup::IconLayout{ Config::MenuSceneUI::MUSIC_OPTION_ICON_OFFSET_X, 0 },
            OptionGroup::IconLayout{ Config::MenuSceneUI::MUSIC_OPTION_FLIP_ICON_OFFSET_X, 0, true }
        }
    );
}

/**
 * @brief 进入场景，播放图标动画与当前所选音乐
 */
void MenuScene::OnEnter() {
    m_gameTypeOptionGroup->PlayIconAnim();
    m_musicOptionGroup->PlayIconAnim();

    auto bgm = m_ctx.game.setting.GetMusic();
    if (bgm.has_value()) {
        m_ctx.manager.audioMgr.PlayMusic(m_ctx.manager.resourceMgr, bgm.value());
    }
}

/**
 * @brief 退出场景，停止图标动画与音乐
 */
void MenuScene::OnExit() {
    m_gameTypeOptionGroup->StopIconAnim();
    m_musicOptionGroup->StopIconAnim();

    m_ctx.manager.audioMgr.StopMusic();
}

/**
 * @brief 更新：处理场景切换与选项移动
 */
void MenuScene::OnUpdate() {
    m_gameTypeOptionGroup->OnUpdate();
    m_musicOptionGroup->OnUpdate();

    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::NEXT_SCENE_KEY)) {
        m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::LOAD_SCENE_CHUNK);
        m_loadSceneCallback(Config::SettingSceneUI::NAME);
        return;
    }

    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::LAST_SCENE_KEY)) {
        m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::LOAD_SCENE_CHUNK);
        m_loadSceneCallback(Config::TitleSceneUI::NAME);
        return;
    }

    int gameTypeOptionDelta = 0;
    int musicOptionDelta = 0;
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::LEFT_KEY)) {
        --gameTypeOptionDelta;
    }
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::RIGHT_KEY)) {
        ++gameTypeOptionDelta;
    }
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::UP_KEY)) {
        --musicOptionDelta;
    }
    if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::DOWN_KEY)) {
        ++musicOptionDelta;
    }

    int preMusicOptionIdx = m_ctx.game.setting.GetMusicOptionIdx();
    m_ctx.game.setting.AdjustGameTypeOptionIdx(gameTypeOptionDelta);
    m_ctx.game.setting.AdjustMusicOptionIdx(musicOptionDelta);

    if (gameTypeOptionDelta != 0 || musicOptionDelta != 0) {
        m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::OPTION_CHUNK);
    }
    // 音乐选项变化时切换到对应背景音乐
    if (preMusicOptionIdx != m_ctx.game.setting.GetMusicOptionIdx()) {
        m_ctx.manager.audioMgr.StopMusic();
        auto bgm = m_ctx.game.setting.GetMusic();
        if (bgm.has_value()) {
            m_ctx.manager.audioMgr.PlayMusic(m_ctx.manager.resourceMgr, bgm.value());
        }
    }
}

/**
 * @brief 渲染背景与两个选项组
 */
void MenuScene::RenderContent() {
    m_menuImg->OnRender();

    m_gameTypeOptionGroup->RenderTitle();
    m_gameTypeOptionGroup->RenderOptions();
    m_gameTypeOptionGroup->RenderIcons(m_ctx.game.setting.GetGameTypeOptionIdx());

    m_musicOptionGroup->RenderTitle();
    m_musicOptionGroup->RenderOptions();
    m_musicOptionGroup->RenderIcons(m_ctx.game.setting.GetMusicOptionIdx());
}