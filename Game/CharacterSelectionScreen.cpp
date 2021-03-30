#include "stdafx.h"
#include "CharacterSelectionScreen.h"

#include "UIImage.h"
#include "UIButton.h"

#include "InputManager.h"
#include "StateManager.h"
#include "AudioManager.h"


void CharacterSelectionScreen::Init(const EStateType& aState)
{
	SetStateType(aState);

	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.83f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackToLevelSelectPress(); });

	myBackground = std::make_unique<UIImage>();
	myBackground->Init({0.5f, 0.5f}, "sprites/ui/OptionsMenu/settings_MenuBoard.dds", 2);

	myNormalCharacter = std::make_unique<AnimationClip>("Sprites/Player/State1/player_idle_R.dds", 0, 0);
	myNormalCharacter->Init({ 8, 1 }, {7, 1});
	myNormalCharacter->GetRenderCommand().Update({ 0.4f, 0.75f });
	myNormalCharacter->PlayAnimLoop();

	myDoubleJumpCharacter = std::make_unique<AnimationClip>("Sprites/Player/State2/player_idle_R.dds", 0, 0);
	myDoubleJumpCharacter->Init({ 8, 1 }, { 7, 1 });
	myDoubleJumpCharacter->PlayAnimLoop();
	myDoubleJumpCharacter->GetRenderCommand().Update({ 0.5f, 0.75f });
	myDoubleJumpCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });

	myGlideCharacter = std::make_unique<AnimationClip>("Sprites/Player/State3/player_idle_R.dds", 0, 0);
	myGlideCharacter->Init({ 8, 1 }, { 7, 1 });
	myGlideCharacter->PlayAnimLoop();
	myGlideCharacter->GetRenderCommand().Update({ 0.6f, 0.75f });
	myGlideCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });

	myCharacterDescription = std::make_unique<Tga2D::CText>("Text/Tomodachy.otf", Tga2D::EFontSize_18);
	myCharacterDescription->SetPosition({ 0.3f, 0.6f });
	myCharacterDescription->SetColor(Tga2D::CColor{0.0f, 0.0f, 0.0f, 1.0f});
	myTitle = std::make_unique<Tga2D::CText>("Text/Tomodachy.otf", Tga2D::EFontSize_30);
	myTitle->SetPosition({ 0.3f, 0.5f });
	myTitle->SetColor(Tga2D::CColor{ 0.0f, 0.0f, 0.0f, 1.0f });

	myNormalCharacterTitle = "Default :";
	myNormalCharacterDescription = "A normal character with nothing\n special about it.";

	myGlideCharacterTitle = "Glide :";
	myGlideCharacterDescription = "A character that glides to where he\n pleases.";

	myDoubleJumpCharacterTitle = "Double Jump :";
	myDoubleJumpCharacterDescription = "A character that does twice the\n amounts of jumps as a normal character.";

	myCurrentHoveredButton = GetUIButtonElementsSize();

}

void CharacterSelectionScreen::Update()
{
	//Logik för att hovera över 
	if (InputManagerS::GetInstance().GetKeyDown(DIK_ESCAPE))
	{
		BackToLevelSelectPress();
	}
	if (InputManagerS::GetInstance().GetKeyDown(DIK_S) && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
	}
	else if (InputManagerS::GetInstance().GetKeyDown(DIK_W) && myCurrentHoveredButton < GetUIButtonElementsSize())
	{
		myCurrentHoveredButton++;
	}

	//If hovering characters
	if (myCurrentHoveredButton == GetUIButtonElementsSize())
	{
		if (InputManagerS::GetInstance().GetKeyDown(DIK_A) && myCurrentHoveredCharacter > 0)
		{
			myCurrentHoveredCharacter--;
		}
		else if (InputManagerS::GetInstance().GetKeyDown(DIK_D) && myCurrentHoveredCharacter < 3)
		{
			myCurrentHoveredCharacter++;
		}

		switch (myCurrentHoveredCharacter)
		{
		case 0:
			myNormalCharacter->Activate();
			myNormalCharacter->SetScaleRelativeToFrame({ 1.2f, 1.2f });
			myGlideCharacter->SetScaleRelativeToFrame({ -1.0f, 1.0f });
			myDoubleJumpCharacter->SetScaleRelativeToFrame({ -1.0f, 1.0f });
			
			myTitle->SetText(myNormalCharacterTitle);
			myCharacterDescription->SetText(myNormalCharacterDescription);

			break;
		case 1:
			if (myCurrentUnlockedWorld > 1)
			{
				myDoubleJumpCharacter->Activate();
			}
			else
			{
				myDoubleJumpCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });
			}
			myNormalCharacter->SetScaleRelativeToFrame({ -1.0f, 1.0f });
			myGlideCharacter->SetScaleRelativeToFrame({ -1.0f, 1.0f });
			myDoubleJumpCharacter->SetScaleRelativeToFrame({ 1.2f, 1.2f });

			myTitle->SetText(myDoubleJumpCharacterTitle);
			myCharacterDescription->SetText(myDoubleJumpCharacterDescription);

			break;
		case 2:
			if (myCurrentUnlockedWorld > 2)
			{
				myGlideCharacter->Activate();
			}
			else
			{
				myGlideCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });
			}
			myNormalCharacter->SetScaleRelativeToFrame({ -1.0f, 1.0f });
			myGlideCharacter->SetScaleRelativeToFrame({ 1.2f, 1.2f });
			myDoubleJumpCharacter->SetScaleRelativeToFrame({ -1.0f, 1.0f });

			myTitle->SetText(myGlideCharacterTitle);
			myCharacterDescription->SetText(myGlideCharacterDescription);

			break;
		default:
			break;
		}

		if (InputManagerS::GetInstance().GetKeyDown(DIK_RETURN))
		{
			CharacterChoicePress();
		}

	}
	else
	{
		myNormalCharacter->Deactivate();
		myGlideCharacter->Deactivate();
		myDoubleJumpCharacter->Deactivate();
	}
	// UPdating Buttons
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

	myNormalCharacter->UpdateAnimation(myNormalCharacter->GetRenderCommand().GetPosition());
	myGlideCharacter->UpdateAnimation(myGlideCharacter->GetRenderCommand().GetPosition());
	myDoubleJumpCharacter->UpdateAnimation(myDoubleJumpCharacter->GetRenderCommand().GetPosition());
}

