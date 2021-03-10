#include "stdafx.h"
#include "OptionsMenu.h"
#include "UIButton.h"
#include "UIImage.h"
#include "InputManager.h"
#include "StateManager.h"

void OptionsMenu::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.75f }, "sprites/UI/BackButton.dds", 0, [this]() {BackButtonPress(); });
	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/OptionsBackground.dds", -1);
	myBackground.get()->Activate();
}

void OptionsMenu::Update()
{
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

void OptionsMenu::Render()
{
	myBackground.get()->Render();
	MenuObject::Render();
}

void OptionsMenu::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}
