#include "stdafx.h"
#include "ControllerLayOutState.h"
#include "UIButton.h"
#include "UIImage.h"
#include "StateManager.h"
#include "InputManager.h"

void ControllerLayOutState::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>(myController));
	GetButtonElement(0)->Init({ 0.5f, 0.78f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });
	GetButtonElement(0)->SetIsHovered(true);


	myBackground = std::make_unique<UIImage>();
	myBackground->Init({ 0.5f, 0.5f }, "sprites/BlackSprite.dds", 2);
	myBackground->GetRenderCommand().SetSizeRelativeToImage({500.0f, 500.0f});
	myBackground->GetRenderCommand().SetColor(Tga2D::CColor{1.0f, 1.0f, 1.0f, 0.75f});

	myControllerLayout = std::make_unique<UIImage>();
	myControllerLayout->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/ControlKeys.dds", 2);
	myControllerLayout->GetRenderCommand().SetSizeRelativeToImage({ 0.5f, 0.5f });
}

void ControllerLayOutState::Update()
{
	MenuObject::UpdateInput();
	if (GetInputExit())
	{
		BackButtonPress();
	}
	GetButtonElement(0)->Update();
}

void ControllerLayOutState::Render()
{
	myBackground->Render();
	myControllerLayout->Render();
	MenuObject::Render();
}

void ControllerLayOutState::OnPushed()
{
	printf("Added controller layout on top of Stack");
	SetRenderThrough(true);
}

void ControllerLayOutState::BackButtonPress()
{
	StateManager::GetInstance().RemoveStateFromTop();
}
