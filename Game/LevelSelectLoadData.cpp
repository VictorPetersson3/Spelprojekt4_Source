#include "stdafx.h"
#include "LevelSelectLoadData.h"
#include "LevelSelect_SpecificLevelData.h"

void LevelSelectLoadData::CreateLevelSelectButtonData()
{
	rapidjson::Document document;
	JsonParser parser;
	document = parser.GetDocument("Json/Levels.json");
	auto worlds = document["Worlds"].GetArray(); 
	int levelCounter = 0;
	for (rapidjson::SizeType i = 0; i < worlds.Size(); i++)
	{
		auto worldLevel = worlds[i]["levels"].GetArray();

		switch (i)
		{
		case 0:
			World1Song = worlds[i]["actSong"].GetString();
			FillData(worldLevel, levelCounter, EWorldLevel::eWorld1);
			break;
		case 1:
			World2Song = worlds[i]["actSong"].GetString();
			FillData(worldLevel, levelCounter, EWorldLevel::eWorld2);
			break;
		case 2:
			World3Song = worlds[i]["actSong"].GetString();
			FillData(worldLevel, levelCounter, EWorldLevel::eWorld3);
			break;
		case 3:
			World4Song = worlds[i]["actSong"].GetString();
			FillData(worldLevel, levelCounter, EWorldLevel::eWorld4);
			break;
		default:
			break;
		}
	}
	for (size_t i = 0; i < myLevelSelectLoadData.Size(); i++)
	{
		std::string debugPath = myLevelSelectLoadData[i]->myMapTile.GetString();
	}
}

void LevelSelectLoadData::FillData(rapidjson::Value& aJsonValue, int& aLevelIterator, EWorldLevel aWorld)
{
	for (rapidjson::SizeType i = 0; i < aJsonValue.Size(); i++)
	{
		myLevelSelectLoadData.Add(std::make_shared<LevelSelect_SpecificLevelData>());
		myLevelSelectLoadData[aLevelIterator]->myLevelNumber = aLevelIterator;
		myLevelSelectLoadData[aLevelIterator]->myLevelPath = aJsonValue[i]["path"].GetString();
		myLevelSelectLoadData[aLevelIterator]->myTileSheetPath = aJsonValue[i]["gameplayAreaTileSheetPath"].GetString();
		myLevelSelectLoadData[aLevelIterator]->myPropsTileSheetPath = aJsonValue[i]["propsTileSheetPath"].GetString();
		myLevelSelectLoadData[aLevelIterator]->myMapTile = aJsonValue[i]["mapTilePath"].GetString();
		myLevelSelectLoadData[aLevelIterator]->myPosition.x = aJsonValue[i]["positionX"].GetFloat() / 1920;
		myLevelSelectLoadData[aLevelIterator]->myPosition.y = aJsonValue[i]["positionY"].GetFloat() / 1080;

		if (aJsonValue[i]["hasCutscene"].GetBool())
		{
			myLevelSelectLoadData[aLevelIterator]->myHasCutscene = true;
			myLevelSelectLoadData[aLevelIterator]->myCutsceneConversation = aJsonValue[i]["cutSceneConversationNumber"].GetInt();
		}
		myLevelSelectLoadData[aLevelIterator]->myWorld = aWorld;
		aLevelIterator++;
	}
}
