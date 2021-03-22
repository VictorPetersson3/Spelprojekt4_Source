#include "stdafx.h"
#include "ControllerLayOutState.h"
#include "UIButton.h"
#include "UIImage.h"
#include "StateManager.h"
#include "InputManager.h"

void ControllerLayOutState::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.75f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });
	GetButtonElement(0)->SetIsHovered(true);


	myBackground = std::make_unique<UIImage>();
	myBackground.get()->Init({ 0.5f, 0.5f }, "sprites/UI/OptionsMenu/ControllerLayout.dds", 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({1.0f, 1.0f});
	myBackground.get()->Activate();
}

void ControllerLayOutState::Update()
{
	if (InputManagerS::GetInstance().GetKeyDown(DIK_ESCAPE))
	{
		BackButtonPress();
	}
	GetButtonElement(0)->Update();
}

void ControllerLayOutState::Render()
{
	myBackground.get()->Render();
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
