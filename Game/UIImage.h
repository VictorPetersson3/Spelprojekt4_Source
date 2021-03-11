#pragma once
#include "UIElement.h"
class UIImage :
    public UIElement
{
public:
    UIImage() = default;
    ~UIImage() = default;
    void Update() override;
    void Render();
};

