#include "stdafx.h"
#include "CreditsState.h"
#include "UIButton.h"
#include "UIImage.h"
#include "StateManager.h"
#include "InputManager.h"

void CreditsState::Init(const EStateType& aState) 
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>(myController));
	GetButtonElement(0)->Init({ 0.5f, 0.95f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });
	GetButtonElement(0)->SetIsHovered(true);


	myBackground = std::make_unique<UIImage>();
	myBackground->Init({ 0.5f, 0.5f }, "sprites/BlackSprite.dds", 2);
	myBackground->GetRenderCommand().SetSizeRelativeToImage({ 500.0f, 500.0f });
	myBackground->GetRenderCommand().SetColor(Tga2D::CColor{ 1.0f, 1.0f, 1.0f, 0.75f });

	myCredits = std::make_unique<UIImage>();
	myCredits->Init({ 0.5f, 0.5f }, "sprites/UI/Credits.dds", 2);
	myCredits->GetRenderCommand().SetSizeRelativeToImage({ 0.5f, 0.5f });
}

void CreditsState::Update()
{
	MenuObject::UpdateInput();
	if (GetInputExit())
	{
		BackButtonPress();
	}
	GetButtonElement(0)->Update();
}

void CreditsState::Render()
{
	myBackground->Render();
	myCredits->Render();
	MenuObject::Render();
}

void CreditsState::OnPushed()
{
	SetRenderThrough(true);
}

void CreditsState::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}
