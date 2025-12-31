#pragma once

#include "scene/scene.h"
#include "ui/text.h"

class SettingScene : public Scene {
private:
    enum class Setting {
        Game,
        Level,
        Handicap,
        Music
    };
    Setting m_setting;

    SDL_Texture* m_settingFrame;
    SDL_Texture* m_scoreboard;
    SDL_Texture* m_logo;
    SDL_Texture* m_arrow;

    std::unique_ptr<Text> m_scoreText;
    std::unique_ptr<Text> m_scoreNum1;
    std::unique_ptr<Text> m_scoreNum2;
    std::unique_ptr<Text> m_lineText;
    std::unique_ptr<Text> m_lineNum1;
    std::unique_ptr<Text> m_lineNum2;
    std::unique_ptr<Text> m_levelText;
    std::unique_ptr<Text> m_levelNum1;
    std::unique_ptr<Text> m_levelNum2;
    std::unique_ptr<Text> m_gameSelectText;
    std::vector<std::unique_ptr<Text>> m_gameSelectOptionText;
    std::unique_ptr<Text> m_levelSelectText;
    std::vector<std::unique_ptr<Text>> m_levelSelectOptionText;
    std::unique_ptr<Text> m_handicapSelectText;
    std::vector<std::unique_ptr<Text>> m_handicapSelectOptionText;
    std::unique_ptr<Text> m_musicSelectText;
    std::vector<std::unique_ptr<Text>> m_musicSelectOptionText;

    Mix_Music* m_music;
    Mix_Chunk* m_selectChunk;
    Mix_Chunk* m_nextSceneChunk;

public:
    SettingScene(Context& ctx, Core& core, std::function<void(const std::string&)> loadSceneCallback);
    ~SettingScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;
};