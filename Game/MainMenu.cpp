#include "stdafx.h"
#include "MainMenu.h"
#include "UIButton.h"
#include "InputManager.h"
#include "StateManager.h"
#include <tga2d/shaders/customshader.h>

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

	LinkString tempImagePaths[4] = { 
	"sprites/UI/MainMenu/B_Find.dds",
	"sprites/UI/MainMenu/B_Settings.dds",
	"sprites/UI/MainMenu/B_Credits.dds",
	"sprites/UI/MainMenu/B_Quit.dds" };
	for (int i = 0; i < 4; i++)
	{
		AddButton(std::make_shared<UIButton>());
	}
	for (int i = 0; i < 2; i++)
	{
		GetButtonElement(i)->Init({ 00.5f, 0.2f + 0.2f * i }, tempImagePaths[i].GetString(), 0, [this](int index) {TestMe(index);}, i);
	}
	GetButtonElement(2)->Init({ 00.5f, 0.2f + 0.2f * 2 }, tempImagePaths[2].GetString(), 0, [this]() { OptionsButtonPress(); });
	GetButtonElement(3)->Init({ 00.5f, 0.2f + 0.2f * 3 }, tempImagePaths[3].GetString(), 0, [this]() { ExitButtonPress();});
	myPanningShader = std::make_shared<Tga2D::CCustomShader>();
	myPanningBackground = std::make_unique<UIImage>();
	myPanningBackground->Init({ 0.5f, 0.5f }, "sprites/UI/MainMenu/huvudmeny_bg_tile.dds", -1);
	myPanningShader->Init("shaders/sprite_shader_panning_vs.fx", "shaders/sprite_shader_ps.fx");
	myPanningBackground.get()->GetRenderCommand().SetSamplerState(ESamplerFilter::ESamplerFilter_Bilinear, ESamplerAddressMode::ESamplerAddressMode_Wrap);
	myPanningBackground.get()->GetRenderCommand().SetTextureRect(0,0,2,2);
	myPanningBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 2.0f, 2.0f });
	myPanningBackground->SetShader(*myPanningShader.get());


	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({0.5f, 0.5f}, "sprites/UI/MainMenu/huvudmeny_fg_prince.dds", -1 );
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
	myPanningBackground->Render();
	myBackground.get()->Render();
	MenuObject::Render();
}
