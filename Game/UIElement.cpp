#include "stdafx.h"
#include "UIElement.h"

void UIElement::Update()
{
	myRenderCommand->Update(myPosition);
}

void UIElement::Update(const CommonUtilities::Vector2f& aPos)
{
	myPosition = aPos;
	myRenderCommand->Update(myPosition);
}

void UIElement::Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer)
{
	myPosition = aPos;
	myRenderCommand = std::make_unique<RenderCommand>(aImagePath, aLayer, aPos);
	Activate();
}

void UIElement::Render()
{
	myRenderCommand->Render();
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

RenderCommand& UIElement::GetRenderCommand()
{
	return *myRenderCommand;
}

void UIElement::SetPosition(const CommonUtilities::Vector2f& aPos)
{
	myRenderCommand->SetSpritePosition(aPos);
	myPosition = aPos;
}

const CommonUtilities::Vector2f& UIElement::GetPosition() const
{
	return myPosition;
}