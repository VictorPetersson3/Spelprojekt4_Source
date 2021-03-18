#pragma once
#include "CommonUtilities/Stack.hpp"
#include "State.h"

class MainMenu;
class OptionsMenu;
class Level;
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

	static void AddStateOnStack(std::shared_ptr<State> aState);
	static void AddOptionsOnStack();
	static void AddLevelOnStack(int aLevelIndex);

private:
	StateManager() = default;
	static StateManager* myInstance;
	std::shared_ptr<MainMenu> myMainMenu;
	std::shared_ptr<OptionsMenu> myOptionsMenu;
	std::shared_ptr<Level> myLevel;
	//Add States here as an object, 1 per state, Init the states after in Init



	CommonUtilities::Stack<std::shared_ptr<State>> myGameStates;
};

