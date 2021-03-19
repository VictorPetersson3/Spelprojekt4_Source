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
};

