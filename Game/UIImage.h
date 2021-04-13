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
    void ActivatePulse(const float aSizeTimer = 1.0f, const float aMinSize = 0.9f, const float aMaxSize = 1.1f);
private:
    void Pulsing();
    bool myIsPulsing = false;
    bool myReachedApex = false;
    float mySizeMaxTimer = 1;
    float mySizeTimer = 0;
    float mySize = 1;
    float myMinSize, myMaxSize = 0.4;
};

