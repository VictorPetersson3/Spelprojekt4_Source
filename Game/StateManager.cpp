#include "stdafx.h"
#include "StateManager.h"
#include "AudioManager.h"

#include "MainMenu.h"
#include "OptionsMenu.h"
#include "CharacterSelectionScreen.h"
#include "Level.h"
#include "LevelSelect.h"
#include "CutsceneManager.h"
#include "EndOfGameCutscene.h"
#include "FadeInImage.h"
#include "LevelSelect_SpecificLevelData.h"
#include "XController.h"

StateManager* StateManager::myInstance = nullptr;

uint32_t globalAllocCounter = 0ui32;
void* operator new(size_t aSize)
{
	++globalAllocCounter;
	return malloc(aSize);
}



void StateManager::Init(XController* aControllerPointer)
{
	assert(myInstance == nullptr && "State Manager have already been Created");
	myInstance = new StateManager;

	myInstance->myMainMenu = std::make_shared<MainMenu>(aControllerPointer);
	myInstance->myOptionsMenu = std::make_shared<OptionsMenu>(aControllerPointer);
	myInstance->myLevel = std::make_shared<Level>(aControllerPointer);
	myInstance->myLevelSelect = std::make_shared<LevelSelect>(aControllerPointer);
	myInstance->myCutsceneManager = std::make_shared<CutsceneManager>(aControllerPointer);
	myInstance->myCharacterSelection = std::make_shared<CharacterSelectionScreen>(aControllerPointer);
	myInstance->myEndOfGameCutscene = std::make_shared<EndOfGameCutscene>(aControllerPointer);
	myInstance->myFadeInImage = std::make_shared<FadeInImage>();

	//Init the states you made here, rest will work automagically,
	myInstance->myMainMenu.get()->Init(EStateType::eMainMenu);
	myInstance->myOptionsMenu.get()->Init(EStateType::eOptionsMenu);
	myInstance->myLevel.get()->Init(EStateType::eGame);
	myInstance->myLevelSelect->Init(EStateType::eLevelSelect);
	myInstance->myCutsceneManager->Init(EStateType::eCutsceneManager, "Json/Cutscenes/Conversations");
	myInstance->myCharacterSelection->Init(EStateType::eCharacterSelection);
	myInstance->myEndOfGameCutscene->Init(EStateType::eEndOfGameCutscene);
	myInstance->myFadeInImage->Init(EStateType::eFadeIn);
	//Main Menu is the default beginning state
	myInstance->AddStateOnStack(GetInstance().myMainMenu);
	myInstance->AddStateOnStack(GetInstance().myFadeInImage);
	myInstance->myFadeInImage->PlayIntro();
	// 
	//If you want to test a state, Push it on to myGameStates above the main menu


}

void StateManager::Destroy()
{
	assert(myInstance != nullptr && "State Manager have already been destroyed");
	delete myInstance;
	myInstance = nullptr;
}

StateManager& StateManager::GetInstance()
{
	assert(myInstance != nullptr && "State Manager is Nullptr");
	return *myInstance;
}

bool StateManager::IsReady()
{
	return myInstance != nullptr;
}

void StateManager::RemoveStateFromTop()
{
	myInstance->myGameStates.RemoveTop();
	myInstance->myGameStates.GetTop()->OnResumed();
}

