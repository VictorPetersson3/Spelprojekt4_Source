#pragma once
#include "MenuObject.h"
#include "UISlider.h"

class UIImage;
class ControllerLayOutState;

class OptionsMenu :
    public MenuObject
{
public:
    OptionsMenu() = default;
    ~OptionsMenu() = default;
    void Init(const EStateType& aState) final;
    void Update() final;
    void Render() final;
    void OnPushed() final;
private:
    void BackButtonPress();
    void EmptyFunction();
    void ControllerButtonFunction();
    void MusicSliderFunction(float aValue);
    void EffectSliderFunction(float aValue);
    std::unique_ptr<UIImage> myBackground;
    std::unique_ptr<UIImage> mySliderBackground;
    std::unique_ptr<UISlider> mySliderMusic;
    std::unique_ptr<UISlider> mySliderEffects;
    std::shared_ptr<ControllerLayOutState> myControllerLayout;
    int myCurrentHoveredButton = 0;
};

