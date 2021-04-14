#include "stdafx.h"
#include "UISlider.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "CommonUtilities/Math.h"
#include "Timer.h"
#include "XController.h"
#include "CommonUtilities/Math.h"

UISlider::UISlider(XController* aControllerPointer) : myController(aControllerPointer)
{
	mySliderFunction = nullptr;
	myIsHovered = false;
	myHoverCurrentScale = 0.55f;
	myHoverEndScale = 0.75f;
	myHoverMinScale = 0.55f;
	mySlideSpeed = 2.0f;
	myMinSliderX = 0;
	myMaxSliderX = 0;
	mySlideSoundTimer = 0;
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

int UISlider::Input()
{
	int rInput = 0;
	int lInput = 0;
	bool controllerConnected = myController->IsConnected();
	if (controllerConnected && myController->GetDPadInput().x > 0 || myController->GetLeftTumbStick().x > 0.45f)
	{
		rInput += 1;
	}
	if (InputManagerS::GetInstance().GetKey(DIK_D) || InputManagerS::GetInstance().GetKey(DIK_RIGHT))
	{
		if (rInput == 0)
		{
			rInput += 1;
		}
	}
	if (InputManagerS::GetInstance().GetKey(DIK_A) || InputManagerS::GetInstance().GetKey(DIK_LEFT))
	{
		lInput -= 1;
	}
	if (controllerConnected && myController->GetDPadInput().x < 0 || myController->GetLeftTumbStick().x < -0.45f)
	{
		if (lInput == 0)
		{
			lInput -= 1;
		}
	}
	return rInput + lInput;
}

void UISlider::SlideSlider()
{
	float sliderDirection = 0;
	if (Input() < 0 && mySliderPosX != 0)
	{
		sliderDirection = -1;
		if (mySlideSoundTimer > 0.1f)
		{
			AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSlide.mp3");
			mySlideSoundTimer = 0;
		}
		//AddSoundHere
	}
	if (Input() > 0 && mySliderPosX != 1)
	{
		sliderDirection = 1;
		if (mySlideSoundTimer > 0.1f)
		{
			AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSlide.mp3");
			mySlideSoundTimer = 0;
		}
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
	mySlideSoundTimer += Timer::GetInstance().GetDeltaTime();
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
