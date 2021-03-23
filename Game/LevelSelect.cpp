#include "stdafx.h"
#include "LevelSelect.h"
#include "CommonUtilities/Math.h"
#include "UIButton.h"
#include "UIImage.h"
#include "tga2d/shaders/customshader.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Timer.h"


void LevelSelect::Init(const EStateType& aState)
{
	SetStateType(aState);
	//Add levels here
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.45f, 0.5f }, "sprites/UI/LevelSelect/LevelSelect_Map_Marker.dds", 0, [this](int aLevelIndex) {MapMarkerPress(aLevelIndex); }, 0);
	
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(1)->Init({ 0.55f, 0.5f }, "sprites/UI/LevelSelect/LevelSelect_Map_Marker.dds", 0, [this](int aLevelIndex) {MapMarkerPress(aLevelIndex); }, 2);

	AddButton(std::make_shared<UIButton>());
	GetButtonElement(2)->Init({ 0.5f, 0.8f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });

	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/LevelSelect/LevelSelect_Map.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.95f, 0.95f });
	myBackground.get()->Activate();


	myPanningShader = std::make_shared<Tga2D::CCustomShader>();
	myPanningBackground = std::make_unique<UIImage>();
	myPanningBackground->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/settings_bg_tile.dds", -1);
	myPanningShader->Init("shaders/sprite_shader_panning_vs.fx", "shaders/sprite_shader_ps.fx");
	myPanningBackground.get()->GetRenderCommand().SetSamplerState(ESamplerFilter::ESamplerFilter_Bilinear, ESamplerAddressMode::ESamplerAddressMode_Wrap);
	myPanningBackground.get()->GetRenderCommand().SetTextureRect(0, 0, 2, 2);
	myPanningBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 2.0f, 2.0f });
	myPanningBackground->SetShader(*myPanningShader.get());


	myPlayerAvatar = std::make_unique<UIImage>();
	myPlayerAvatar.get()->Init({ 0.74f, 0.6f }, "sprites/UI/LevelSelect/LevelSelect_Character.dds", 2);
	myPlayerAvatar.get()->GetRenderCommand().SetSizeRelativeToImage({ 1.4f, 1.4f });
	myPlayerAvatar.get()->Activate();

}

void LevelSelect::Update()
{
	myBackground->Update(); 
	myPanningBackground->Update();

	if (myCharacterMoveTimer < 1.0f)
	{
		myCharacterMoveTimer += Timer::GetInstance().GetDeltaTime() * 2.5f;
	}

	if (InputManagerS::GetInstance().GetKeyDown(DIK_ESCAPE))
	{
		BackButtonPress();
	}
	if (InputManagerS::GetInstance().GetKeyDown(DIK_W) && myCurrentHoveredButtonVertical > 0)
	{
		myCurrentHoveredButtonVertical--;
	}
	else if (InputManagerS::GetInstance().GetKeyDown(DIK_S) && myCurrentHoveredButtonVertical < 1)
	{
		myCurrentHoveredButtonVertical++;
	}
	if (InputManagerS::GetInstance().GetKeyDown(DIK_A) && myCurrentHoveredButtonVertical != 1 && myCurrentHoveredButtonHorizontal > 0)
	{
		myCharactersPreviousIndex = myCharactersCurrentIndex;
		myCurrentHoveredButtonHorizontal--;
		myCharactersCurrentIndex = myCurrentHoveredButtonHorizontal;
		myCharacterMoveTimer = 0;
	}
	else if (InputManagerS::GetInstance().GetKeyDown(DIK_D) && myCurrentHoveredButtonVertical != 1 && myCurrentHoveredButtonHorizontal < 1)
	{
		myCharactersPreviousIndex = myCharactersCurrentIndex;
		myCurrentHoveredButtonHorizontal++;
		myCharactersCurrentIndex = myCurrentHoveredButtonHorizontal;
		myCharacterMoveTimer = 0;
	}
	if (myCurrentHoveredButtonVertical != 1)
	{
		GetButtonElement(GetUIButtonElementsSize() - 1)->SetIsHovered(false);
		GetButtonElement(GetUIButtonElementsSize() - 1)->Update();
		for (int i = 0; i < GetUIButtonElementsSize() - 1; i++)
		{
			if (i == myCurrentHoveredButtonHorizontal)
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
	else
	{
		GetButtonElement(GetUIButtonElementsSize() - 1)->SetIsHovered(true);
		GetButtonElement(GetUIButtonElementsSize() - 1)->Update();
		for (int i = 0; i < GetUIButtonElementsSize() - 1; i++)
		{
			GetButtonElement(i)->SetIsHovered(false);
			GetButtonElement(i)->Update();
		}
	}
	myPlayerAvatar->Update({
		CommonUtilities::Lerp(GetButtonElement(myCharactersPreviousIndex)->GetPosition().x, GetButtonElement(myCharactersCurrentIndex)->GetPosition().x, myCharacterMoveTimer),
		CommonUtilities::Lerp(GetButtonElement(myCharactersPreviousIndex)->GetPosition().y, GetButtonElement(myCharactersCurrentIndex)->GetPosition().y, myCharacterMoveTimer)
		});
}

void LevelSelect::Render()
{
	myPanningBackground->Render();
	myBackground->Render();
	MenuObject::Render();
	myPlayerAvatar->Render();
}

void LevelSelect::OnPushed()
{
}

void LevelSelect::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}

void LevelSelect::MapMarkerPress(int aVal)
{
	StateManager::GetInstance().AddLevelOnStack(aVal);
	printf("Pressed Map Number %i\n", aVal);
}
