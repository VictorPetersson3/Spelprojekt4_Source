#include "stdafx.h"
#include "UIImage.h"


void UIImage::Update()
{
	if (GetIsActive())
	{
		UIElement::Update();
		myRenderCommand->Render();
	}
}

