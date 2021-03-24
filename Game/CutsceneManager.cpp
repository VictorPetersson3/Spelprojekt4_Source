#include "stdafx.h"
#include "CutsceneManager.h"

#include "tga2d/sprite/sprite.h"

#include "CutsceneCharacter.h"
#include "CutsceneData.h"

#include "rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

#include "JsonParser.h"
#include "Timer.h"
#include "StateManager.h"

void CutsceneManager::Init(const EStateType& aState)
{
	SetStateType(aState);
	LoadCharacters();
	LoadCutscenes();
}

void CutsceneManager::Update()
{
	if (myIsPlaying)
	{
		Dialogue();
	}
	else
	{
		//Quit dialogue
	}
}

void CutsceneManager::Render()
{
}

void CutsceneManager::OnPushed()
{
	SetRenderThrough(true);
}

void CutsceneManager::PlayCutscene(int aLevelIndex)
{
	mySceneToPlay = aLevelIndex;
	myIsPlaying = true;

	//Setting the current speaking characters
	myLeftCharacter = myLevelCharacterDialogues[aLevelIndex]->GetLeftCharacter();
	myRightCharacter = myLevelCharacterDialogues[aLevelIndex]->GetRightCharacter();
	myCurrentLineIndexToPlay = 0;
	myCurrentLetterInLineToPlay = 0;
	//Getting the first line and activating the speakin character
	myCurrentLineToPlay = myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].first;
	myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->SetActive(true);
	myCurrentLineIndexToPlay++;

}

void CutsceneManager::LoadCutscenes()
{
	std::vector<std::string> cutscenePaths;
	std::string directory = "Json/Cutscenes/Conversations";
	int iterator = 0;
	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		if (entry.path().extension().string() == ".json")
		{

			auto file = entry.path().string();

			std::string type = file.substr(29);
			std::string levelPathStitched = "Json/Cutscenes/Conversations/";
			levelPathStitched.append(type);
			cutscenePaths.push_back(levelPathStitched);
		}
		iterator++;
	}
	std::sort(cutscenePaths.begin(), cutscenePaths.end());
	for (int i = 0; i < iterator; i++)
	{
		printf("My Sorted Cutscene Path: %s\n", cutscenePaths[i].c_str());
	}

	myLevelCharacterDialogues.Init(iterator);

	JsonParser parser;
	for (int i = 0; i < iterator; i++)
	{
		rapidjson::Document document = parser.GetDocument(cutscenePaths[i].c_str());
		
		std::shared_ptr<CutsceneData> currentSceneData = std::make_shared<CutsceneData>();

		for (int i = 0; i < myCharacters.Size(); i++)
		{
			if (myCharacters[i]->GetName() == document["characterLeft"].GetString())
			{
				currentSceneData->AddLeftCharacter(myCharacters[i]);
			}
			if (myCharacters[i]->GetName() == document["characterRight"].GetString())
			{
				currentSceneData->AddRightCharacter(myCharacters[i]);
			}
		}
		auto lines = document["dialogue"].GetArray();
		for (rapidjson::SizeType i = 0; i < lines.Size(); i++)
		{
			if (lines[i]["speaker"].GetString() == currentSceneData->GetLeftCharacter()->GetName())
			{
				std::pair<std::string, std::shared_ptr<CutsceneCharacter>> line = std::make_pair(lines[i]["line"].GetString(), currentSceneData->GetLeftCharacter() );
				currentSceneData->AddLine(line);
			}
			else
			{
				std::pair<std::string, std::shared_ptr<CutsceneCharacter>> line = std::make_pair(lines[i]["line"].GetString(), currentSceneData->GetRightCharacter());
				currentSceneData->AddLine(line);
			}
		}
		myLevelCharacterDialogues.Add(currentSceneData);
	}
}

void CutsceneManager::LoadCharacters()
{
	myCharacters.Init(10);
	std::vector<std::string> characterPaths;
	std::string directory = "Json/Cutscenes/Characters";
	int iterator = 0;
	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		if (entry.path().extension().string() == ".json")
		{

			auto file = entry.path().string();

			std::string type = file.substr(26);
			std::string levelPathStitched = "Json/Cutscenes/Characters/";
			levelPathStitched.append(type);
			characterPaths.push_back(levelPathStitched);
		}
		iterator++;
	}
	std::sort(characterPaths.begin(), characterPaths.end());
	for (int i = 0; i < iterator; i++)
	{
		printf("My Character Path: %s\n", characterPaths[i].c_str());
	}

	JsonParser parser;


	for (int i = 0; i < iterator; i++)
	{
		rapidjson::Document document = parser.GetDocument(characterPaths[i].c_str());
		

		std::string imagePath = document["imagepath"].GetString();
		std::string name = document["name"].GetString();
		printf("Character path : %s name : %s \n", imagePath.c_str(), name.c_str());
		myCharacters.Add(std::make_shared<CutsceneCharacter>(imagePath.c_str(), name.c_str(), CommonUtilities::Vector2f{ 0.5f, 0.5f }));
	}
}

void CutsceneManager::Dialogue()
{
	myTextTimer += Timer::GetInstance().GetDeltaTime();

	if (myTextTimer > 0.05f)
	{
		myTextTimer = 0;
		if (myCurrentLetterInLineToPlay < myCurrentLineToPlay.size())
		{
			printf( "%c", myCurrentLineToPlay.at(myCurrentLetterInLineToPlay) );
			myCurrentLetterInLineToPlay++;
		}
		else
		{
			if (myCurrentLineIndexToPlay < myLevelCharacterDialogues[mySceneToPlay]->GetLines().Size())
			{
				myTextTimer = -0.25f;
				myCurrentLineToPlay = myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].first;
				myCurrentLineIndexToPlay++;
				printf("\n");
			}
			else
			{
				myCurrentLineIndexToPlay = 0;
				myIsPlaying = false;
			}
			myCurrentLetterInLineToPlay = 0;
		}
	}
}

void CutsceneManager::OnExit()
{
	StateManager::GetInstance().RemoveStateFromTop();
}
