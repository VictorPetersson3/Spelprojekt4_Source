#pragma once
#include "UIElement.h"
class UIImage :
    public UIElement
{
public:
    UIImage() = default;
    ~UIImage() = default;
    void Update();
    void Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer);
private:
    CommonUtilities::Vector2f myPosition;
};

