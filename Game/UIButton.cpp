#include "stdafx.h"
#include "UIButton.h"
#include "Timer.h"
#include "InputManager.h"

UIButton::UIButton() 
{
	myOnPressIndexIndex = -1;
	myOnPressFunction = nullptr;
	myOnPressIndexFunction = nullptr;
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
		if (InputManager::GetInstance().IsKeyUp(VK_RETURN) && myIsHovered)
		{
			if (myOnPressFunction != nullptr)
			{
				myOnPressFunction();
			}
			if (myOnPressIndexFunction != nullptr)
			{
				myOnPressIndexFunction(myOnPressIndexIndex);
			}
		}
	}
}
void UIButton::Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer, callback_function aCallback)
{
	myOnPressFunction = aCallback;
	myOnPressIndexFunction = nullptr;
	UIElement::Init(aPos, aImagePath, aLayer);
	myHoverCurrentScale = 1;
	myPosition = aPos;
}

void UIButton::Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer, callback_function_index aCallback, int aIndex)
{
	myOnPressIndexIndex = aIndex;
	myOnPressIndexFunction = aCallback;
	myOnPressFunction = nullptr;
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
		if (myHoverCurrentScale > myHoverEndScale)
		{
			myHoverCurrentScale = myHoverEndScale;
		}
		else if (myHoverCurrentScale < myHoverEndScale)
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
