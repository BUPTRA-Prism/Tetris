#include "scene/gamescene.h"
#include "conf/sceneconf.h"

GameScene::GameScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback)
    : Scene(ctx, loadSceneCallback, GAME_SCENE::BGCOLOR)
    {}

void GameScene::onEnter() {

}

void GameScene::onExit() {
    
}

void GameScene::onInput() {
    
}

void GameScene::onUpdate() {
    
}

void GameScene::renderContent() {
    
}