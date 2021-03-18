#include "stdafx.h"
#include "OptionsMenu.h"
#include "UIButton.h"
#include "UIImage.h"
#include "InputManager.h"
#include "StateManager.h"
#include "AudioManager.h"

void OptionsMenu::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.74f, 0.88f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(1)->Init({ 0.74f, 0.78f }, "sprites/UI/OptionsMenu/B_controls.dds", 0, [this]() {EmptyFunction(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(2)->Init({ 0.74f, 0.68f }, "sprites/UI/OptionsMenu/B_Resolution.dds", 0, [this]() {EmptyFunction(); });


	mySliderBackground = std::make_unique<UIImage>();
	mySliderBackground.get()->Init({ 0.74f, 0.54f }, "sprites/UI/OptionsMenu/B_Volume.dds", 2);
	mySliderBackground.get()->Activate();

	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.74f, 0.6f }, "sprites/UI/OptionsMenu/settings_MenuBoard.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
	myBackground.get()->Activate();

	mySliderMusic = std::make_unique<UISlider>();
	mySliderMusic.get()->Init({ 0.74f, 0.577f }, "sprites/UI/OptionsMenu/B_VolumeSlider.dds", 2, 0.723f, 0.821f, [this](float aValue) {EffectSliderFunction(aValue); });
	mySliderEffects = std::make_unique<UISlider>();
	mySliderEffects.get()->Init({ 0.74f, 0.547f }, "sprites/UI/OptionsMenu/B_VolumeSlider.dds", 2, 0.723f, 0.821f, [this](float aValue) {MusicSliderFunction(aValue); });


}

void OptionsMenu::Update()
{
	if (InputManager::GetInstance().IsKeyPressed(VK_ESCAPE))
	{
		BackButtonPress();
	}
	if (InputManager::GetInstance().IsKeyPressed('S') && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
	}
	else if (InputManager::GetInstance().IsKeyPressed('W') && myCurrentHoveredButton < 4)
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

void OptionsMenu::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}

void OptionsMenu::EmptyFunction()
{
}

void OptionsMenu::MusicSliderFunction(float aValue)
{
	AudioManager::GetInstance().SetMusicVolumeMultiplier(aValue);
}

void OptionsMenu::EffectSliderFunction(float aValue)
{
	AudioManager::GetInstance().SetEffectVolumeMultiplier(aValue);
}


