#pragma once
#include "MenuObject.h"

class CutsceneManager;
class CCustomShader;
class UIImage;
class EndOfGameCutscene :
    public MenuObject
{
public:
    EndOfGameCutscene() = default;
    ~EndOfGameCutscene() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
    void OnResumed() final;
private:
    void BackButtonPress();
    void ContinueConversationPress();

    bool myConversationIsOver = false;
    bool myCutsceneIsFinished = false;
    bool myImageHasBeenSeen = false;
    int myCurrentConversation = 0;

    std::unique_ptr<UIImage> myBackground;
    std::shared_ptr<Tga2D::CCustomShader> myPanningShader;
    std::unique_ptr<UIImage> myCreditsImage;
    std::unique_ptr<UIImage> mySadKiwi;
    std::shared_ptr<CutsceneManager> myCutsceneManager;
};

