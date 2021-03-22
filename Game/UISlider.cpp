#include "stdafx.h"
#include "UISlider.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "CommonUtilities/Math.h"
#include "Timer.h"

UISlider::UISlider()
{
	mySliderFunction = nullptr;
	myIsHovered = false;
	myHoverCurrentScale = 0.55f;
	myHoverEndScale = 0.75f;
	myHoverMinScale = 0.55f;
	mySlideSpeed = 2.0f;
	myMinSliderX = 0;
	myMaxSliderX = 0;
	mySliderPosX = myMaxSliderX;
}

void UISlider::Update()
{
	if (GetIsActive())
	{
		OnHover();
		myPosition = { CommonUtilities::Lerp(myMinSliderX, myMaxSliderX, mySliderPosX) , myPosition.y };
		UIElement::Update();
	}
}

void UISlider::Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer, const float aMinX, const float aMaxX, callback_function_slider aCallback)
{
	UIElement::Init(aPos, aImagePath, aLayer); 
	mySliderFunction = aCallback;
	myHoverCurrentScale = 1;
	myPosition = aPos;
	myMinSliderX = aMinX;
	myMaxSliderX = aMaxX;
	mySliderPosX = 1;
}

void UISlider::SetIsHovered(const bool aHoverStatus)
{
	myIsHovered = aHoverStatus;
}

void UISlider::SlideSlider()
{
	float sliderDirection = 0;
	if (InputManagerS::GetInstance().GetKey('A'))
	{
		sliderDirection = -1;
		//AddSoundHere
	}
	if (InputManagerS::GetInstance().GetKey('D'))
	{
		sliderDirection = 1;
		//AddSoundHere
	}
	
	mySliderPosX += sliderDirection * mySlideSpeed * Timer::GetInstance().GetDeltaTime();
	if (mySliderPosX < 0)
	{
		mySliderPosX = 0;
	}
	if (mySliderPosX > 1)
	{
		mySliderPosX = 1;
	}
	mySliderFunction(CommonUtilities::Lerp(0.f, 1.f, mySliderPosX));
}

void UISlider::OnHover()
{
	const Tga2D::CColor hoverColor{ 1.25f, 1.25f, 1.25f, 1.0f };
	if (myIsHovered)
	{
		SlideSlider();
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
