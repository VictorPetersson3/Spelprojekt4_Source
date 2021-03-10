#pragma once
#include "CommonUtilities/Stack.hpp"
#include "State.h"
#include "MainMenu.h"
#include "OptionsMenu.h"

class StateManager
{
public:
	~StateManager() = default;
	static void Init();
	static void Destroy();
	static StateManager& GetInstance();
	static bool IsReady();

	static void Update();


	static void RemoveStateFromTop();
	static void RemoveDownToState(const EStateType& aStateType);

	static void AddOptionsOnStack();


private:
	StateManager() = default;
	static StateManager* myInstance;
	MainMenu myMainMenu;
	OptionsMenu myOptionsMenu;
	//Add States here as an object, 1 per state, Init the states after in Init



	CommonUtilities::Stack<State*> myGameStates;
};

