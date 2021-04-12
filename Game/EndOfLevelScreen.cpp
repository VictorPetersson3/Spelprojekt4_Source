#include "stdafx.h"
#include "EndOfLevelScreen.h"

#include "UIButton.h"
#include "UIImage.h"

#include "InputManager.h"
#include "StateManager.h"
#include "AudioManager.h"

#include "Level.h"


EndOfLevelScreen::EndOfLevelScreen(Level* aLevelPointer)
{
	myLevelPointer = aLevelPointer;
}

void EndOfLevelScreen::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.7f }, "sprites/UI/PauseMenu/B_LevelSelect.dds", 0, [this]() {BackToMainButton(); });
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(1)->Init({ 0.5f, 0.5f }, "sprites/UI/PauseMenu/B_NextLevel.dds", 0, [this]() {NextLevelPress(); });
	myCurrentHoveredButton = 1;

	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/PauseMenu/Pause_MenuBoard.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
}

void EndOfLevelScreen::Update()
{
	if (InputManagerS::GetInstance().GetKeyDown(DIK_ESCAPE))
	{
		NextLevelPress();
	}
	if (InputManagerS::GetInstance().GetKeyDown(DIK_S) && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
	}
	else if (InputManagerS::GetInstance().GetKeyDown(DIK_W) && myCurrentHoveredButton < GetUIButtonElementsSize() - 1)
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
}

void EndOfLevelScreen::Render()
{
	myBackground.get()->Render();
	MenuObject::Render();
}

void EndOfLevelScreen::OnPushed()
{
	SetRenderThrough(true);
	StateManager::GetInstance().UnlockNextlevel(myCurrentLevel);
}

void EndOfLevelScreen::SetCurrentLevel(const int aLevelIndex)
{
	myCurrentLevel = aLevelIndex;
}

void EndOfLevelScreen::NextLevelPress()
{
	StateManager::GetInstance().AddNextLevelOnStack(myCurrentLevel);
}

void EndOfLevelScreen::BackToMainButton()
{
	StateManager::GetInstance().RemoveDownToState(EStateType::eLevelSelect);
}
