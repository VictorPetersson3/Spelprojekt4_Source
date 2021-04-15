#include "stdafx.h"
#include "FadeInImage.h"
#include "UIImage.h"
#include "Timer.h"
#include "StateManager.h"

void FadeInImage::Init(const EStateType& aState)
{
	SetStateType(aState);

	myBlackFadeBackground = std::make_unique<UIImage>();
	myBlackFadeBackground->Init({ 0.5f, 0.5f }, "sprites/BlackSprite.dds", 2);
	myBlackFadeBackground->GetRenderCommand().SetSizeRelativeToImage({ 500.0f, 500.0f });

	myBlackBackground = std::make_unique<UIImage>();
	myBlackBackground->Init({ 0.5f, 0.5f }, "sprites/BlackSprite.dds", 2);
	myBlackBackground->GetRenderCommand().SetSizeRelativeToImage({ 500.0f, 500.0f });

	myTga2DBackground = std::make_unique<UIImage>();
	myTga2DBackground->Init({ 0.5f, 0.5f }, "sprites/tga_logo.dds", 2);
	myTga2DBackground->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });

	myGameLogoBackground = std::make_unique<UIImage>();
	myGameLogoBackground->Init({ 0.5f, 0.5f }, "sprites/HästfanDDS.dds", 2);
	myGameLogoBackground->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });
}

void FadeInImage::Update()
{
	if (myIsPlayingIntro)
	{
		IntroLogic();
	}
	else
	{
		if (myHasReachedApex)
		{
			myFadeTimer -= Timer::GetInstance().GetDeltaTime() * 0.8f;
		}
		else
		{
			if (myFadeTimer > 1.0f)
			{
				myHasReachedApex = true;
			}
			myFadeTimer = 1;
			myFadeTimer += Timer::GetInstance().GetDeltaTime() * 0.8f;
		}
		if (myFadeTimer < 0)
		{
			StateManager::GetInstance().RemoveStateFromTop();
		}
	}
}

void FadeInImage::Render()
{
	if (myIsPlayingIntro)
	{
		myBlackBackground->Render();
	}
	switch (myImageToFade)
	{
	case EFadeImage::eBlack:
		myBlackFadeBackground->GetRenderCommand().SetColor(Tga2D::CColor{ 1.0f, 1.0f, 1.0f, myFadeTimer, });
		myBlackFadeBackground->Render();
		break;
	case EFadeImage::eTgaLogo:
		myTga2DBackground->GetRenderCommand().SetColor(Tga2D::CColor{ 1.0f, 1.0f, 1.0f, myFadeTimer, });
		myTga2DBackground->Render();
		break;
	case EFadeImage::eGroupLogo:
		myGameLogoBackground->GetRenderCommand().SetColor(Tga2D::CColor{ 1.0f, 1.0f, 1.0f, myFadeTimer, });
		myGameLogoBackground->Render();
		break;
	default:
		break;
	}
}

void FadeInImage::OnPushed()
{
	SetRenderThrough(true);
}

void FadeInImage::PlayFade(const EFadeImage aFadeImage)
{
	myHasReachedApex = false;
	myHasReachedEnd = false;
	myFadeTimer = 0;
	myImageToFade = aFadeImage;
}

void FadeInImage::PlayIntro()
{
	myIsPlayingIntro = true;
	myCurrentIntroFrame = 0;
	myHasReachedEnd = true;
}

void FadeInImage::IntroLogic()
{
	switch (myCurrentIntroFrame)
	{
	case 0:
		if (myHasReachedEnd)
		{
			PlayFade(EFadeImage::eTgaLogo);
		}
		break;
	case 1:
		if (myHasReachedEnd)
		{
			PlayFade(EFadeImage::eGroupLogo);
		}
		break;
	case 2:
		StateManager::GetInstance().RemoveStateFromTop();
		myIsPlayingIntro = false;
		break;
	default:
		break;
	}

	if (myHasReachedApex)
	{
		myFadeTimer -= Timer::GetInstance().GetDeltaTime() * 0.6f;
	}
	else
	{
		if (myFadeTimer > 1.0f)
		{
			myHasReachedApex = true;
		}
		myFadeTimer += Timer::GetInstance().GetDeltaTime() * 0.75f;
	}
	if (myFadeTimer < 0)
	{
		myHasReachedEnd = true;
		myCurrentIntroFrame++;
	}
}
