#pragma once
#include "UIElement.h"

using callback_function_slider = std::function<void(float)>;

class UISlider :
    public UIElement
{
public:
    UISlider();
    ~UISlider() = default;
    void Update();
    void Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer, const float aMinX, const float aMaxX, callback_function_slider aCallback);
    void SetIsHovered(const bool aHoverStatus);

private:
    bool myIsHovered;
    float myHoverCurrentScale;
    float myHoverMinScale;
    float myHoverEndScale;

    float mySlideSpeed;
    float mySliderPosX;
    float myMinSliderX;
    float myMaxSliderX;
    float mySlideSoundTimer;

    callback_function_slider mySliderFunction;

    void SlideSlider();
    void OnHover();
};

