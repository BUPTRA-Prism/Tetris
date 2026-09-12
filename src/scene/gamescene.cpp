/**
 * @file gamescene.cpp
 * @brief 游戏场景实现
 */
#include "scene/gamescene.h"
#include "config/key.h"
#include "config/resource.h"
#include "config/rule.h"
#include "mysdl/render.h"
#include "util/stringutils.h"
#include "game/setting.h"
#include "game/leaderboard.h"
#include "game/logic.h"
#include "manager/audiomanager.h"
#include "manager/inputmanager.h"
#include "framework/game.h"
#include "framework/manager.h"
#include "framework/context.h"
#include <string>

/**
 * @brief 构造游戏场景，创建各 HUD 文本与方块/结束图片
 */
GameScene::GameScene(Context& ctx, std::function<void(std::string_view)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback)
    , m_paused(false)
    , m_fallTotalFrame(0)
    , m_fallCompletedFrame(0)
    , m_softFall(false)
    , m_softFallLines(0)
    , m_moveHorizontalTotalFrame(0)
    , m_moveHorizontalCompletedFrame(0)
    , m_curHorizontalDelta(0)
    , m_generateDelayTotalFrame(0)
    , m_generateDelayCompletedFrame(0)
    , m_eraseStep(0)
    , m_stepEraseTotalFrame(Config::Game::STEP_ERASE_TOTAL_FRAME)
    , m_stepEraseCompletedFrame(0) {
    m_pauseText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::GameSceneUI::PAUSE_TEXT_STR);
    m_gameImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, "");
    m_gameTypeText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");
    m_countText.resize(ctx.game.logic.GetTetrominoTypes().size());
    for (auto& text: m_countText) {
        text = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");
    }
    m_linesText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::GameSceneUI::LINES_TEXT_STR);
    m_linesNumText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");
    m_hiScoreText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::GameSceneUI::HISCORE_TEXT_STR);
    m_hiScoreNumText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");
    m_scoreText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::UICommon::SCORE_TEXT_STR);
    m_scoreNumText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");
    m_nextTetrominoText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::GameSceneUI::NEXT_TETROMINO_TEXT_STR);
    m_levelText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::UICommon::LEVEL_TEXT_STR);
    m_levelNumText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");
    m_heightText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, Config::UICommon::HEIGHT_TEXT_STR);
    m_heightNumText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");
    m_blockBaseImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::BLOCK_BASE_IMG);
    m_blockSolidPatternImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::BLOCK_SOLID_PATTERN_IMG);
    m_blockHollowPatternImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::BLOCK_HOLLOW_PATTERN_IMG);
    m_blockIconBaseImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::BLOCK_ICON_BASE_IMG);
    m_blockIconSolidPatternImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::BLOCK_ICON_SOLID_PATTERN_IMG);
    m_blockIconHollowPatternImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::BLOCK_ICON_HOLLOW_PATTERN_IMG);
    m_finishOuterPanelImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::FINISH_OUTER_PANEL_IMG);
    m_finishInnerPanelImg = std::make_unique<Image>(ctx.manager.resourceMgr, ctx.renderer, Resource::Image::FINISH_INNER_PANEL_IMG);
    m_finishText = std::make_unique<Text>(ctx.manager.resourceMgr, ctx.renderer, "");
}

/**
 * @brief 进入场景，重置对局并按设置刷新 HUD 与背景音乐
 */
