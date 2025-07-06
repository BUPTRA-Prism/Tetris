#include "scene/titlescene.h"
#include "conf/sceneconf.h"

TitleScene::TitleScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback, TITLE_SCENE::BGCOLOR)
    {}

void TitleScene::onEnter() {

}

void TitleScene::onExit() {
    
}

void TitleScene::onInput() {
    
}

void TitleScene::onUpdate() {
    
}

void TitleScene::renderContent() {

}