#pragma once
#include "UIElement.h"

class UIButton :
    public UIElement
{
public:
    UIButton();
    ~UIButton() = default;
    void Update();
    void Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer);
    void SetIsHovered(const bool aHoverStatus);
    
private:
    bool myIsHovered;
    float myHoverCurrentScale;
    float myHoverEndScale;
    CommonUtilities::Vector2f myPosition;
    void ChangeSize();
};

