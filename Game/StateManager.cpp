#include "stdafx.h"
#include "StateManager.h"
StateManager* StateManager::myInstance = nullptr;

uint32_t globalAllocCounter = 0ui32;
void* operator new(size_t aSize)
{
	++globalAllocCounter;
	return malloc(aSize);
}



void StateManager::Init()
{
	assert(myInstance == nullptr && "Input Manager have already been Created");
	myInstance = new StateManager;
	myInstance->myMainMenu.Init(EStateType::eMainMenu);
	myInstance->myOptionsMenu.Init(EStateType::eOptionsMenu);
	myInstance->myOptionsMenu.SetRenderThrough(true);
	myInstance->myLevel.Init(EStateType::eGame);
	//Main Menu is the default beginning state
	myInstance->myGameStates.Push(&GetInstance().myMainMenu);
	myInstance->myGameStates.GetTop()->OnPushed();
	//Init the states you made here, rest will work automagically,
	//If you want to test a state, Push it on to myGameStates


}

void StateManager::Destroy()
{
	assert(myInstance != nullptr && "Input Manager have already been destroyed");
	delete myInstance;
	myInstance = nullptr;
}

StateManager& StateManager::GetInstance()
{
	assert(myInstance != nullptr && "Input Manager is Nullptr");
	return *myInstance;
}

bool StateManager::IsReady()
{
	return myInstance != nullptr;
}

void StateManager::RemoveStateFromTop()
{
	myInstance->myGameStates.RemoveTop();
}

void StateManager::RemoveDownToState(const EStateType& aStateType)
{
	while (myInstance->myGameStates.GetTop()->GetStateType() != aStateType)
	{
		myInstance->myGameStates.RemoveTop();
	}
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddOptionsOnStack()
{
	myInstance->myGameStates.Push(&myInstance->myOptionsMenu);
	myInstance->myGameStates.GetTop()->OnPushed();
}

void StateManager::AddLevelOnStack(int aLevelIndex)
{
	myInstance->myGameStates.Push(&myInstance->myLevel);
	myInstance->myLevel.Load(aLevelIndex);
	myInstance->myGameStates.GetTop()->OnPushed();
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
