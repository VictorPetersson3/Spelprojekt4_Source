#include "stdafx.h"
#include "ResolutionMenu.h"
#include "CommonUtilities/Math.h"

#include "UIButton.h"
#include "UIImage.h"

#include "InputManager.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "Timer.h"

ResolutionMenu::ResolutionMenu()
{
	myHoverCurrentScale = 0.55f;
	myHoverEndScale = 0.62f;
	myHoverMinScale = 0.52f;
}

void ResolutionMenu::Init(const EStateType& aState)
{
	SetStateType(aState);
	myResolutions.Init(8);

	myResolutionsBackground = std::make_unique<UIImage>();
	myResolutionsBackground.get()->Init({ 0.5f, 0.46f }, "sprites/UI/OptionsMenu/B_ResolutionSelect.dds", 2);
	myResolutionsBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });

	myResolutions.Add(std::make_shared<UIImage>());
	myResolutions[0]->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/R_360.dds", 2);
	myResolutions.Add(std::make_shared<UIImage>());
	myResolutions[1]->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/R_540.dds", 2);
	myResolutions.Add(std::make_shared<UIImage>());
	myResolutions[2]->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/R_720.dds", 2);
	myResolutions.Add(std::make_shared<UIImage>());
	myResolutions[3]->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/R_900.dds", 2);
	myResolutions.Add(std::make_shared<UIImage>());
	myResolutions[4]->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/R_1080.dds", 2);
	myResolutions.Add(std::make_shared<UIImage>());
	myResolutions[5]->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/R_1440.dds", 2);
	

	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.78f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(1)->Init({ 0.5f, 0.69f }, "sprites/UI/OptionsMenu/B_Fullscreen.dds", 0, [this]() {PressFullScreenButton(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(2)->Init({ 0.5f, 0.6f }, "sprites/UI/OptionsMenu/B_Apply.dds", 0, [this]() {PressApplyResolutionButton(); });
	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/settings_MenuBoard.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
	myIsFullScreen = false;

}

void ResolutionMenu::Update()
{
	if (InputManagerS::GetInstance().GetKeyDown(DIK_ESCAPE))
	{
		BackButtonPress();
	}
	if (InputManagerS::GetInstance().GetKeyDown(DIK_S) && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
	}
	else if (InputManagerS::GetInstance().GetKeyDown(DIK_W) && myCurrentHoveredButton < GetUIButtonElementsSize() + 1)
	{
		myCurrentHoveredButton++;
	}
	for (int i = 0; i < GetUIButtonElementsSize(); i++)
	{
		if (i == myCurrentHoveredButton)
		{
			GetButtonElement(i)->SetIsHovered(true);
		}
		else
		{
			GetButtonElement(i)->SetIsHovered(false);
		}
		GetButtonElement(i)->Update();
	}
	if (myCurrentHoveredButton == GetUIButtonElementsSize())
	{
		if (InputManagerS::GetInstance().GetKeyDown(DIK_D) && myCurrentHoveredResolution < static_cast<int>(eResolutions::eEnd) - 1)
		{
			myCurrentHoveredResolution++;
		}
		else if (InputManagerS::GetInstance().GetKeyDown(DIK_A) && myCurrentHoveredResolution > 0)
		{
			myCurrentHoveredResolution--;
		}
	}
	ChangeSize();
}

void ResolutionMenu::Render()
{
	myBackground.get()->Render();
	MenuObject::Render();
	myResolutionsBackground->Render();
	myResolutions[myCurrentHoveredResolution]->Render();
}

void ResolutionMenu::OnPushed()
{
	SetRenderThrough(true);
}

void ResolutionMenu::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}

void ResolutionMenu::PressApplyResolutionButton()
{
	switch (myCurrentHoveredResolution)
	{
	case 0:
		Tga2D::CEngine::GetInstance()->SetResolution({ 640, 360 }, true); 
		break;
	case 1:
		Tga2D::CEngine::GetInstance()->SetResolution({ 960, 540 }, true);
		break;
	case 2:
		Tga2D::CEngine::GetInstance()->SetResolution({ 1280, 720 }, true);
		break;
	case 3:
		Tga2D::CEngine::GetInstance()->SetResolution({ 1600, 900 }, true);
		break;
	case 4:
		Tga2D::CEngine::GetInstance()->SetResolution({ 1920, 1080 }, true);
		break;
	case 5:
		Tga2D::CEngine::GetInstance()->SetResolution({ 2560, 1440 }, true);
		break;
	default:
		break;
	}
}

void ResolutionMenu::PressFullScreenButton()
{
	myIsFullScreen = !myIsFullScreen;
	Tga2D::CEngine::GetInstance()->SetFullScreen(myIsFullScreen);
}

void ResolutionMenu::ChangeSize()
{
	const Tga2D::CColor hoverColor{ 1.25f, 1.25f, 1.25f, 1.0f };
	if (myCurrentHoveredButton == GetUIButtonElementsSize())
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
	myResolutions[myCurrentHoveredResolution]->GetRenderCommand().SetColor(Tga2D::CColor{
	CommonUtilities::Lerp(1.0f, hoverColor.myR, lerpT),
	CommonUtilities::Lerp(1.0f, hoverColor.myG, lerpT),
	CommonUtilities::Lerp(1.0f, hoverColor.myB, lerpT) ,
	1.0f });
	myResolutions[myCurrentHoveredResolution]->GetRenderCommand().SetSizeRelativeToImage({ myHoverCurrentScale , myHoverCurrentScale });
}

