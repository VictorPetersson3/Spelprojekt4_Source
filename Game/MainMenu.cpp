#include "stdafx.h"
#include "MainMenu.h"
#include "UIElement.h"
#include "UIButton.h"
#include "InputManager.h"
void MainMenu::Init()
{
	//Skapa rapidjsonInl�sning f�r alla Objekt som jag Initar
	std::string tempImagePaths[4] = { 
	"sprites/UI/MainMenu/Button_Play.dds",
	"sprites/UI/MainMenu/Button_LevelSelect.dds",
	"sprites/UI/MainMenu/Button_Settings.dds",
	"sprites/UI/MainMenu/Button_Exit.dds" };
	for (int i = 0; i < 4; i++)
	{
		AddButton(std::make_shared<UIButton>());
	}
	for (int i = 0; i < GetUIElementsSize(); i++)
	{
		GetElement(i)->Init({00.5f, 0.2f + 0.2f * i}, tempImagePaths[i].c_str(), 0);
	}
	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({0.5f, 0.5f}, "sprites/UI/MainMenu/Image_Background.dds", -1 );
	myBackground.get()->Activate();
	MenuObject::Activate();
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
	for (int i = 0; i < GetUIElementsSize(); i++)
	{
		if (i == myCurrentHoveredButton)
		{
			GetElement(i)->SetIsHovered(true);
		}
		else
		{
			GetElement(i)->SetIsHovered(false);
		}
		GetElement(i)->Update();
	}
	MenuObject::Render();
}
