#include "stdafx.h"
#include "StateManager.h"

#include "MainMenu.h"
#include "OptionsMenu.h"
#include "CharacterSelectionScreen.h"
#include "Level.h"
#include "LevelSelect.h"
#include "CutsceneManager.h"
#include "EndOfGameCutscene.h"

#include "LevelSelect_SpecificLevelData.h"


StateManager* StateManager::myInstance = nullptr;

uint32_t globalAllocCounter = 0ui32;
void* operator new(size_t aSize)
{
	++globalAllocCounter;
	return malloc(aSize);
}



void StateManager::Init()
{
	assert(myInstance == nullptr && "State Manager have already been Created");
	myInstance = new StateManager;

	myInstance->myMainMenu = std::make_shared<MainMenu>();
	myInstance->myOptionsMenu = std::make_shared<OptionsMenu>();
	myInstance->myLevel = std::make_shared<Level>();
	myInstance->myLevelSelect = std::make_shared<LevelSelect>();
	myInstance->myCutsceneManager = std::make_shared<CutsceneManager>();
	myInstance->myCharacterSelection = std::make_shared<CharacterSelectionScreen>();
	myInstance->myEndOfGameCutscene = std::make_shared<EndOfGameCutscene>();


	//Init the states you made here, rest will work automagically,
	myInstance->myMainMenu.get()->Init(EStateType::eMainMenu);
	myInstance->myOptionsMenu.get()->Init(EStateType::eOptionsMenu);
	myInstance->myLevel.get()->Init(EStateType::eGame);
	myInstance->myLevelSelect->Init(EStateType::eLevelSelect);
	myInstance->myCutsceneManager->Init(EStateType::eCutsceneManager);
	myInstance->myCharacterSelection->Init(EStateType::eCharacterSelection);
	myInstance->myEndOfGameCutscene->Init(EStateType::eEndOfGameCutscene);
	
	//Main Menu is the default beginning state
	myInstance->myGameStates.Push(GetInstance().myMainMenu);
	myInstance->myGameStates.GetTop()->OnPushed();
	
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

void StateManager::AddLevelOnStack(int aLevelIndex)
{
	if (myInstance->myLevelSelect->GetSpecificLevelData(aLevelIndex)->myIsUnlocked)
	{
		myInstance->RemoveDownToState(EStateType::eLevelSelect);
		myInstance->myGameStates.Push(myInstance->myLevel);
		myInstance->myLevel.get()->Load(myInstance->myLevelSelect->GetSpecificLevelData(aLevelIndex), false);
		myInstance->myGameStates.GetTop()->OnPushed();
	}
}

void StateManager::AddNextLevelOnStack(int aCurrentLevelIndex)
{
	if (aCurrentLevelIndex + 1 < myInstance->myLevelSelect->GetLevelAmount())
	{
		myInstance->myLevelSelect->GetSpecificLevelData(aCurrentLevelIndex + 1)->myIsUnlocked = true;
		myInstance->AddCharacterSelectOnStack(aCurrentLevelIndex + 1);
	}
	else
	{
		myInstance->RemoveDownToState(EStateType::eLevelSelect);
		myInstance->AddStateOnStack(myInstance->myEndOfGameCutscene);
		//Play Game over stuff and final cutscenes
	}
}

void StateManager::UnlockNextlevel(int aCurrentLevelIndex)
{
	if (aCurrentLevelIndex + 1 < myInstance->myLevelSelect->GetLevelAmount())
	{
		myInstance->myLevelSelect->GetSpecificLevelData(aCurrentLevelIndex + 1)->myIsUnlocked = true;
	}
}


void StateManager::AddAndPlayCutscene(int aCutsceneIndex)
{
	myInstance->myGameStates.Push(GetInstance().myCutsceneManager);
	myInstance->myCutsceneManager->PlayCutscene(aCutsceneIndex);
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddLastCutscene()
{
	myInstance->myGameStates.Push(GetInstance().myCutsceneManager);
	myInstance->myCutsceneManager->PlayLastCutscene();
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddCharacterSelectOnStack(const int aLevelIndex)
{
	myInstance->myGameStates.Push(myInstance->myCharacterSelection);
	myInstance->myCharacterSelection->AddCurrentLevelIndex(aLevelIndex);
	myInstance->myCharacterSelection->UnlockNewWorld(myInstance->myLevelSelect->GetSpecificLevelData(aLevelIndex)->myWorld);
	myInstance->myGameStates.GetTop()->OnPushed();
}

EPowerUp StateManager::GetSelectedCharacter()
{
	return myInstance->myCharacterSelection->GetCharacterChosen();
}

void StateManager::Update()
{
	myInstance->myGameStates.GetTop()->Update();
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
	globalAllocCounter = 0ui32;
}
