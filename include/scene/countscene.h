#pragma once

#include "scene/scene.h"
#include "ui/optionicon.h"
#include "ui/text.h"

class CountScene : public Scene {
private:
    SDL_Texture* m_countFrameTexture;
    SDL_Texture* m_typeFrameTexture;
    UniqueTexture m_recordNameIconTexture;

    std::unique_ptr<VerticalLayout> m_recordOrderLayout;
    std::unique_ptr<GridLayout> m_recordLayout;
    std::unique_ptr<HorizontalLayout> m_recordNameIconLayout;

    std::unique_ptr<Text> m_gameTypeTitle;
    std::vector<std::unique_ptr<Text>> m_countText;
    std::vector<std::unique_ptr<Text>> m_recordTitle;
    std::vector<std::unique_ptr<Text>> m_recordOrderText;
    std::vector<std::unique_ptr<Text>> m_recordNameText;
    std::vector<std::unique_ptr<Text>> m_recordScoreText;
    std::vector<std::unique_ptr<Text>> m_recordLvText;

    std::unique_ptr<OptionIcon> m_recordNameIcon;

    Mix_Music* m_countMusic;
    Mix_Chunk* m_optionChunk;
    Mix_Chunk* m_sceneChunk;

    std::string m_updateRecordName;
    int m_recordNamePosIdx;
    std::vector<int> m_recordNameCharIdx;
    int m_recordNameUpdateFrameCount;
    int m_recordNameUpdateFrameTarget;

public:
    CountScene(Context& ctx, std::function<void(const std::string&)> loadSceneCallback);
    ~CountScene() = default;

    void onEnter() override;
    void onExit() override;
    void onUpdate() override;
    void renderContent() override;
};