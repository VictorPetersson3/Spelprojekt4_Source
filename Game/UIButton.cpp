#include "stdafx.h"
#include "UIButton.h"
#include "Timer.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "CommonUtilities/Math.h"

UIButton::UIButton() 
{
	myOnPressIndexIndex = -1;
	myOnPressFunction = nullptr;
	myOnPressIndexFunction = nullptr;
	myIsHovered = false;
	myHoverCurrentScale = 0.55f;
	myHoverEndScale = 0.65f;
	myHoverMinScale = 0.55f;
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
			AudioManager::GetInstance().PlayEffect("Audio/UI/Button/on_Click.mp3");
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
	const Tga2D::CColor hoverColor{1.25f, 1.25f, 1.25f, 1.0f};
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
		if (myHoverMinScale < myHoverCurrentScale)
		{
			myHoverCurrentScale -= (Timer::GetInstance().GetDeltaTime() * 4);
		}
		else
		{
			myHoverCurrentScale = myHoverMinScale;
		}
	}
	float lerpT = (myHoverCurrentScale - myHoverMinScale) * 4;
	myRenderCommand->SetColor(Tga2D::CColor{ 
	CommonUtilities::Lerp(1.0f, hoverColor.myR, lerpT),
	CommonUtilities::Lerp(1.0f, hoverColor.myG, lerpT),
	CommonUtilities::Lerp(1.0f, hoverColor.myB, lerpT) ,
	1.0f });
	myRenderCommand->SetSizeRelativeToImage({ myHoverCurrentScale , myHoverCurrentScale });
}
