#include "scene/pausescene.h"
#include "conf/sceneconf.h"

PauseScene::PauseScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback) {}

void PauseScene::onEnter() {

}

void PauseScene::onExit() {
    
}

void PauseScene::onUpdate() {
    
}

void PauseScene::renderContent() {

}