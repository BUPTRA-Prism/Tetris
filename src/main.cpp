/**
 * @file main.cpp
 * @brief 程序入口，初始化 SDL 与各子系统并启动主循环
 */
#include "config/basic.h"
#include "config/resource.h"
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
    SDL_Event event;

    // 主循环：处理输入、更新与渲染，并做帧时间控制
    while (running) {
        Uint32 start = SDL_GetTicks();

        inputMgr.BeginFrame();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            inputMgr.ProcessEvent(event);
        }

        sceneMgr.OnUpdate();
        sceneMgr.OnRender();

        Uint32 finish = SDL_GetTicks();
        Uint32 duration = finish - start;
        if (duration < Config::Basic::FRAME_TIME) {
            SDL_Delay(Config::Basic::FRAME_TIME - duration);
        }
    }

    return 0;
}