#include "stdafx.h"
#include "UIButton.h"
#include "Timer.h"
#include "InputManager.h"

UIButton::UIButton() 
{
	myIsHovered = false;
	myHoverCurrentScale = 0;
	myHoverEndScale = 1.25f;
}

void UIButton::Update()
{
	if (GetIsActive())
	{
		ChangeSize();
		UIElement::Update();
		if (InputManager::GetInstance().IsKeyPressed(VK_RETURN))
		{

		}
	}
}

void UIButton::Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer)
{
	UIElement::Init(aPos, aImagePath, aLayer);
	myHoverCurrentScale = 1;
	myPosition = aPos;
}

void UIButton::SetIsHovered(const bool aHoverStatus)
{
	myIsHovered = aHoverStatus;
}

void UIButton::ChangeSize()
{
	if (myIsHovered)
	{
		if (myHoverCurrentScale < myHoverEndScale)
		{
			myHoverCurrentScale += (Timer::GetInstance().GetDeltaTime() * 4);
		}
	}
	else
	{
		if (1.0f < myHoverCurrentScale)
		{
			myHoverCurrentScale -= (Timer::GetInstance().GetDeltaTime() * 4);
		}
	}
	myRenderCommand->SetSizeRelativeToImage({ myHoverCurrentScale , myHoverCurrentScale });
}
