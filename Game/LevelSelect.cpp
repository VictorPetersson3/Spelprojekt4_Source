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
#include "LevelSelectLoadData.h"
#include "LevelSelect_SpecificLevelData.h"


void LevelSelect::Init(const EStateType& aState)
{
	SetStateType(aState);
	

	//Add levels here and all the buttons
	myLevels_LevelData = std::make_shared<LevelSelectLoadData>();
	myLevels_LevelData->CreateLevelSelectButtonData();
	myLevels_LevelData->myLevelSelectLoadData[0]->myIsUnlocked = true;
	for (int i = 0; i < myLevels_LevelData->myLevelSelectLoadData.Size(); i++)
	{
		AddButton(std::make_shared<UIButton>());
		std::string debug = myLevels_LevelData->myLevelSelectLoadData[i]->myMapTile.GetString();
		GetButtonElement(i)->Init( myLevels_LevelData->myLevelSelectLoadData[i]->myPosition
		, myLevels_LevelData->myLevelSelectLoadData[i]->myMapTile.GetString(),
			0, [this](int i) {MapMarkerPress(i); }, i);
	}

	AddButton(std::make_shared<UIButton>());
	GetButtonElement(myLevels_LevelData->myLevelSelectLoadData.Size())->Init({ 0.5f, 0.94f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });

	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/LevelSelect/lvlmap_ph.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.72f, 0.72f });
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
	myPlayerAvatar.get()->GetRenderCommand().SetSizeRelativeToImage({ 0.6f, 0.6f });
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
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
		myCurrentHoveredButtonVertical--;
	}
	else if (InputManagerS::GetInstance().GetKeyDown(DIK_S) && myCurrentHoveredButtonVertical < 1)
	{
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
		myCurrentHoveredButtonVertical++;
	}
	if (InputManagerS::GetInstance().GetKeyDown(DIK_A) && myCurrentHoveredButtonVertical != 1 && myCurrentHoveredButtonHorizontal > 0)
	{
		myCharactersPreviousIndex = myCharactersCurrentIndex;
		myCurrentHoveredButtonHorizontal--;
		myCharactersCurrentIndex = myCurrentHoveredButtonHorizontal;
		myCharacterMoveTimer = 0;
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
	}
	else if (InputManagerS::GetInstance().GetKeyDown(DIK_D) && myCurrentHoveredButtonVertical != 1 && myCurrentHoveredButtonHorizontal < myLevels_LevelData->myLevelSelectLoadData.Size() - 1)
	{
		myCharactersPreviousIndex = myCharactersCurrentIndex;
		myCurrentHoveredButtonHorizontal++;
		myCharactersCurrentIndex = myCurrentHoveredButtonHorizontal;
		myCharacterMoveTimer = 0;
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
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
	for (int i = 0; i < myLevels_LevelData->myLevelSelectLoadData.Size(); i++)
	{
		if (!myLevels_LevelData->myLevelSelectLoadData[i]->myIsUnlocked)
		{
			GetButtonElement(i)->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });
		}
	}
	if (InputManagerS::GetInstance().GetKeyDown(DIK_L))
	{
		for (int i = 0; i < myLevels_LevelData->myLevelSelectLoadData.Size(); i++)
		{
			myLevels_LevelData->myLevelSelectLoadData[i]->myIsUnlocked = true;
		}
	}
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

LevelSelect_SpecificLevelData* LevelSelect::GetSpecificLevelData(const int aIndex) const
{
	return myLevels_LevelData->myLevelSelectLoadData[aIndex].get();
}

const int LevelSelect::GetLevelAmount() const
{
	return myLevels_LevelData->myLevelSelectLoadData.Size();
}


void LevelSelect::LoadLevelButtons()
{
}

void LevelSelect::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}

void LevelSelect::MapMarkerPress(int aVal)
{
	StateManager::AddCharacterSelectOnStack(aVal);
	printf("Pressed Map Number %i\n", aVal);
}
