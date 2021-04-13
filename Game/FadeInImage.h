#pragma once
#include "State.h"
#include "Enums.h"

class UIImage;
class FadeInImage :
    public State
{
public:
    FadeInImage() = default;
    ~FadeInImage() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
    void PlayFade(const EFadeImage aFadeImage);

    void PlayIntro();
    
private:

    void IntroLogic();


    float myFadeTimer;
    EFadeImage myImageToFade;
    int myCurrentIntroFrame;
    bool myHasReachedApex;
    bool myHasReachedEnd;
    bool myIsPlayingIntro;
    std::unique_ptr<UIImage> myBlackFadeBackground;
    std::unique_ptr<UIImage> myBlackBackground;
    std::unique_ptr<UIImage> myTga2DBackground;
    std::unique_ptr<UIImage> myGameLogoBackground;
};

