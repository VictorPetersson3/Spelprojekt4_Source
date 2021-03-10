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
	CommonUtilities::Stack<State*> myGameStates;
};

