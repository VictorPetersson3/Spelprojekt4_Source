#include "stdafx.h"
#include "EndOfLevelScreen.h"

#include "UIButton.h"
#include "UIImage.h"

#include "InputManager.h"
#include "StateManager.h"
#include "AudioManager.h"


void EndOfLevelScreen::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.4f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackToMainButton(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(1)->Init({ 0.5f, 0.7f }, "sprites/UI/OptionsMenu/B_Resolution.dds", 0, [this]() {NextLevelPress(); });


	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/settings_MenuBoard.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
}

void EndOfLevelScreen::Update()
{
	if (InputManager::GetInstance().IsKeyPressed(VK_ESCAPE))
	{
		NextLevelPress();
	}
	if (InputManager::GetInstance().IsKeyPressed('S') && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
	}
	else if (InputManager::GetInstance().IsKeyPressed('W') && myCurrentHoveredButton < GetUIButtonElementsSize())
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
}

void EndOfLevelScreen::Render()
{
	myBackground.get()->Render();
	MenuObject::Render();
}

void EndOfLevelScreen::OnPushed()
{
	SetRenderThrough(true);
}

void EndOfLevelScreen::NextLevelPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}

void EndOfLevelScreen::BackToMainButton()
{
	StateManager::GetInstance().RemoveDownToState(EStateType::eMainMenu);
}
