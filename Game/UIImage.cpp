#include "stdafx.h"
#include "UIImage.h"
#include "CommonUtilities/Math.h"
#include "Timer.h"


void UIImage::Update()
{
	if (GetIsActive())
	{
		UIElement::Update();
	}
	if (myIsPulsing)
	{
		Pulsing();
	}
}

void UIImage::Update(const CommonUtilities::Vector2f& aPos)
{
	if (GetIsActive())
	{
		UIElement::Update(aPos);
	}
}

void UIImage::Render()
{
	if (myIsPulsing)
	{
		Pulsing();
		myRenderCommand->SetSizeRelativeToImage({ mySize, mySize });
	}
	UIElement::Render();
}

void UIImage::SetShader(Tga2D::CCustomShader& aShader)
{
	myRenderCommand->SetShader(aShader);
}

void UIImage::ActivatePulse(const float aSizeTimer, float aMinSize, float aMaxSize)
{
	myMinSize = aMinSize;
	myMaxSize = aMaxSize;
	mySizeTimer = aSizeTimer;
	myIsPulsing = true;
}

void UIImage::Pulsing()
{
	if (!myReachedApex)
	{
		if (mySizeTimer > 1)
		{
			myReachedApex = true;
		}
		mySizeTimer += Timer::GetInstance().GetDeltaTime() * 0.35f;
	}
	else
	{
		if (mySizeTimer < 0)
		{
			myReachedApex = false;
		}
		mySizeTimer -= Timer::GetInstance().GetDeltaTime() * 0.35f;
	}
	mySize = CommonUtilities::Lerp(myMinSize, myMaxSize, mySizeTimer);
}

