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
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.4f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(1)->Init({ 0.5f, 0.6f }, "sprites/UI/MainMenu/B_Settings.dds", 0, [this]() {PressSettingsButton(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(2)->Init({ 0.5f, 0.7f }, "sprites/UI/OptionsMenu/B_Resolution.dds", 0, [this]() {PressGoToMainMenu(); });


	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/settings_MenuBoard.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
}

void PauseMenu::Update()
{
	if (InputManager::GetInstance().IsKeyPressed(VK_ESCAPE))
	{
		BackButtonPress();
	}
	if (InputManager::GetInstance().IsKeyPressed('S') && myCurrentHoveredButton < GetUIButtonElementsSize())
	{
		myCurrentHoveredButton++;
	}
	else if (InputManager::GetInstance().IsKeyPressed('W') && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
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
	StateManager::GetInstance().RemoveDownToState(EStateType::eMainMenu);
}

void PauseMenu::PressSettingsButton()
{
	StateManager::GetInstance().AddOptionsOnStack();
}
