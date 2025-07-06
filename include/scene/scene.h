#pragma once

#include "core/context.h"
#include <functional>

class Scene {
protected:
    Context& m_ctx;
    std::function<void(const std::string&)> m_loadSceneCallback;

    SDL_Color m_bgColor;

public:
    Scene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback, SDL_Color m_bgColor);
    ~Scene() = default;

    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void onInput() = 0;
    virtual void onUpdate() = 0;
    void onRender();
    void renderBGColor();
    virtual void renderContent() = 0;
};