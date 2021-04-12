#include "stdafx.h"
#include "EndOfGameCutscene.h"
#include "UIButton.h"
#include "UIImage.h"
#include "StateManager.h"
#include "InputManager.h"

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
}

void EndOfGameCutscene::Update()
{
}

void EndOfGameCutscene::Render()
{
	myBackground->Render();
}

void EndOfGameCutscene::OnPushed()
{
	StateManager::GetInstance().AddLastCutscene();
}

void EndOfGameCutscene::OnResumed()
{
	//Add Image and Credit Roll
}

void EndOfGameCutscene::BackButtonPress()
{
}
