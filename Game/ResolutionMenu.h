#pragma once
#include "MenuObject.h"

class UIImage;

enum class eResolutions
{
    e640,
    e960,
    e1280,
    e1600,
    e1920,
    e2560,
    eEnd
};

class ResolutionMenu :
    public MenuObject
{
public:
    ResolutionMenu();
    ~ResolutionMenu() = default;
    void Init(const EStateType & aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
private:
    void BackButtonPress();
    void PressApplyResolutionButton();
    void PressFullScreenButton();
    void ChangeSize();
    std::unique_ptr<UIImage> myBackground;
    std::unique_ptr<UIImage> myResolutionsBackground;
    CommonUtilities::GrowingArray<std::shared_ptr<UIImage>> myResolutions;
    int myCurrentHoveredButton = 0;
    int myCurrentHoveredResolution = 4;

    bool myIsFullScreen;
    float myHoverCurrentScale;
    float myHoverMinScale;
    float myHoverEndScale;

};

