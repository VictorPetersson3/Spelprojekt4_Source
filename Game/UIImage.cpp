#include "stdafx.h"
#include "UIImage.h"


void UIImage::Update()
{
	if (GetIsActive())
	{
		UIElement::Update();
	}
}

void UIImage::Render()
{
	UIElement::Render();
}

void UIImage::SetShader(Tga2D::CCustomShader& aShader)
{
	myRenderCommand->SetShader(aShader);
}

