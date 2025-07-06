#include "scene/pausescene.h"
#include "conf/sceneconf.h"

PauseScene::PauseScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback, PAUSE_SCENE::BGCOLOR)
    {}

void PauseScene::onEnter() {

}

void PauseScene::onExit() {
    
}

void PauseScene::onInput() {
    
}

void PauseScene::onUpdate() {
    
}

void PauseScene::renderContent() {

}