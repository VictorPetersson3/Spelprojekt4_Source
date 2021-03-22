#include "stdafx.h"
#include "OptionsMenu.h"
#include "UIButton.h"
#include "UIImage.h"
#include "InputManager.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "ControllerLayOutState.h"

void OptionsMenu::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.78f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(1)->Init({ 0.5f, 0.68f }, "sprites/UI/OptionsMenu/B_controls.dds", 0, [this]() {ControllerButtonFunction(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(2)->Init({ 0.5f, 0.58f }, "sprites/UI/OptionsMenu/B_Resolution.dds", 0, [this]() {EmptyFunction(); });


	mySliderBackground = std::make_unique<UIImage>();
	mySliderBackground.get()->Init({ 0.5f, 0.44f }, "sprites/UI/OptionsMenu/B_Volume.dds", 2);
	mySliderBackground.get()->Activate();

	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/settings_MenuBoard.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
	myBackground.get()->Activate();

	mySliderMusic = std::make_unique<UISlider>();
	mySliderMusic.get()->Init({ 0.5f, 0.477f }, "sprites/UI/OptionsMenu/B_VolumeSlider.dds", 2, 0.483f, 0.581f, [this](float aValue) {EffectSliderFunction(aValue); });
	mySliderEffects = std::make_unique<UISlider>();
	mySliderEffects.get()->Init({ 0.5f, 0.447f }, "sprites/UI/OptionsMenu/B_VolumeSlider.dds", 2, 0.483f, 0.581f, [this](float aValue) {MusicSliderFunction(aValue); });

	myControllerLayout = std::make_shared<ControllerLayOutState>();
	myControllerLayout->Init(EStateType::eControllerLayout);
}

void OptionsMenu::Update()
{
	if (InputManagerS::GetInstance().GetKeyDown(DIK_ESCAPE))
	{
		BackButtonPress();
	}
	if (InputManagerS::GetInstance().GetKeyDown('S') && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
	}
	else if (InputManagerS::GetInstance().GetKeyDown('W') && myCurrentHoveredButton < 4)
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
	if (myCurrentHoveredButton == 3)
	{
		mySliderMusic->SetIsHovered(true);
	}
	else
	{
		mySliderMusic->SetIsHovered(false);
	}
	if (myCurrentHoveredButton == 4)
	{
		mySliderEffects->SetIsHovered(true);
	}
	else
	{
		mySliderEffects->SetIsHovered(false);
	}
	mySliderMusic.get()->Update();
	mySliderEffects.get()->Update();
}

void OptionsMenu::Render()
{
	myBackground.get()->Render();
	mySliderBackground.get()->Render();
	MenuObject::Render();
	mySliderMusic.get()->Render();
	mySliderEffects.get()->Render();
}

void OptionsMenu::OnPushed()
{
	SetRenderThrough(true);
}

void OptionsMenu::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}

void OptionsMenu::EmptyFunction()
{
}

void OptionsMenu::ControllerButtonFunction()
{
	StateManager::GetInstance().AddStateOnStack(myControllerLayout);
}

void OptionsMenu::MusicSliderFunction(float aValue)
{
	AudioManager::GetInstance().SetMusicVolumeMultiplier(aValue);
}

void OptionsMenu::EffectSliderFunction(float aValue)
{
	AudioManager::GetInstance().SetEffectVolumeMultiplier(aValue);
}


