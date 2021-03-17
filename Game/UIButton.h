#pragma once
#include "UIElement.h"

using callback_function = std::function<void()>;
using callback_function_index = std::function<void(int)>;

class UIButton :
    public UIElement
{
public:
    UIButton();
    ~UIButton() = default;
    void Update();
    void Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer, callback_function aCallback);
    void Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer, callback_function_index aCallback, int aIndex);
    void SetIsHovered(const bool aHoverStatus);
    
private:
    bool myIsHovered;
    int myOnPressIndexIndex;
    float myHoverCurrentScale;
    float myHoverMinScale;
    float myHoverEndScale;


    callback_function myOnPressFunction;
    callback_function_index myOnPressIndexFunction;
    void ChangeSize();
};