void StateManager::RemoveDownToState(const EStateType& aStateType)
{
	while (myInstance->myGameStates.GetTop()->GetStateType() != aStateType)
	{
		myInstance->myGameStates.RemoveTop();
	}
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddStateOnStack(std::shared_ptr<State> aState)
{
	myInstance->myGameStates.Push(aState);
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddOptionsOnStack()
{
	myInstance->myGameStates.Push(myInstance->myOptionsMenu);
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddLevelSelectOnStack()
{
	myInstance->myGameStates.Push(myInstance->myLevelSelect);
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddAndPlayFadeOnStack(const EFadeImage aFadeImage)
{
	myInstance->AddStateOnStack(GetInstance().myFadeInImage);
	myInstance->myFadeInImage->PlayFade(aFadeImage);
}

void StateManager::AddLevelOnStack(int aLevelIndex)
{
	if (myInstance->myLevelSelect->GetSpecificLevelData(aLevelIndex)->myIsUnlocked)
	{
		myInstance->RemoveDownToState(EStateType::eLevelSelect);
		myInstance->myGameStates.Push(myInstance->myLevel);
		myInstance->myLevel->Load(myInstance->myLevelSelect->GetSpecificLevelData(aLevelIndex), false);
		myInstance->myGameStates.GetTop()->OnPushed();
	}
}

void StateManager::AddNextLevelOnStack(int aCurrentLevelIndex)
{
	if (aCurrentLevelIndex + 1 < myInstance->myLevelSelect->GetLevelAmount())
	{
		myInstance->AddCharacterSelectOnStack(aCurrentLevelIndex + 1);
	}
	else
	{
		myInstance->RemoveDownToState(EStateType::eLevelSelect);
		myInstance->AddStateOnStack(myInstance->myEndOfGameCutscene);
	}
}

void StateManager::UnlockNextlevel(int aCurrentLevelIndex)
{
	if (aCurrentLevelIndex + 1 < myInstance->myLevelSelect->GetLevelAmount())
	{
		myInstance->myLevelSelect->GetSpecificLevelData(aCurrentLevelIndex + 1)->myIsUnlocked = true;
	}
}


void StateManager::AddAndPlayCutscene(int aCutsceneIndex, const bool aEndOfMapCutscene)
{
	myInstance->myGameStates.Push(GetInstance().myCutsceneManager);
	myInstance->myCutsceneManager->PlayCutscene(aCutsceneIndex, aEndOfMapCutscene);
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddAndPlayCutscene(int aCutsceneIndex, std::shared_ptr<CutsceneManager> aCutsceneManager, const bool aEndOfMapCutscene)
{
	myInstance->myGameStates.Push(aCutsceneManager);
	aCutsceneManager->PlayCutscene(aCutsceneIndex, aEndOfMapCutscene);
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddEndOfLevelOnStack()
{
	myInstance->myLevel->AddEndOfLevelOnStack();
}

void StateManager::AddLastCutscene()
{
	myInstance->myGameStates.Push(GetInstance().myCutsceneManager);
	myInstance->myCutsceneManager->PlayLastCutscene();
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddCharacterSelectOnStack(const int aLevelIndex)
{
	if (myInstance->myLevelSelect->GetSpecificLevelData(aLevelIndex)->myIsUnlocked)
	{
		myInstance->myGameStates.Push(myInstance->myCharacterSelection);
		myInstance->myCharacterSelection->AddCurrentLevelIndex(aLevelIndex);
		myInstance->myCharacterSelection->UnlockNewWorld(myInstance->myLevelSelect->GetSpecificLevelData(aLevelIndex)->myWorld);
		myInstance->myGameStates.GetTop()->OnPushed();
	}
	else
	{
		AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onReturn.mp3");
	}
}

EPowerUp StateManager::GetSelectedCharacter()
{
	return myInstance->myCharacterSelection->GetCharacterChosen();
}

void StateManager::Update()
{
	myInstance->myGameStates.GetTop()->Update();
	globalAllocCounter = 0ui32;
}

void StateManager::Render()
{
	//This is to render the layers that are beneath the current game state if they are renderable
	if (myInstance->myGameStates.GetTop()->GetRenderThrough())
	{
		for (int i = 0; i < myInstance->myGameStates.GetSize() - 1; i++)
		{
			if (myInstance->myGameStates.GetElement(i + 1)->GetRenderThrough())
			{
				myInstance->myGameStates.GetElement(i)->Render();
			}
		}
	}
	myInstance->myGameStates.GetTop()->Render();
}
