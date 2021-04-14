#include "stdafx.h"
#include "PauseMenu.h"

#include "UIButton.h"
#include "UIImage.h"

#include "InputManager.h"
#include "StateManager.h"
#include "AudioManager.h"

void PauseMenu::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>(myController));
	GetButtonElement(0)->Init({ 0.5f, 0.4f }, "sprites/UI/PauseMenu/B_Resume.dds", 0, [this]() {BackButtonPress(); });
	AddButton(std::make_shared<UIButton>(myController));
	GetButtonElement(1)->Init({ 0.5f, 0.55f }, "sprites/UI/PauseMenu/B_Settings2.dds", 0, [this]() {PressSettingsButton(); });
	GetButtonElement(1)->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
	AddButton(std::make_shared<UIButton>(myController));
	GetButtonElement(2)->Init({ 0.5f, 0.7f }, "sprites/UI/PauseMenu/B_LevelSelect.dds", 0, [this]() {PressGoToMainMenu(); });

	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/PauseMenu/Pause_MenuBoard.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
}

void PauseMenu::Update()
{
	MenuObject::UpdateInput();
	if (GetInputExit())
	{
		BackButtonPress();
	}
	if (GetInputVertical() < 0 && myCurrentHoveredButton < GetUIButtonElementsSize())
	{
		myCurrentHoveredButton++;
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
	}
	else if (GetInputVertical() > 0 && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
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
}

void PauseMenu::Render()
{
	myBackground.get()->Render();
	MenuObject::Render();
}

void PauseMenu::OnPushed()
{
	SetRenderThrough(true);
}

void PauseMenu::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}

void PauseMenu::PressGoToMainMenu()
{
	StateManager::GetInstance().RemoveDownToState(EStateType::eLevelSelect);
}

void PauseMenu::PressSettingsButton()
{
	StateManager::GetInstance().AddOptionsOnStack();
}
