#pragma once
#include "UIElement.h"
#include <tga2d/shaders/customshader.h>

class UIImage :
    public UIElement
{
public:
    UIImage() = default;
    ~UIImage() = default;
    void Update() override;
    void Update(const CommonUtilities::Vector2f& aPos);
    void Render();
    void SetShader(Tga2D::CCustomShader& aShader);
    void ActivatePulse(const float aSizeTimer, float aMinSize, float aMaxSize);
private:
    void Pulsing();
    bool myIsPulsing = false;
    bool myReachedApex = false;
    float mySizeTimer = 0;
    float mySize = 1;
    float myMinSize, myMaxSize = 0.4;
};

