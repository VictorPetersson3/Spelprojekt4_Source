#include "stdafx.h"
#include "UIImage.h"


void UIImage::Update()
{
	if (GetIsActive())
	{
		myRenderCommand->Render();
	}
}

void UIImage::Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer)
{
	myPosition = aPos;
	UIElement::Init(aPos, aImagePath, aLayer);
}
