#include "stdafx.h"
#include "MainMenu.h"
#include "UIButton.h"
#include "InputManager.h"
#include "StateManager.h"

void MainMenu::TestMe(int aVal)
{
	printf("Hello World %i\n", aVal);
	StateManager::GetInstance().AddLevelOnStack(aVal);

}


void MainMenu::OptionsButtonPress()
{
	StateManager::GetInstance().AddOptionsOnStack();
	printf("Pressing Options\n");
}

void MainMenu::ExitButtonPress()
{
	Tga2D::CEngine::GetInstance()->Shutdown();
	printf("Pressing Exit\n");
}

void MainMenu::Init(const EStateType& aState)
{
	SetStateType(aState);
	//Skapa rapidjsonInläsning för alla Objekt som jag Initar
	std::string tempImagePaths[4] = { 
	"sprites/UI/MainMenu/Button_Play.dds",
	"sprites/UI/MainMenu/Button_LevelSelect.dds",
	"sprites/UI/MainMenu/Button_Settings.dds",
	"sprites/UI/MainMenu/Button_Exit.dds" };
	for (int i = 0; i < 4; i++)
	{
		AddButton(std::make_shared<UIButton>());
	}
	for (int i = 0; i < 2; i++)
	{
		GetButtonElement(i)->Init({ 00.5f, 0.2f + 0.2f * i }, tempImagePaths[i].c_str(), 0, [this](int index) {TestMe(index);}, i);
	}
	GetButtonElement(2)->Init({ 00.5f, 0.2f + 0.2f * 2 }, tempImagePaths[2].c_str(), 0, [this]() { OptionsButtonPress(); });
	GetButtonElement(3)->Init({ 00.5f, 0.2f + 0.2f * 3 }, tempImagePaths[3].c_str(), 0, [this]() { ExitButtonPress();});

	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({0.5f, 0.5f}, "sprites/UI/MainMenu/Image_Background.dds", -1 );
}

void MainMenu::Update()
{
	myBackground->Update();

	if (InputManager::GetInstance().IsKeyPressed('W') && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
	}
	else if (InputManager::GetInstance().IsKeyPressed('S') && myCurrentHoveredButton < 3)
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

void MainMenu::Render()
{
	myBackground.get()->Render();
	MenuObject::Render();
}
