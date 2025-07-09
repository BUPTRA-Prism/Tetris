#include "scene/countscene.h"
#include "conf/sceneconf.h"

CountScene::CountScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback, COUNT_SCENE::BGCOLOR) {}

void CountScene::onEnter() {

}

void CountScene::onExit() {
    
}

void CountScene::onInput() {
    
}

void CountScene::onUpdate() {
    
}

void CountScene::renderContent() {

}