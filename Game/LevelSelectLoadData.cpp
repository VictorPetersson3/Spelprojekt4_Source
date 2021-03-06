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
	//for (size_t i = 0; i < myLevelSelectLoadData.Size(); i++)
	//{
	//	std::string debugPath = myLevelSelectLoadData[i]->myMapTile.GetString();
	//}
}

void LevelSelectLoadData::FillData(rapidjson::Value& aJsonValue, int& aLevelIterator, EWorldLevel aWorld)
{
	for (rapidjson::SizeType i = 0; i < aJsonValue.Size(); i++)
	{
		myLevelSelectLoadData.Add(std::make_shared<LevelSelect_SpecificLevelData>());
		myLevelSelectLoadData[aLevelIterator]->myWorldLevelNumber = i;
		myLevelSelectLoadData[aLevelIterator]->myLevelSelectNumber = aLevelIterator;
		myLevelSelectLoadData[aLevelIterator]->myLevelPath = aJsonValue[i]["path"].GetString();
		myLevelSelectLoadData[aLevelIterator]->myTileSheetPath = aJsonValue[i]["gameplayAreaTileSheetPath"].GetString();
		myLevelSelectLoadData[aLevelIterator]->myPropsTileSheetPath = aJsonValue[i]["propsTileSheetPath"].GetString();
		myLevelSelectLoadData[aLevelIterator]->myBackgroundTilesTileSheetPath = aJsonValue[i]["backgroundTileSheetPath"].GetString();
		myLevelSelectLoadData[aLevelIterator]->myMapTile = aJsonValue[i]["mapTilePath"].GetString();
		myLevelSelectLoadData[aLevelIterator]->myPosition.x = aJsonValue[i]["positionX"].GetFloat() / 1920;
		myLevelSelectLoadData[aLevelIterator]->myPosition.y = aJsonValue[i]["positionY"].GetFloat() / 1080;
		myLevelSelectLoadData[aLevelIterator]->myCameraAcceleration = aJsonValue[i]["cameraAcceleration"].GetFloat();
		myLevelSelectLoadData[aLevelIterator]->myCameraMinBorderX = aJsonValue[i]["cameraMinBorderX"].GetFloat();
		myLevelSelectLoadData[aLevelIterator]->myCameraMaxBorderX = aJsonValue[i]["cameraMaxBorderX"].GetFloat();
		myLevelSelectLoadData[aLevelIterator]->myCameraMinBorderY = aJsonValue[i]["cameraMinBorderY"].GetFloat();
		myLevelSelectLoadData[aLevelIterator]->myCameraMaxBorderY = aJsonValue[i]["cameraMaxBorderY"].GetFloat();
		myLevelSelectLoadData[aLevelIterator]->myCameraPosition.x = aJsonValue[i]["cameraPosition"][0].GetFloat();
		myLevelSelectLoadData[aLevelIterator]->myCameraPosition.y = aJsonValue[i]["cameraPosition"][1].GetFloat();
		myLevelSelectLoadData[aLevelIterator]->myMoveCameraX = aJsonValue[i]["moveX"].GetBool();
		myLevelSelectLoadData[aLevelIterator]->myMoveCameraY = aJsonValue[i]["moveY"].GetBool();
		myLevelSelectLoadData[aLevelIterator]->myHasBoss = aJsonValue[i]["hasBoss"].GetBool();

		if (aJsonValue[i]["hasCutscene"].GetBool())
		{
			myLevelSelectLoadData[aLevelIterator]->myHasCutscene = true;
			myLevelSelectLoadData[aLevelIterator]->myCutsceneConversation = aJsonValue[i]["cutSceneConversationNumber"].GetInt();
		}
		if (aJsonValue[i].HasMember("hasEndCutscene") && aJsonValue[i]["hasEndCutscene"].GetBool())
		{
			myLevelSelectLoadData[aLevelIterator]->myHasEndCutscene = true;
			myLevelSelectLoadData[aLevelIterator]->myEndCutsceneConversation = aJsonValue[i]["EndCutsceneConversationNumber"].GetInt();
		}


		myLevelSelectLoadData[aLevelIterator]->myWorld = aWorld;
		switch (aWorld)
		{
		case EWorldLevel::eWorld1:
			myLevelSelectLoadData[aLevelIterator]->mySong = World1Song;
			break;
		case EWorldLevel::eWorld2:
			myLevelSelectLoadData[aLevelIterator]->mySong = World2Song;
			break;
		case EWorldLevel::eWorld3:
			myLevelSelectLoadData[aLevelIterator]->mySong = World3Song;
			break;
		case EWorldLevel::eWorld4:
			myLevelSelectLoadData[aLevelIterator]->mySong = World4Song;
			break;
		default:
			break;
		}
		aLevelIterator++;
	}
}