void GameScene::OnEnter() {
    m_ctx.game.logic.Reset(
        m_ctx.game.setting.GetGameType(),
        m_ctx.game.setting.GetLevel(),
        m_ctx.game.setting.GetHeight()
    );
    m_state = State::Generate;

    switch (m_ctx.game.setting.GetGameType()) {
        case Setting::GameType::TypeA: {
            m_gameImg->SetTexture(m_ctx.manager.resourceMgr, Resource::Image::GAME_A_IMG);
            m_gameTypeText->SetStr(Config::UICommon::GAME_TYPE_A_TEXT_STR);
            break;
        }
        case Setting::GameType::TypeB: {
            m_gameImg->SetTexture(m_ctx.manager.resourceMgr, Resource::Image::GAME_B_IMG);
            m_gameTypeText->SetStr(Config::UICommon::GAME_TYPE_B_TEXT_STR);
            break;
        }
        default: {
            m_gameImg->SetTexture(m_ctx.manager.resourceMgr, "");
            m_gameTypeText->SetStr("");
            break;
        }
    }

    for (size_t i = 0; i < m_countText.size(); ++i) {
        m_countText[i]->SetStr(
            Util::Int2String(m_ctx.game.logic.GetTetrominoCnt(static_cast<Rule::TetrominoType>(i)), Config::UICommon::COUNT_NUM_DIGITS)
        );
    }
    m_linesNumText->SetStr(Util::Int2String(m_ctx.game.logic.GetLinesCnt(), Config::UICommon::COUNT_NUM_DIGITS));
    m_hiScoreNumText->SetStr(Util::Int2String(m_ctx.game.leaderBoard.GetHiScore(m_ctx.game.setting.GetGameType()), Config::UICommon::SCORE_NUM_DIGITS));
    m_scoreNumText->SetStr(Util::Int2String(m_ctx.game.logic.GetScore(), Config::UICommon::SCORE_NUM_DIGITS));
    m_levelNumText->SetStr(Util::Int2String(m_ctx.game.logic.GetLevel(), Config::UICommon::LEVEL_NUM_DIGITS));
    m_heightNumText->SetStr(std::to_string(m_ctx.game.logic.GetHeight()));

    auto bgm = m_ctx.game.setting.GetMusic();
    if (bgm.has_value()) {
        m_ctx.manager.audioMgr.PlayMusic(m_ctx.manager.resourceMgr, bgm.value());
    }
}

/**
 * @brief 退出场景，停止音乐
 */
void GameScene::OnExit() {
    m_ctx.manager.audioMgr.StopMusic();
}

/**
 * @brief 更新：处理暂停状态与对局状态机
 */