void CharacterSelectionScreen::Render()
{
	myBackground->Render();
	MenuObject::Render();
	myNormalCharacter->Render();
	myGlideCharacter->Render();
	myDoubleJumpCharacter->Render();
	myCharacterDescription->Render();
	myTitle->Render();
}

void CharacterSelectionScreen::OnPushed()
{
	SetRenderThrough(true);
}

void CharacterSelectionScreen::AddCurrentLevelIndex(const int aLevelIndex)
{
	myCurrentLevelIndex = aLevelIndex;
}

void CharacterSelectionScreen::UnlockNewWorld(EWorldLevel aWorldLevel)
{
	switch (aWorldLevel)
	{
	case EWorldLevel::eWorld2:
		if (myCurrentUnlockedWorld < 2)
		{
			myCurrentUnlockedWorld = 2;
			myDoubleJumpCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 1.0f, 1.0f, 1.0f, 1.0f });
		}
		break;
	case EWorldLevel::eWorld3:
		if (myCurrentUnlockedWorld < 3)
		{
			myCurrentUnlockedWorld = 3;
			myGlideCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 1.0f, 1.0f, 1.0f, 1.0f });
			myDoubleJumpCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 1.0f, 1.0f, 1.0f, 1.0f });
		}
		break;
	case EWorldLevel::eWorld4:
		myCurrentUnlockedWorld = 4;
		myGlideCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 1.0f, 1.0f, 1.0f, 1.0f });
		myDoubleJumpCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 1.0f, 1.0f, 1.0f, 1.0f });
		break;
	default:
		break;
	}
}

EPowerUp CharacterSelectionScreen::GetCharacterChosen()
{
	EPowerUp powerUp = static_cast<EPowerUp>(myCurrentHoveredCharacter + 1);
	return powerUp;
}

void CharacterSelectionScreen::CharacterChoicePress()
{
	bool sucessfulPress = false;
	switch (myCurrentHoveredCharacter)
	{
	case 0:
		// Load Level with this character
		myNormalCharacter;
		sucessfulPress = true;
		break;
	case 1:
		if (myCurrentUnlockedWorld > 2)
		{
			// Load Level with this character
			myDoubleJumpCharacter;
			sucessfulPress = true;
		}
		else
		{
			// Play nono sounds
		}
		break;
	case 2:
		if (myCurrentUnlockedWorld > 1)
		{
			// Load Level with this character
			myGlideCharacter;
			sucessfulPress = true;
		}
		else
		{
			// Play nono sounds not unlocked
		}
		break;
	default:
		break;
	}
	if (sucessfulPress)
	{
		StateManager::RemoveStateFromTop();
		StateManager::AddLevelOnStack(myCurrentLevelIndex);
	}
}

void CharacterSelectionScreen::BackToLevelSelectPress()
{
	switch (myCurrentHoveredCharacter)
	{
	case 1:
		if (myCurrentUnlockedWorld < 2)
		{
			myCurrentHoveredCharacter = 0;
		}
		break;
	case 2:
		if (myCurrentUnlockedWorld < 3)
		{
			myCurrentHoveredCharacter = 0;
		}
		break;
	default:
		break;
	}
	StateManager::RemoveDownToState(EStateType::eLevelSelect);
}
