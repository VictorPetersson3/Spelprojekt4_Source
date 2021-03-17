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
			AudioManager::GetInstance().Play2D("Audio/UI/Button/on_Click.mp3");
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
	const Tga2D::CColor hoverColor{1.1f, 1.1f, 1.1f, 1.0f};
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
	float lerpT = (myHoverCurrentScale - 1) * 4;
	myRenderCommand->SetColor(Tga2D::CColor{ 
	CommonUtilities::Lerp(1.0f, hoverColor.myR, lerpT),
	CommonUtilities::Lerp(1.0f, hoverColor.myG, lerpT),
	CommonUtilities::Lerp(1.0f, hoverColor.myB, lerpT) ,
	1.0f });
	myRenderCommand->SetSizeRelativeToImage({ myHoverCurrentScale , myHoverCurrentScale });
}
