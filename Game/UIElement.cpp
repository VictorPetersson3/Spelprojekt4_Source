#include "stdafx.h"
#include "UIElement.h"

void UIElement::Update()
{
	myRenderCommand->Render();
}

void UIElement::Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer)
{
	myPosition = aPos;
	myRenderCommand = std::make_unique<RenderCommand>(aImagePath, aLayer);
}

const bool UIElement::GetIsActive() const { return myIsActive; }

void UIElement::Activate()
{
	myIsActive = true;
}

void UIElement::Deactivate()
{
	myIsActive = false;
}
