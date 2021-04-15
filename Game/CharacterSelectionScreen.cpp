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

	AddButton(std::make_shared<UIButton>(myController));
	GetButtonElement(0)->Init({ 0.5f, 0.83f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackToLevelSelectPress(); });

	myBackground = std::make_unique<UIImage>();
	myBackground->Init({0.5f, 0.5f}, "sprites/ui/OptionsMenu/settings_MenuBoard.dds", 2);
	myBackground->GetRenderCommand().SetSizeRelativeToImage({0.75f, 0.75f});

	myNormalCharacter = std::make_unique<UIImage>();
	myNormalCharacter->Init({ 0.4f, 0.75f }, "Sprites/ui/CharacterSelect/B_CharacterSelect1.dds", 0);
	myNormalCharacter->ActivatePulse(2.0f, 0.9f, 1.0f);
	myNormalCharacter->Deactivate();

	myDoubleJumpCharacter = std::make_unique<UIImage>();
	myDoubleJumpCharacter->Init({ 0.5f, 0.55f }, "Sprites/ui/CharacterSelect/B_CharacterSelect2.dds", 0);
	myDoubleJumpCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });
	myDoubleJumpCharacter->ActivatePulse(2.0f, 0.9f, 1.0f);
	myDoubleJumpCharacter->Deactivate();

	myGlideCharacter = std::make_unique<UIImage>();
	myGlideCharacter->Init({ 0.6f, 0.75f }, "Sprites/ui/CharacterSelect/B_CharacterSelect3.dds", 0);
	myGlideCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });
	myGlideCharacter->ActivatePulse(2.0f, 0.9f, 1.0f);
	myGlideCharacter->Deactivate();

	myCharacterDescription = std::make_unique<Tga2D::CText>("Text/Tomodachy.otf", Tga2D::EFontSize_12);
	myCharacterDescription->SetPosition({ 0.37f, 0.4f });
	myCharacterDescription->SetColor(Tga2D::CColor{0.0f, 0.0f, 0.0f, 1.0f});
	myTitle = std::make_unique<Tga2D::CText>("Text/Tomodachy.otf", Tga2D::EFontSize_24);
	myTitle->SetPosition({ 0.37f, 0.35f });
	myTitle->SetColor(Tga2D::CColor{ 0.0f, 0.0f, 0.0f, 1.0f });

	myNormalCharacterTitle = "Default :";
	myNormalCharacterDescription = "Morty just being his special self.";

	myGlideCharacterTitle = "Glide :";
	myGlideCharacterDescription = "Morty with some new shiny gliders.";

	myDoubleJumpCharacterTitle = "Double Jump :";
	myDoubleJumpCharacterDescription = "Morty finally got his wings, now he \ncan jump twice as high.";

	myCurrentHoveredButton = GetUIButtonElementsSize();

}

void CharacterSelectionScreen::Update()
{
	MenuObject::UpdateInput();
	//Logik för att hovera över 
	if (GetInputExit())
	{
		BackToLevelSelectPress();
	}
	if (GetInputVertical() < 0 && myCurrentHoveredButton > 0)
	{
		myCurrentHoveredButton--;
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
	}
	else if (GetInputVertical() > 0 && myCurrentHoveredButton < GetUIButtonElementsSize())
	{
		myCurrentHoveredButton++;
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onSelect.mp3");
	}

	//If hovering characters
	if (myCurrentHoveredButton == GetUIButtonElementsSize())
	{
		if (GetInputHorizontal() < 0 && myCurrentHoveredCharacter > 0)
		{
			myCurrentHoveredCharacter--;
		}
		else if (GetInputHorizontal() > 0 && myCurrentHoveredCharacter < 2)
		{
			myCurrentHoveredCharacter++;
		}

		switch (myCurrentHoveredCharacter)
		{
		case 0:
			if (!myNormalCharacter->GetIsActive())
			{
				myNormalCharacter->Activate();
				myNormalCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });
				myGlideCharacter->GetRenderCommand().SetSizeRelativeToImage({ -0.8f, 0.8f });
				myDoubleJumpCharacter->GetRenderCommand().SetSizeRelativeToImage({ -0.8f, 0.8f });
				myGlideCharacter->Deactivate();
				myDoubleJumpCharacter->Deactivate();
				myTitle->SetText(myNormalCharacterTitle);
				myCharacterDescription->SetText(myNormalCharacterDescription);
			}

			break;
		case 1:
			if (!myDoubleJumpCharacter->GetIsActive())
			{
				if (myCurrentUnlockedWorld > 1)
				{
					myDoubleJumpCharacter->Activate();
				}
				else
				{
					myDoubleJumpCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });
				}
				myNormalCharacter->GetRenderCommand().SetSizeRelativeToImage({ -0.8f, 0.8f });
				myGlideCharacter->GetRenderCommand().SetSizeRelativeToImage({ -0.8f, 0.8f });
				myDoubleJumpCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });
				myNormalCharacter->Deactivate();
				myGlideCharacter->Deactivate();
				
				myTitle->SetText(myDoubleJumpCharacterTitle);
				myCharacterDescription->SetText(myDoubleJumpCharacterDescription);
			}
			break;
		case 2:
			if (!myGlideCharacter->GetIsActive())
			{
				if (myCurrentUnlockedWorld > 2)
				{
					myGlideCharacter->Activate();
				}
				else
				{
					myGlideCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });
				}
				myNormalCharacter->GetRenderCommand().SetSizeRelativeToImage({ -0.8f, 0.8f });
				myGlideCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });
				myDoubleJumpCharacter->GetRenderCommand().SetSizeRelativeToImage({ -0.8f, 0.8f });

				myTitle->SetText(myGlideCharacterTitle);
				myCharacterDescription->SetText(myGlideCharacterDescription);
				myNormalCharacter->Deactivate();
				myDoubleJumpCharacter->Deactivate();
			}
			break;
		default:
			break;
		}
		if (GetInputContinue())
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
	// Updating Buttons
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

	myNormalCharacter->Update();
	myGlideCharacter->Update();
	myDoubleJumpCharacter->Update();
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
		if (myCurrentUnlockedWorld > 1)
		{
			// Load Level with this character
			myDoubleJumpCharacter;
			sucessfulPress = true;
		}
		else
		{
			// Play nono sounds
			AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onReturn.mp3");
		}
		break;
	case 2:
		if (myCurrentUnlockedWorld > 2)
		{
			// Load Level with this character
			myGlideCharacter;
			sucessfulPress = true;
		}
		else
		{
			// Play nono sounds not unlocked
			AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onReturn.mp3");
		}
		break;
	default:
		break;
	}
	if (sucessfulPress)
	{
		StateManager::RemoveStateFromTop();
		StateManager::AddLevelOnStack(myCurrentLevelIndex);
		StateManager::AddAndPlayFadeOnStack(EFadeImage::eBlack);
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
