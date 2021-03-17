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
    void Render();
    void SetShader(Tga2D::CCustomShader& aShader);
};

