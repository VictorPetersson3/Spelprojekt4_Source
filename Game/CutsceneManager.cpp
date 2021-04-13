#include "stdafx.h"
#include "CutsceneManager.h"
#include "AudioManager.h"
#include "InputManager.h"

#include "tga2d/sprite/sprite.h"

#include "CutsceneCharacter.h"
#include "CutsceneData.h"
#include "UIImage.h"
#include "UIButton.h"

#include "rapidjson/document.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

#include "JsonParser.h"
#include "Timer.h"
#include "StateManager.h"

#include "tga2d/text/text.h"


void CutsceneManager::Init(const EStateType& aState)
{
	SetStateType(aState);
	

	AddButton(std::make_shared<UIButton>());
	GetButtonElement(0)->Init({ 0.875f, 0.85f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {ContinuePrint(); });
	GetButtonElement(0)->SetIsHovered(false);
	GetButtonElement(0)->SetButtonScales(0.7f, 0.9f);
	AddButton(std::make_shared<UIButton>());
	GetButtonElement(1)->Init({ 0.875f, 0.85f }, "sprites/UI/OptionsMenu/B_BackArrow.dds", 0, [this]() {OnExit(); });
	GetButtonElement(1)->SetIsHovered(false);
	GetButtonElement(1)->Deactivate();
	GetButtonElement(1)->SetButtonScales(0.7f, 0.9f);
	myTextBackground = std::make_unique<UIImage>();
	myTextBackground->Init({ 0.5f, 0.85f }, "sprites/Cutscenes/TextFrame.dds", -1);
	myTextBackground->GetRenderCommand().SetSizeRelativeToImage({ 0.60f, 0.60f });
	myTextBackgroundGradient = std::make_unique<UIImage>();
	myTextBackgroundGradient->Init({ 0.5f, 0.85f }, "sprites/Cutscenes/AlphaGradient.dds", -1);
	myTextBackgroundGradient->GetRenderCommand().SetPivot({ 0.5f, 1.0f });
	myTextBackgroundGradient->GetRenderCommand().SetSpritePosition({ 0.5f, 1.0f });
	myTextBackgroundGradient->GetRenderCommand().SetSizeRelativeToImage({ 5.0f, 1.0f });
	myTextBackgroundGradient->GetRenderCommand().SetColor(Tga2D::CColor{0.5f, 0.15f, 0.23f, 1.0f});

	myTextToPrint = std::make_shared<Tga2D::CText>("Text/Tomodachy.otf", Tga2D::EFontSize_14);
	myTextToPrint->SetColor({ 0,0,0,1 });
	myTextToPrint->SetPosition({ 0.21f, 0.79f });
	myHasReachedEndOfSentence = false;
}
void CutsceneManager::Init(const EStateType& aState, const char* aCutsceneDirectory)
{
	LoadCharacters();
	LoadCutscenes(aCutsceneDirectory);
	Init(aState);
}

void CutsceneManager::Update()
{
	MenuObject::Update();
	if (myIsPrinting)
	{
		Dialogue();
	}
	else
	{
		GetButtonElement(1)->SetIsHovered(true);
		GetButtonElement(1)->Activate();
	}
	if (InputManagerS::GetInstance().GetKeyUp(DIK_ESCAPE) && !myPrintEverything)
	{
		printf("I will print Everything!!!\n");
		PrintEverything();
	}
	
}

void CutsceneManager::Render()
{
	myTextBackgroundGradient->Render();
	myLeftCharacter->Render();
	myRightCharacter->Render();
	myTextBackground->Render();
	myTextToPrint->SetText(myDialogueToRender);
	myTextToPrint->Render();
	MenuObject::Render();
}

void CutsceneManager::OnPushed()
{
	SetRenderThrough(true);
}

void CutsceneManager::PlayCutscene(int aLevelIndex)
{
	myCurrentLineToPlay.clear();
	myDialogueToRender.clear();
	mySceneToPlay = aLevelIndex;
	myIsPrinting = true;
	myPrintEverything = false;
	myHasReachedEndOfSentence = false;

	//Setting the current speaking characters
	myLeftCharacter = myLevelCharacterDialogues[aLevelIndex]->GetLeftCharacter();
	myLeftCharacter->SetPosition({ 0.25f, 0.55f });
	myRightCharacter = myLevelCharacterDialogues[aLevelIndex]->GetRightCharacter();
	myRightCharacter->SetPosition({ 0.75f, 0.55f });
	myCurrentLineIndexToPlay = 0;
	myCurrentLetterInLineToPlay = 0;
	//Getting the first line and activating the speakin character
	myCurrentLineToPlay = myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].first;
	myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->SetActive(true);
	if (myLevelCharacterDialogues[mySceneToPlay]->GetCharacterMoods()[myCurrentLineIndexToPlay] != "default")
	{
		myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->MakeAngry(true);
	}
	else
	{
		myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->MakeAngry(false);
	}

	//Print the name of the speaking Character
	std::string characterName = myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->GetName().GetString();
	characterName.append("  ");
	myDialogueToRender.append(characterName.c_str());

	//printf("\n%s: ", myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->GetName().GetString());
	myCurrentLineIndexToPlay++;
	GetButtonElement(0)->Activate();
	GetButtonElement(1)->Deactivate();


}

void CutsceneManager::PlayLastCutscene() { PlayCutscene(myLevelCharacterDialogues.Size() - 1); }

