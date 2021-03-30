#include "stdafx.h"
#include "CharacterSelectionScreen.h"

#include "UIImage.h"
#include "UIButton.h"
#include "AnimationClip.h"

#include "InputManager.h"
#include "StateManager.h"
#include "AudioManager.h"

#include "tga2d/text/text.h"

void CharacterSelectionScreen::Init(const EStateType& aState)
{
	SetStateType(aState);

	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.4f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackToLevelSelectPress(); });

	myBackground = std::make_unique<UIImage>();
	myBackground->Init({0.5f, 0.5f}, "sprites/ui/OptionsMenu/settings_MenuBoard.dds", 2);

	myNormalCharacter = std::make_unique<AnimationClip>("Sprites/Player/State1/player_idle_R.dds", 0, 0);
	myNormalCharacter->Init({ 8, 1 }, {7, 1});
	myNormalCharacter->PlayAnimLoop();
	myGlideCharacter = std::make_unique<AnimationClip>("Sprites/Player/State2/player_idle_R.dds", 0, 0);
	myGlideCharacter->Init({ 8, 1 }, { 7, 1 });
	myGlideCharacter->PlayAnimLoop();
	myDoubleJumpCharacter = std::make_unique<AnimationClip>("Sprites/Player/State3/player_idle_R.dds", 0, 0);
	myDoubleJumpCharacter->Init({ 8, 1 }, { 7, 1 });
	myGlideCharacter->PlayAnimLoop();


	myCharacterDescription = std::make_unique<Tga2D::CText>();
	myCharacterDescription->SetPosition({ 0.5f, 0.75f });
	myTitle = std::make_unique<Tga2D::CText>();
	myTitle->SetPosition({ 0.5f, 0.5f });

	myNormalCharacterTitle = "The normal Default Character!";
	myNormalCharacterDescription = "A normal character with nothing special about it.";

	myGlideCharacterTitle = "The not so normal Gliding Character!";
	myGlideCharacterDescription = "A character that glides to where he pleases.";

	myDoubleJumpCharacterTitle = "Double Jumping character, kind of cool!";
	myDoubleJumpCharacterDescription = "A character that does twice the amounts of jumps as a normal character.";

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
	else if (InputManagerS::GetInstance().GetKeyDown(DIK_W) && myCurrentHoveredButton < GetUIButtonElementsSize() + 1)
	{
		myCurrentHoveredButton++;
	}

	//If hovering characters
	if (myCurrentHoveredButton == GetUIButtonElementsSize())
	{
		if (InputManagerS::GetInstance().GetKeyDown(DIK_S) && myCurrentHoveredCharacter > 0)
		{
			myCurrentHoveredCharacter--;
		}
		else if (InputManagerS::GetInstance().GetKeyDown(DIK_W) && myCurrentHoveredCharacter < 3)
		{
			myCurrentHoveredCharacter++;
		}

		switch (myCurrentHoveredCharacter)
		{
		case 0:
			myNormalCharacter->Activate();
			myNormalCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.2f, 1.2f });
			myGlideCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });
			myDoubleJumpCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });
			
			myTitle->SetText(myNormalCharacterTitle);
			myCharacterDescription->SetText(myNormalCharacterDescription);

			break;
		case 1:
			if (myCurrentUnlockedWorld > 1)
			{
				myGlideCharacter->Activate();
			}
			else
			{
				myGlideCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });
			}
			myNormalCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });
			myGlideCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.2f, 1.2f });
			myDoubleJumpCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });

			myTitle->SetText(myGlideCharacterTitle);
			myCharacterDescription->SetText(myGlideCharacterDescription);

			break;
		case 2:
			if (myCurrentUnlockedWorld > 2)
			{
				myDoubleJumpCharacter->Activate();
			}
			else
			{
				myDoubleJumpCharacter->GetRenderCommand().SetColor(Tga2D::CColor{ 0.50f, 0.50f, 0.50f, 1.0f });
			}
			myNormalCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });
			myGlideCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.0f, 1.0f });
			myDoubleJumpCharacter->GetRenderCommand().SetSizeRelativeToImage({ 1.2f, 1.2f });

			myTitle->SetText(myDoubleJumpCharacterTitle);
			myCharacterDescription->SetText(myDoubleJumpCharacterDescription);

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
	myGlideCharacter->UpdateAnimation(myNormalCharacter->GetRenderCommand().GetPosition());
	myDoubleJumpCharacter->UpdateAnimation(myNormalCharacter->GetRenderCommand().GetPosition());
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
}

void CharacterSelectionScreen::UnlockNewWorld(EWorldLevel)
{
	//Logic for unlocking a new character based on the enum nad if it is unlocked or not
}

void CharacterSelectionScreen::CharacterChoicePress()
{
	switch (myCurrentHoveredCharacter)
	{
	case 0:
		// Load Level with this character
		myNormalCharacter;
		break;
	case 1:
		if (myCurrentUnlockedWorld > 1)
		{
			// Load Level with this character
			myGlideCharacter;
		}
		else
		{
			// Play nono sounds not unlocked
		}
		break;
	case 2:
		if (myCurrentUnlockedWorld > 2)
		{
			// Load Level with this character
			myDoubleJumpCharacter;
		}
		else
		{
			// Play nono sounds
		}
		break;
	default:
		break;
	}
}

void CharacterSelectionScreen::BackToLevelSelectPress()
{
}
