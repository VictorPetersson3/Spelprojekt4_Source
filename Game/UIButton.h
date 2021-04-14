#pragma once
#include "UIElement.h"

using callback_function = std::function<void()>;
using callback_function_index = std::function<void(int)>;

class XController;
class UIButton :
    public UIElement
{
public:
    UIButton(XController* aControllerPointer);
    ~UIButton() = default;
    void Update();
    void Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer, callback_function aCallback);
    void Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer, callback_function_index aCallback, int aIndex);
    void SetIsHovered(const bool aHoverStatus);
    void SetButtonScales(const float aMinScale, const float aMaxScale);
    
private:

    bool Input();

    bool myIsHovered;
    bool myHasReachedApex;
    int myOnPressIndexIndex;
    float myHoverCurrentScale;
    float myHoverMinScale;
    float myHoverMaxScale;
    XController* myController;

    callback_function myOnPressFunction;
    callback_function_index myOnPressIndexFunction;
    void ChangeSize();
};

