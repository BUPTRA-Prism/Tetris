#pragma once

#include "framework/context.h"
#include "game/core.h"
#include <functional>

class Scene {
protected:
    Context& m_ctx;
    Core& m_core;
    std::function<void(const std::string&)> m_loadSceneCallback;

    SDL_Color m_bgColor;

public:
    Scene(Context& ctx, Core& core, std::function<void(const std::string&)> loadSceneCallback, SDL_Color m_bgColor = {0, 0, 0, 255});
    virtual ~Scene() = default;

    SDL_Color getBGColor() const;

    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void onUpdate() = 0;
    virtual void renderContent() = 0;
};