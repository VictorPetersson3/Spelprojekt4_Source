#pragma once
#include "MenuObject.h"
#include "UISlider.h"

class UIImage;
class ControllerLayOutState;
class ResolutionMenu;

class OptionsMenu :
    public MenuObject
{
public:
    OptionsMenu(XController* aControllerPointer) : MenuObject(aControllerPointer) {
        myBackground = nullptr;
        mySliderBackground = nullptr;
        mySliderMusic = nullptr;
        mySliderEffects = nullptr;
        mySliderSounds = nullptr;
        myControllerLayout = nullptr;
        myResolutionMenu = nullptr;
    }
    ~OptionsMenu() = default;
    void Init(const EStateType& aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
private:
    void BackButtonPress();
    void ControllerButtonFunction();
    void ResolutionButtonFunction();
    void MusicSliderFunction(float aValue);
    void EffectSliderFunction(float aValue);
    void SoundSliderFunction(float aValue);
    std::unique_ptr<UIImage> myBackground;
    std::unique_ptr<UIImage> mySliderBackground;
    std::unique_ptr<UISlider> mySliderMusic;
    std::unique_ptr<UISlider> mySliderEffects;
    std::unique_ptr<UISlider> mySliderSounds;
    std::shared_ptr<ControllerLayOutState> myControllerLayout;
    std::shared_ptr<ResolutionMenu> myResolutionMenu;
    int myCurrentHoveredButton = 0;
};

