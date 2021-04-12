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
	if (GetIsActive())
	{
		if (myIsPulsing)
		{
			Pulsing();
		}
	}
	UIElement::Render();
}

void UIImage::SetShader(Tga2D::CCustomShader& aShader)
{
	myRenderCommand->SetShader(aShader);
}

void UIImage::ActivatePulse(const float aSizeTimer, const float aMinSize, const float aMaxSize)
{
	myMinSize = aMinSize;
	myMaxSize = aMaxSize;
	mySizeTimer = aSizeTimer;
	mySizeMaxTimer = aSizeTimer;
	myIsPulsing = true;
}

void UIImage::Pulsing()
{
	if (!myReachedApex)
	{
		if (mySizeTimer > mySizeMaxTimer)
		{
			myReachedApex = true;
		}
		mySizeTimer += Timer::GetInstance().GetDeltaTime();
	}
	else
	{
		if (mySizeTimer < 0)
		{
			myReachedApex = false;
		}
		mySizeTimer -= Timer::GetInstance().GetDeltaTime();
	}
	mySize = CommonUtilities::Lerp(myMinSize, myMaxSize, mySizeTimer / mySizeMaxTimer);
	myRenderCommand->SetSizeRelativeToImage({ mySize, mySize });
	
}

