#define SDL_MAIN_HANDLED

#include "conf/basicconf.h"
#include "core/context.h"
#include "scene/scenemanager.h"
#include <SDL_Image.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // SDL 初始化
    SDLInitializer init;
    if (!init.isSuccess()) {
        return 1;
    }
    
    {
        // 读取窗口图标
        UniqueSurface icon(IMG_Load((IMAGE_DIR + ICON_IMAGE_PATH).c_str()));
        if (!icon) {
            std::cerr << "Load Icon Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        // 创建 SDL 窗口
        UniqueWindow window(
            SDL_CreateWindow(SCREEN_TITLE.c_str(), 
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH, SCREEN_HEIGHT, 
                SDL_WINDOW_SHOWN
            )
        );
        if (!window) {
            std::cerr << "Create Window Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        SDL_SetWindowIcon(window.get(), icon.get());

        // 创建 SDL 渲染器 
        UniqueRenderer renderer(
            SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED)
        );
        if (!renderer) {
            std::cerr << "Create Renderer Error: " << SDL_GetError() << std::endl;
            return 1;
        }

        // 创建资源管理器，加载资源
        ResourceManager& resourceManager = ResourceManager::getInstance();
        if (!resourceManager.loadResource(renderer.get())) {
            std::cerr << "Load Resource Error: " << SDL_GetError() << std::endl;
            resourceManager.destroyResource();
            return 1;
        }

        // 创建音效管理器&输入管理器
        AudioManager& audioManager = AudioManager::getInstance();
        InputManager& inputManager = InputManager::getInstance();

        // 初始化游戏设置
        Settings& settings = Settings::getInstance();

        // 创建上下文
        Context ctx(resourceManager, audioManager, inputManager, settings, renderer.get());
        // 创建场景管理器
        SceneManager& sceneManager = SceneManager::getInstance(ctx);

        // 主循环
        bool running = true;
        while (running) {
            // 输入管理器每帧刷新
            inputManager.beginFrame();

            // 接收事件
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                // 退出
                if (event.type == SDL_QUIT) {
                    running = false;
                }
                // 输入事件处理
                inputManager.processEvent(event);
            }

            // 每帧更新与渲染
            sceneManager.onUpdate();
            sceneManager.onRender();

            // 延迟一帧时长
            SDL_Delay(MSPF);
        }

        // 停止所有音乐与音效播放
        audioManager.stopChunk();
        audioManager.stopMusic();

        // 退出游戏时，销毁资源
        resourceManager.destroyResource();
    }
    
    return 0;
}