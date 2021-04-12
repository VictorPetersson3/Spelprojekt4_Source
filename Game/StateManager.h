#pragma once
#include "CommonUtilities/Stack.hpp"
#include "State.h"
#include "Enums.h"

class MainMenu;
class OptionsMenu;
class Level;
class LevelSelect;
class CutsceneManager;
class CharacterSelectionScreen;
class EndOfGameCutscene;

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
	static void AddLevelSelectOnStack();

	static void AddLevelOnStack(int aLevelIndex);
	static void AddNextLevelOnStack(int aLevelIndex);
	static void UnlockNextlevel(int aCurrentLevelIndex);

	static void AddAndPlayCutscene(int aCutsceneIndex);
	static void AddLastCutscene();

	static void AddCharacterSelectOnStack(const int aLevelIndex);
	static EPowerUp GetSelectedCharacter();


private:
	StateManager() = default;
	static StateManager* myInstance;
	std::shared_ptr<LevelSelect> myLevelSelect;
	std::shared_ptr<MainMenu> myMainMenu;
	std::shared_ptr<OptionsMenu> myOptionsMenu;
	std::shared_ptr<Level> myLevel;
	std::shared_ptr<CutsceneManager> myCutsceneManager;
	std::shared_ptr<CharacterSelectionScreen> myCharacterSelection;
	std::shared_ptr<EndOfGameCutscene> myEndOfGameCutscene;
	//Add States here as an object, 1 per state, Init the states after in Init



	CommonUtilities::Stack<std::shared_ptr<State>> myGameStates;
};

