#include "stdafx.h"
#include "OptionsMenu.h"
#include "UIButton.h"
#include "UIImage.h"
#include "InputManager.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "ControllerLayOutState.h"
#include "ResolutionMenu.h"

void OptionsMenu::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>(myController));
	GetButtonElement(0)->Init({ 0.5f, 0.78f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });
	AddButton(std::make_shared<UIButton>(myController));
	GetButtonElement(1)->Init({ 0.5f, 0.68f }, "sprites/UI/OptionsMenu/B_controls.dds", 0, [this]() {ControllerButtonFunction(); });

	AddButton(std::make_shared<UIButton>(myController));
	GetButtonElement(2)->Init({ 0.5f, 0.58f }, "sprites/UI/OptionsMenu/B_Resolution.dds", 0, [this]() {ResolutionButtonFunction(); });


	mySliderBackground = std::make_unique<UIImage>();
	mySliderBackground.get()->Init({ 0.5f, 0.44f }, "sprites/UI/OptionsMenu/B_Volume.dds", 2);
	mySliderBackground->GetRenderCommand().SetSizeRelativeToImage({ 0.5f, 0.5f });
	mySliderBackground.get()->Activate();

	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/settings_MenuBoard.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
	myBackground.get()->Activate();

	mySliderMusic = std::make_unique<UISlider>(myController);
	mySliderMusic.get()->Init({ 0.5f, 0.486f }, "sprites/UI/OptionsMenu/B_VolumeSlider.dds", 2, 0.483f, 0.582f, [this](float aValue) {EffectSliderFunction(aValue); });
	mySliderEffects = std::make_unique<UISlider>(myController);
	mySliderEffects.get()->Init({ 0.5f, 0.457f }, "sprites/UI/OptionsMenu/B_VolumeSlider.dds", 2, 0.483f, 0.582f, [this](float aValue) {MusicSliderFunction(aValue); });
	mySliderSounds = std::make_unique<UISlider>(myController);
	mySliderSounds.get()->Init({ 0.5f, 0.426f }, "sprites/UI/OptionsMenu/B_VolumeSlider.dds", 2, 0.419f, 0.582f, [this](float aValue) {SoundSliderFunction(aValue); });
	myControllerLayout = std::make_shared<ControllerLayOutState>(myController);
	myControllerLayout->Init(EStateType::eControllerLayout);

	myResolutionMenu = std::make_shared<ResolutionMenu>(myController);
	myResolutionMenu->Init(EStateType::eResolutionMenu);
}

void OptionsMenu::Update()
{
	MenuObject::UpdateInput();
	if (GetInputExit())
	{
		BackButtonPress();
	}
	if (GetInputVertical() < 0 && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
	}
	else if (GetInputVertical() > 0 && myCurrentHoveredButton < 5)
	{
		myCurrentHoveredButton++;
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
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
	if (myCurrentHoveredButton == 5)
	{
		mySliderSounds->SetIsHovered(true);
	}
	else
	{
		mySliderSounds->SetIsHovered(false);
	}
	mySliderMusic->Update();
	mySliderEffects->Update();
	mySliderSounds->Update();
}

void OptionsMenu::Render()
{
	myBackground.get()->Render();
	mySliderBackground.get()->Render();
	MenuObject::Render();
	mySliderMusic->Render();
	mySliderEffects->Render();
	mySliderSounds->Render();
}

void OptionsMenu::OnPushed()
{
	SetRenderThrough(true);
}

void OptionsMenu::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}


void OptionsMenu::ControllerButtonFunction()
{
	StateManager::GetInstance().AddStateOnStack(myControllerLayout);
}

void OptionsMenu::ResolutionButtonFunction()
{
	StateManager::GetInstance().AddStateOnStack(myResolutionMenu);
}

void OptionsMenu::MusicSliderFunction(float aValue)
{
	AudioManager::GetInstance().SetMusicVolumeMultiplier(aValue);
}

void OptionsMenu::EffectSliderFunction(float aValue)
{
	AudioManager::GetInstance().SetEffectVolumeMultiplier(aValue);
}

void OptionsMenu::SoundSliderFunction(float aValue)
{
	AudioManager::GetInstance().SetSoundVolumeMultiplier(aValue);
}


