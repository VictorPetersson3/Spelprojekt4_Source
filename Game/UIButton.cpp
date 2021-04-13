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
	myHasReachedApex = false;
	myHoverCurrentScale = 0.55f;
	myHoverMaxScale = 0.62f;
	myHoverMinScale = 0.55f;
}

void UIButton::Update()
{
	if (GetIsActive())
	{
		ChangeSize();
		UIElement::Update();
		if (InputManagerS::GetInstance().GetKeyUp(DIK_RETURN) && myIsHovered)
		{
			if (myOnPressFunction != nullptr)
			{
				myOnPressFunction();
			}
			if (myOnPressIndexFunction != nullptr)
			{
				myOnPressIndexFunction(myOnPressIndexIndex);
			}
			AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onClick.mp3");
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

void UIButton::SetButtonScales(const float aMinScale, const float aMaxScale)
{
	myHoverMinScale = aMinScale;
	myHoverMaxScale = aMaxScale;
}



void UIButton::ChangeSize()
{
	const Tga2D::CColor hoverColor{1.25f, 1.25f, 1.25f, 1.0f};
	if (myIsHovered)
	{
		if (myHoverCurrentScale > myHoverMaxScale && !myHasReachedApex)
		{
			myHoverCurrentScale = myHoverMaxScale;
			myHasReachedApex = true;
		}
		else if (myHoverCurrentScale < myHoverMaxScale)
		{
			myHoverCurrentScale += (Timer::GetInstance().GetDeltaTime() * 4);
		}
		if (myHasReachedApex)
		{
			myHoverCurrentScale = CommonUtilities::Lerp(myHoverMaxScale, myHoverMaxScale * 1.1f, (1 + sin(Timer::GetInstance().GetTotalTime() * 2) ) * 0.5f );
		}
	}
	else
	{
		myHasReachedApex = false;
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
