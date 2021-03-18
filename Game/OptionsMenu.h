#pragma once
#include "MenuObject.h"
#include "UISlider.h"

class UIImage;


class OptionsMenu :
    public MenuObject
{
public:
    OptionsMenu() = default;
    ~OptionsMenu() = default;
    void Init(const EStateType& aState) final;
    void Update() final;
    void Render() final;
private:
    void BackButtonPress();
    void EmptyFunction();
    void MusicSliderFunction(float aValue);
    void EffectSliderFunction(float aValue);
    std::unique_ptr<UIImage> myBackground;
    std::unique_ptr<UIImage> mySliderBackground;
    std::unique_ptr<UISlider> mySliderMusic;
    std::unique_ptr<UISlider> mySliderEffects;
    int myCurrentHoveredButton = 0;

};

