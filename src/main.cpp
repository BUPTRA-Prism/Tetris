/**
 * @file main.cpp
 * @brief 程序入口，初始化 SDL 与各子系统并启动主循环
 */
#include "config/basic.h"
#include "mysdl/wrapper.h"
#include "game/setting.h"
#include "game/leaderboard.h"
#include "game/logic.h"
#include "manager/resourcemanager.h"
#include "manager/audiomanager.h"
#include "manager/inputmanager.h"
#include "framework/game.h"
#include "framework/manager.h"
#include "framework/context.h"
#include "scene/scenemanager.h"
#include <SDL2/SDL.h>
#include <iostream>

/**
 * @brief 程序主函数
 * @param argc 参数个数（未使用）
 * @param argv 参数数组（未使用）
 * @return 退出状态码，0 表示正常退出
 */
int main(int, char*[]) {
    // 初始化 SDL 各子系统
    MySDL::Initializer initializer;
    if (!initializer.IsValid()) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 创建窗口
    MySDL::UniqueWindow window(
        SDL_CreateWindow(
            Config::Basic::WINDOW_TITLE.data(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            Config::Basic::WINDOW_WIDTH,
            Config::Basic::WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        )
    );
    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 创建渲染器，硬件加速失败时回退到软件渲染
    SDL_Renderer* rawRenderer = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED);
    if (!rawRenderer) {
        std::cerr << "Hardware acceleration unavailable, falling back to software renderer: " << SDL_GetError() << std::endl;
        rawRenderer = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_SOFTWARE);
    }
    if (!rawRenderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    MySDL::UniqueRenderer renderer(rawRenderer);

    // 加载全部资源
    ResourceManager resourceMgr;
    if (!resourceMgr.LoadResource(renderer.get())) {
        return 1;
    }
    // 设置窗口图标
    auto icon = resourceMgr.GetIcon();
    if (icon) {
        SDL_SetWindowIcon(window.get(), icon);
    }

    // 组装依赖注入的全局上下文
    AudioManager audioMgr;
    InputManager inputMgr;
    Manager manager{ resourceMgr, audioMgr, inputMgr };

    Setting setting;
    LeaderBoard leaderBoard;
    Logic logic;
    Game game{ setting, leaderBoard, logic };

    Context ctx{ manager, game, renderer.get() };
    SceneManager sceneMgr(ctx);

    bool running = true;
    bool focused = true;             // 窗口聚焦状态
    bool pausedMusicByFocus = false; // 音乐是否因失焦被暂停
    bool pausedChunkByFocus = false; // 音效是否因失焦被暂停
    SDL_Event event;

    // 主循环：处理输入、更新与渲染，并做帧时间控制
    while (running) {
        Uint32 start = SDL_GetTicks();

        inputMgr.BeginFrame();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST && focused) {
                    focused = false;
                    inputMgr.ResetKeys();   // 失焦时清空按键状态
                    // 暂停音乐与音效
                    if (audioMgr.IsMusicPlaying()) {
                        audioMgr.PauseMusic();
                        pausedMusicByFocus = true;
                    }
                    if (audioMgr.IsChunkPlaying()) {
                        audioMgr.PauseChunk();
                        pausedChunkByFocus = true;
                    }
                } else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED && !focused) {
                    focused = true;
                    // 如果是因为失焦而暂停的音乐与音效，则恢复它们
                    if (pausedMusicByFocus) {
                        audioMgr.ResumeMusic();
                        pausedMusicByFocus = false;
                    }
                    if (pausedChunkByFocus) {
                        audioMgr.ResumeChunk();
                        pausedChunkByFocus = false;
                    }
                }
            }

            // 键盘事件由 main 检测后回填到输入管理器
            if (event.type == SDL_KEYDOWN) {
                inputMgr.SetKeyState(event.key.keysym.scancode, true);
            } else if (event.type == SDL_KEYUP) {
                inputMgr.SetKeyState(event.key.keysym.scancode, false);
            }
        }

        if (focused) {
            sceneMgr.OnUpdate();
            sceneMgr.OnRender();

            Uint32 finish = SDL_GetTicks();
            Uint32 duration = finish - start;
            if (duration < Config::Basic::FRAME_TIME) {
                SDL_Delay(Config::Basic::FRAME_TIME - duration);
            }
        } else {
            SDL_Delay(Config::Basic::FRAME_TIME);
        }
        
    }

    return 0;
}