const int CutsceneManager::GetAmountOfConversations() const { return myLevelCharacterDialogues.Size(); }

void CutsceneManager::LoadCutscenes(const char* aCutsceneDirectory)
{
	std::vector<std::string> cutscenePaths;
	std::string directory = aCutsceneDirectory; // Json/Cutscenes/Conversations  / Json/Cutscenes/EndOfGameConversations
	int iterator = 0;
	for (const auto& entry : std::filesystem::directory_iterator(aCutsceneDirectory))
	{
		if (entry.path().extension().string() == ".json")
		{

			auto file = entry.path().string();
			int length = directory.length();
			std::string type = file.substr(length + 1);
			std::string levelPathStitched = directory + "/";
			levelPathStitched.append(type);
			cutscenePaths.push_back(levelPathStitched);
		}
		iterator++;
	}
	std::sort(cutscenePaths.begin(), cutscenePaths.end());
	//for (int i = 0; i < iterator; i++)
	//{
	//	printf("My Sorted Cutscene Path: %s\n", cutscenePaths[i].c_str());
	//}

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
			std::string mood = lines[i]["mood"].GetString();
			currentSceneData->AddCharacterMood(mood.c_str());
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
	//for (int i = 0; i < iterator; i++)
	//{
	//	printf("My Character Path: %s\n", characterPaths[i].c_str());
	//}

	JsonParser parser;

	for (int i = 0; i < iterator; i++)
	{
		rapidjson::Document document = parser.GetDocument(characterPaths[i].c_str());
		std::string characterMood;
		std::string imagePath = document["imagepath"].GetString();
		std::string name = document["name"].GetString();
		if (!document["angryImagePath"].IsNull())
		{
			characterMood = document["angryImagePath"].GetString();
		}
		else
		{
			characterMood = imagePath;
		}
		//printf("Character path : %s name : %s \n", imagePath.c_str(), name.c_str());
		myCharacters.Add(std::make_shared<CutsceneCharacter>(imagePath.c_str(), name.c_str(), CommonUtilities::Vector2f{ 0.5f, 0.5f }));
		myCharacters[i]->InitAngrySprite(characterMood.c_str());
	}
}

void CutsceneManager::Dialogue()
{
	myTextTimer += Timer::GetInstance().GetDeltaTime();
	
	if (myPrintEverything)
	{
		while (myIsPrinting)
		{
			ParseAndAddText();
		}
	}
	else
	{
		if (myTextTimer > 0.025f)
		{
			ParseAndAddText();
		}
	}
}

void CutsceneManager::ParseAndAddText()
{
	myTextTimer = 0;
	if (myCurrentLetterInLineToPlay < myCurrentLineToPlay.size())
	{
		if (!myHasReachedEndOfSentence)
		{
			//printf("%c", myCurrentLineToPlay.at(myCurrentLetterInLineToPlay));
			myDialogueToRender.push_back(myCurrentLineToPlay.at(myCurrentLetterInLineToPlay));
			myCurrentLetterInLineToPlay++;
			if (!myPrintEverything)
			{
				AudioManager::GetInstance().PlayEffect("Audio/Cutscene/textclick.wav", false, 0.2f);
			}
		}
	}
	else
	{
		if (myCurrentLineIndexToPlay < myLevelCharacterDialogues[mySceneToPlay]->GetLines().Size())
		{
			if (!myPrintEverything && !myHasReachedEndOfSentence)
			{
				GetButtonElement(0)->SetIsHovered(true);
				myHasReachedEndOfSentence = true;
				myHasResumed = false;
			}
			if (myHasResumed)
			{
				myTextTimer = -0.25f;
				myCurrentLineToPlay = myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].first;

				if (myLeftCharacter->GetName() == myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->GetName())
				{
					myLeftCharacter->SetActive(true);
					myRightCharacter->SetActive(false);
				}
				else
				{
					myLeftCharacter->SetActive(false);
					myRightCharacter->SetActive(true);
				}

				//Print the name of the speaking Character
				myDialogueToRender.push_back('\n');
				std::string characterName = myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->GetName().GetString();
				characterName.append("  ");
				myDialogueToRender.append(characterName.c_str());
				if (myLevelCharacterDialogues[mySceneToPlay]->GetCharacterMoods()[myCurrentLineIndexToPlay] != "default")
				{
					myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->MakeAngry(true);
				}
				else
				{
					myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->MakeAngry(false);
				}

				//printf("\n%s: ", myLevelCharacterDialogues[mySceneToPlay]->GetLines()[myCurrentLineIndexToPlay].second->GetName().GetString());
				myCurrentLineIndexToPlay++;
				myCurrentLetterInLineToPlay = 0;
				myHasReachedEndOfSentence = false;
			}
		}
		else
		{
			myCurrentLineIndexToPlay = 0;
			myIsPrinting = false;
		}
	}
}

void CutsceneManager::ContinuePrint()
{
	if (myHasReachedEndOfSentence)
	{
		GetButtonElement(0)->SetIsHovered(false);
		myHasResumed = true;
	}
}

void CutsceneManager::PrintEverything()
{
	myPrintEverything = true;
	myHasResumed = true;
	GetButtonElement(0)->SetIsHovered(false);
	GetButtonElement(0)->Deactivate();
	AudioManager::GetInstance().PlayEffect("Audio/UI/Button/UI_onReturn.mp3");
}

void CutsceneManager::OnExit()
{
	printf("On Exit");
	StateManager::GetInstance().RemoveStateFromTop();
}