void GameScene::OnUpdate() {
    // 结束时不可暂停；否则按暂停键切换
    if (m_state == State::Win || m_state == State::Lose) {
        m_paused = false;
    } else if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::PAUSE_KEY)) {
        m_paused = !m_paused;
        if (m_paused) {
            m_ctx.manager.audioMgr.PauseMusic();
            m_ctx.manager.audioMgr.PauseChunk();
            m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::PAUSE_CHUNK);
        } else {
            m_ctx.manager.audioMgr.ResumeMusic();
            m_ctx.manager.audioMgr.ResumeChunk();
        }
    }
    
    if (m_paused) {
        return;
    }

    switch (m_state) {
        case State::Generate: {
            // 重置各阶段计时与状态
            m_fallTotalFrame = 0;
            m_fallCompletedFrame = 0;
            m_softFall = false;
            m_softFallLines = 0;
            m_moveHorizontalTotalFrame = 0;
            m_moveHorizontalCompletedFrame = 0;
            m_curHorizontalDelta = 0;
            m_generateDelayTotalFrame = 0;
            m_generateDelayCompletedFrame = 0;
            m_eraseStep = 0;
            m_stepEraseCompletedFrame = 0;

            bool generate = m_ctx.game.logic.Generate();
            auto curTotrominoType = m_ctx.game.logic.GetCurTetrominoType();
            if (curTotrominoType.has_value()) {
                int count = m_ctx.game.logic.GetTetrominoCnt(curTotrominoType.value());
                m_countText[static_cast<size_t>(curTotrominoType.value())]->SetStr(
                    Util::Int2String(count, Config::UICommon::COUNT_NUM_DIGITS)
                );
            }
            
            m_state = State::Move;
            // 生成失败意味着顶部堆满，判定失败
            if (!generate) {
                m_finishText->SetStr(Config::GameSceneUI::FINISH_TEXT_LOSE_STR);
                m_ctx.manager.audioMgr.PlayMusic(m_ctx.manager.resourceMgr, Resource::Audio::LOSE_MUSIC, 1);
                m_state = State::Lose;
            }

            break;
        }
        case State::Move: {
            // 处理水平移动，首次移动经历 DAS 延迟，持续按住按 ARR 自动重复
            int horizontalDelta = 0;
            if (m_ctx.manager.inputMgr.IsKeyDown(Config::Key::LEFT_KEY)) {
                --horizontalDelta;
            }
            if (m_ctx.manager.inputMgr.IsKeyDown(Config::Key::RIGHT_KEY)) {
                ++horizontalDelta;
            }
            if (horizontalDelta != 0) {
                if (horizontalDelta != m_curHorizontalDelta) {
                    m_ctx.game.logic.MoveHorizontal(horizontalDelta);
                    m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::MOVE_CHUNK);
                    m_moveHorizontalTotalFrame = Config::Game::DAS_TOTAL_FRAME;
                    m_moveHorizontalCompletedFrame = 0;
                } else {
                    ++m_moveHorizontalCompletedFrame;
                    if (m_moveHorizontalCompletedFrame >= m_moveHorizontalTotalFrame) {
                        m_ctx.game.logic.MoveHorizontal(horizontalDelta);
                        m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::MOVE_CHUNK);
                        m_moveHorizontalTotalFrame = Config::Game::ARR_TOTAL_FRAME;
                        m_moveHorizontalCompletedFrame = 0;
                    }
                }
            } else {
                m_moveHorizontalTotalFrame = 0;
                m_moveHorizontalCompletedFrame = 0;
            }
            m_curHorizontalDelta = horizontalDelta;

            // 处理旋转
            if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::ROTATE_CW_KEY)) {
                m_ctx.game.logic.Rotate(1);
                m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::ROTATE_CHUNK);
            }
            else if (m_ctx.manager.inputMgr.IsKeyPressed(Config::Key::ROTATE_CCW_KEY)) {
                m_ctx.game.logic.Rotate(-1);
                m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::ROTATE_CHUNK);
            }

            // 处理下落，软降时使用更快的帧间隔
            m_softFall = m_ctx.manager.inputMgr.IsKeyDown(Config::Key::DOWN_KEY);
            m_fallTotalFrame = Config::Game::GetFallTotalFrame(m_ctx.game.logic.GetLevel());
            if (m_softFall) {
                m_fallTotalFrame = Config::Game::SOFT_FALL_TOTAL_FRAME;
            }
            ++m_fallCompletedFrame;
            if (m_fallCompletedFrame >= m_fallTotalFrame) {
                if (!m_ctx.game.logic.Fall()) {
                    m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::LAND_CHUNK);
                    m_state = State::CheckErase;
                } else {
                    m_fallCompletedFrame = 0;
                    m_softFallLines = m_softFall ? (m_softFallLines + 1) : 0;
                }
            }

            break;
        }
        case State::CheckErase: {
            int eraseCnt = m_ctx.game.logic.CheckEraseLines();
            if (eraseCnt != 0) {
                auto bgm = eraseCnt == Config::Game::ERASE_MAX_COUNT ? Resource::Audio::ERASE_FOUR_CHUNK : Resource::Audio::ERASE_CHUNK;
                m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, bgm);
                m_state = State::Erase;
            } else {
                m_state = State::Calculate;
            }

            break;
        }
        case State::Erase: {
            // 按固定帧间隔推进逐块消除，完成后压实行
            ++m_stepEraseCompletedFrame;
            if (m_stepEraseCompletedFrame >= m_stepEraseTotalFrame) {
                if (m_ctx.game.logic.StepErase(m_eraseStep++)) {
                    m_stepEraseCompletedFrame = 0;
                } else {
                    m_ctx.game.logic.Erase();
                    m_state = State::Calculate;
                }
            }

            break;
        }
        case State::Calculate: {
            int preLevel = m_ctx.game.logic.GetLevel();
            m_ctx.game.logic.Calculate(m_ctx.game.setting.GetGameType(), m_softFallLines);
            int curLevel = m_ctx.game.logic.GetLevel();

            m_linesNumText->SetStr(Util::Int2String(m_ctx.game.logic.GetLinesCnt(), Config::UICommon::COUNT_NUM_DIGITS));
            m_scoreNumText->SetStr(Util::Int2String(m_ctx.game.logic.GetScore(), Config::UICommon::SCORE_NUM_DIGITS));
            if (preLevel != curLevel) {
                m_ctx.manager.audioMgr.PlayChunk(m_ctx.manager.resourceMgr, Resource::Audio::LEVEL_UP_CHUNK);
                m_levelNumText->SetStr(Util::Int2String(curLevel, Config::UICommon::LEVEL_NUM_DIGITS));
            }

            m_state = State::GenerateDelay;
            // B 类型行数清零即通关，追加加成分数
            if (m_ctx.game.setting.GetGameType() == Setting::GameType::TypeB && m_ctx.game.logic.GetLinesCnt() == 0) {
                m_ctx.game.logic.AddBuffScore(m_ctx.game.logic.GetLevel(), m_ctx.game.logic.GetHeight());
                m_scoreNumText->SetStr(Util::Int2String(m_ctx.game.logic.GetScore(), Config::UICommon::SCORE_NUM_DIGITS));
                m_finishText->SetStr(Config::GameSceneUI::FINISH_TEXT_WIN_STR);
                m_ctx.manager.audioMgr.PlayMusic(m_ctx.manager.resourceMgr, Resource::Audio::WIN_MUSIC, 1);
                m_state = State::Win;
            } else {
                m_generateDelayTotalFrame = Config::Game::CalculateGenerateDelayFrame(m_ctx.game.logic.GetLockRow());
            }

            break;
        }
        case State::GenerateDelay: {
            ++m_generateDelayCompletedFrame;
            if (m_generateDelayCompletedFrame >= m_generateDelayTotalFrame) {
                m_generateDelayCompletedFrame = 0;
                m_state = State::Generate;
            }
            
            break;
        }
        case State::Win: {
            // 胜利音乐播完后写入榜单并跳转
            if (!m_ctx.manager.audioMgr.IsMusicPlaying()) {
                bool rank = m_ctx.game.leaderBoard.Insert(m_ctx.game.setting.GetGameType(), m_ctx.game.logic.GetScore(), m_ctx.game.setting.GetLevel());
                if (rank) {
                    m_loadSceneCallback(Config::RankSceneUI::NAME);
                } else {
                    m_loadSceneCallback(Config::SettingSceneUI::NAME);
                }
            }

            break;
        }
        case State::Lose: {
            // 失败音乐播完后跳转；B 类型不进入排行榜，A 类型按排名跳转
            if (!m_ctx.manager.audioMgr.IsMusicPlaying()) {
                if (m_ctx.game.setting.GetGameType() == Setting::GameType::TypeB) {
                    m_loadSceneCallback(Config::SettingSceneUI::NAME);
                } else {
                    bool rank = m_ctx.game.leaderBoard.Insert(m_ctx.game.setting.GetGameType(), m_ctx.game.logic.GetScore(), m_ctx.game.logic.GetLevel());
                    if (rank) {
                        m_loadSceneCallback(Config::RankSceneUI::NAME);
                    } else {
                        m_loadSceneCallback(Config::SettingSceneUI::NAME);
                    }
                }
            }

            break;
        }
        default: break;
    }
}

