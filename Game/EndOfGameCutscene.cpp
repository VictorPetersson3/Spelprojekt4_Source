#include "stdafx.h"
#include "EndOfGameCutscene.h"
#include "UIButton.h"
#include "UIImage.h"
#include "StateManager.h"
#include "InputManager.h"
#include "Timer.h"

void EndOfGameCutscene::Init(const EStateType& aState)
{
	SetStateType(aState);
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.5f, 0.75f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {BackButtonPress(); });
	GetButtonElement(0)->SetIsHovered(true);
	GetButtonElement(0)->Deactivate();

	myPanningShader = std::make_shared<Tga2D::CCustomShader>();
	myPanningShader->Init("shaders/sprite_shader_panning_vs.fx", "shaders/sprite_shader_ps.fx");

	myBackground = std::make_unique<UIImage>();
	myBackground->Init({ 0.5f, 0.5f }, "sprites/UI/MainMenu/huvudmeny_bg_tile.dds", -1);
	myBackground.get()->GetRenderCommand().SetSamplerState(ESamplerFilter::ESamplerFilter_Bilinear, ESamplerAddressMode::ESamplerAddressMode_Wrap);
	myBackground.get()->GetRenderCommand().SetTextureRect(0, 0, 2, 2);
	myBackground.get()->GetRenderCommand().SetSizeRelativeToImage({ 2.0f, 2.0f });
	myBackground->SetShader(*myPanningShader.get());

	myCreditsImage = std::make_unique<UIImage>();
	myCreditsImage->Init({ 0.75f, -0.40f }, "sprites/UI/Credits.dds", -1);
	myCreditsImage->ActivatePulse(3.0f, 0.9f, 1.1f);

	mySadKiwi = std::make_unique<UIImage>();
	mySadKiwi->Init({ 0.25f, 0.5f }, "sprites/UI/EndCutsceneSadKiwi.dds", -1);
}

void EndOfGameCutscene::Update()
{
	if (myConversationIsOver)
	{
		myCreditsImage->Update({ myCreditsImage->GetPosition().x , myCreditsImage->GetPosition().y + (Timer::GetInstance().GetDeltaTime() * 0.25f) });
		GetButtonElement(0)->Update();
	}
}

void EndOfGameCutscene::Render()
{
	myBackground->Render();
	if (myConversationIsOver)
	{
		mySadKiwi->Render();
		myCreditsImage->Render();
	}
	MenuObject::Render();
}

void EndOfGameCutscene::OnPushed()
{
	StateManager::GetInstance().AddLastCutscene();
	myCreditsImage->SetPosition({ 0.75f, -0.40f });
	myConversationIsOver = false;
}

void EndOfGameCutscene::OnResumed()
{
	myConversationIsOver = true;
	GetButtonElement(0)->Activate();
}

void EndOfGameCutscene::BackButtonPress()
{
	StateManager::RemoveDownToState(EStateType::eMainMenu);
}
