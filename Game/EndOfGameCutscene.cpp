#include "stdafx.h"
#include "EndOfGameCutscene.h"
#include "UIButton.h"
#include "UIImage.h"
#include "StateManager.h"
#include "InputManager.h"
#include "Timer.h"
#include "CutsceneManager.h"
#include "AudioManager.h"

void EndOfGameCutscene::Init(const EStateType& aState)
{
	SetStateType(aState);

	myCutsceneManager = std::make_shared<CutsceneManager>(myController);
	myCutsceneManager->Init(EStateType::eCutsceneManager, "Json/Cutscenes/EndOfGameConversations");

	AddButton(std::make_shared<UIButton>(myController));
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
	myCreditsImage->Init({ 0.75f, 1.50f }, "sprites/UI/Credits.dds", -1);
	myCreditsImage->ActivatePulse(3.0f, 0.9f, 0.95f);

	mySadKiwi = std::make_unique<UIImage>();
	mySadKiwi->Init({ 0.25f, 0.5f }, "sprites/UI/EndCutsceneSadKiwi.dds", -1);
	mySadKiwi->GetRenderCommand().SetPivot({ 0.5f, 1.0f });
	mySadKiwi->SetPosition({ 0.25f, 0.95f });
	mySadKiwi->ActivatePulse(3.0f, 0.68f, 0.71f);

}

void EndOfGameCutscene::Update()
{
	MenuObject::Update();
	if (myConversationIsOver)
	{
		if (myCurrentConversation < myCutsceneManager->GetAmountOfConversations())
		{
			myConversationIsOver = false;
			StateManager::GetInstance().AddAndPlayCutscene(myCurrentConversation, myCutsceneManager);
			myCurrentConversation++;
		}
		else
		{
			myCutsceneIsFinished = true;
			myCreditsImage->Activate();
			mySadKiwi->Activate();			
		}
	}
	if (myCutsceneIsFinished)
	{
		myCreditsImage->Update({ myCreditsImage->GetPosition().x , myCreditsImage->GetPosition().y - (Timer::GetInstance().GetDeltaTime() * 0.2f) });
		myButtonTimer += Timer::GetInstance().GetDeltaTime();
		if (!GetButtonElement(0)->GetIsActive() && myButtonTimer > 6.5f )
		{
			GetButtonElement(0)->Activate();
		}
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
	myConversationIsOver = false;
	myCutsceneIsFinished = false;
	myCreditsImage->Deactivate();
	mySadKiwi->Deactivate();
	myCurrentConversation = 0;
	myButtonTimer = 0;
	myCreditsImage->SetPosition({ 0.75f, 1.80f });
	StateManager::GetInstance().AddAndPlayCutscene(myCurrentConversation, myCutsceneManager);
	myCurrentConversation++;
	AudioManager::GetInstance().StopAllMusic();
	AudioManager::GetInstance().PlayMusic("Audio/music/Credit_Song.mp3", true, 0.15f);

}

void EndOfGameCutscene::OnResumed()
{
	myConversationIsOver = true;
}

void EndOfGameCutscene::BackButtonPress()
{
	StateManager::RemoveDownToState(EStateType::eMainMenu);
}