/**
 * @brief 渲染游戏区、HUD 与结算面板
 */
void GameScene::RenderContent() {
    if (m_paused) {
        m_pauseText->OnRender(MySDL::RenderParams{
            Config::GameSceneUI::PAUSE_TEXT_POS,
            Config::GameSceneUI::PAUSE_TEXT_COLOR 
        });
        return;
    }

    auto levelColor = Config::GameSceneUI::GetLevelColor(m_ctx.game.logic.GetLevel());

    m_gameImg->OnRender();

    m_gameTypeText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::GAME_TYPE_TEXT_POS });

    // 渲染各方块图标与使用计数
    for (size_t i = 0; i < m_countText.size(); ++i) {
        auto tetrominoType = static_cast<Rule::TetrominoType>(i);
        auto blockType = m_ctx.game.logic.GetTetrominoBlockType(tetrominoType);
        if (blockType != Config::GameSceneUI::BlockType::Blank) {
            const auto rotatePosDelta = m_ctx.game.logic.GetDefaultRotatePosDelta(tetrominoType);
            SDL_Point anchor = m_ctx.game.logic.GetIconPos(tetrominoType);

            for (auto& blockPosDelta: rotatePosDelta) {
                SDL_Point pos = SDL_Point{
                    anchor.x + Config::GameSceneUI::BLOCK_ICON_SPACING * blockPosDelta.second,
                    anchor.y - Config::GameSceneUI::BLOCK_ICON_SPACING * blockPosDelta.first,
                };
                RenderBlock(blockType, pos, levelColor, m_blockIconBaseImg.get(), m_blockIconSolidPatternImg.get(), m_blockIconHollowPatternImg.get());
            }
        }

        m_countText[i]->OnRender(MySDL::RenderParams{
            SDL_Point{
                Config::GameSceneUI::TETROMINO_COUNT_POS.x,
                Config::GameSceneUI::TETROMINO_COUNT_POS.y + Config::GameSceneUI::TETROMINO_COUNT_SPACING_Y * static_cast<int>(i)
            },
            Config::GameSceneUI::TETROMINO_COUNT_COLOR
        });
    }

    m_linesText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::LINES_TEXT_POS });
    m_linesNumText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::LINES_NUM_POS });
    m_hiScoreText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::HISCORE_TEXT_POS });
    m_hiScoreNumText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::HISCORE_NUM_POS });
    m_scoreText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::SCORE_TEXT_POS });
    m_scoreNumText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::SCORE_NUM_POS });

    // 渲染下一个方块预览
    m_nextTetrominoText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::NEXT_TETROMINO_TEXT_POS });
    auto nextTetrominoType = m_ctx.game.logic.GetNextTetrominoType();
    if (nextTetrominoType.has_value()) {
        auto blockType = m_ctx.game.logic.GetTetrominoBlockType(nextTetrominoType.value());
        if (blockType != Config::GameSceneUI::BlockType::Blank) {
            const auto rotatePosDelta = m_ctx.game.logic.GetDefaultRotatePosDelta(nextTetrominoType.value());
            SDL_Point anchor = Config::GameSceneUI::NEXT_TETROMINO_DEFAULT_POS;
            switch (nextTetrominoType.value()) {
                case Rule::TetrominoType::I: {
                    anchor = Config::GameSceneUI::NEXT_TETROMINO_I_POS;
                    break;
                }
                case Rule::TetrominoType::O: {
                    anchor = Config::GameSceneUI::NEXT_TETROMINO_O_POS;
                    break;
                }
                default: break;
            }

            for (auto& blockPosDelta: rotatePosDelta) {
                SDL_Point pos = SDL_Point{
                    anchor.x + Config::GameSceneUI::BLOCK_SPACING * blockPosDelta.second,
                    anchor.y - Config::GameSceneUI::BLOCK_SPACING * blockPosDelta.first,
                };
                RenderBlock(blockType, pos, levelColor, m_blockBaseImg.get(), m_blockSolidPatternImg.get(), m_blockHollowPatternImg.get());
            }
        }
    }

    m_levelText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::LEVEL_TEXT_POS });
    m_levelNumText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::LEVEL_NUM_POS });

    if (m_ctx.game.setting.GetGameType() == Setting::GameType::TypeB) {
        m_heightText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::HEIGHT_TEXT_POS });
        m_heightNumText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::HEIGHT_NUM_POS });
    }

    // 渲染游戏区（仅可见行）
    const auto& field = m_ctx.game.logic.GetField();
    for (int row = 0; row < Config::Game::FIELD_VISIBLE_HEIGHT; ++row) {
        for (int col = 0; col < Config::Game::FIELD_WIDTH; ++col) {
            SDL_Point pos = SDL_Point{
                Config::GameSceneUI::FIELD_POS.x + Config::GameSceneUI::BLOCK_SPACING * col,
                Config::GameSceneUI::FIELD_POS.y - Config::GameSceneUI::BLOCK_SPACING * row,
            };
            RenderBlock(field[row][col], pos, levelColor, m_blockBaseImg.get(), m_blockSolidPatternImg.get(), m_blockHollowPatternImg.get());
        }
    }

    // 结束面板
    if (m_state == State::Win || m_state == State::Lose) {
        m_finishOuterPanelImg->OnRender(MySDL::RenderParams{ Config::GameSceneUI::FINISH_OUTER_PANEL_POS, levelColor.light });
        m_finishInnerPanelImg->OnRender(MySDL::RenderParams{ Config::GameSceneUI::FINISH_INNER_PANEL_POS });
        m_finishText->OnRender(MySDL::RenderParams{ Config::GameSceneUI::FINISH_TEXT_POS, levelColor.dark });
    }
}

/**
 * @brief 在指定位置渲染一个方块（空白类型不绘制）
 */
void GameScene::RenderBlock(
    Config::GameSceneUI::BlockType type, 
    SDL_Point pos,
    Config::GameSceneUI::LevelColor color,
    Image* baseImg,
    Image* solidImg,
    Image* hollowImg
) {
    if (!baseImg || !solidImg || !hollowImg) {
        return;
    }

    if (type != Config::GameSceneUI::BlockType::Blank) {
        baseImg->OnRender(MySDL::RenderParams{ pos });
    }
    switch (type) {
        case Config::GameSceneUI::BlockType::DarkSolid: {
            solidImg->OnRender(MySDL::RenderParams{ pos, color.dark });
            break;
        }
        case Config::GameSceneUI::BlockType::DarkHollow: {
            hollowImg->OnRender(MySDL::RenderParams{ pos, color.dark });
            break;
        }
        case Config::GameSceneUI::BlockType::LightSolid: {
            solidImg->OnRender(MySDL::RenderParams{ pos, color.light });
            break;
        }
        default: break;
    }
}