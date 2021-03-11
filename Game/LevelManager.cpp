#include "stdafx.h"
#include "LevelManager.h"
#include "LevelLoader.h"
#include "Level.h"
#include "JsonParser.h"
#include "rapidjson\document.h"

LevelManager::LevelManager()
{
	Init();
}

LevelManager::~LevelManager()
{

}

void LevelManager::Init()
{
	JsonParser jsonParser;
	LevelLoader levelLoader;

	rapidjson::Document document;

	document = jsonParser.GetDocument("Json/Levels.json");

	for (int i = 0; i < document["levels"].Capacity(); i++)
	{
		myLevels.push_back(std::make_shared<Level>(levelLoader.LoadLevel(document["levels"][i]["path"].GetString())));
	}
}

void LevelManager::Update()
{
	myLevels[myCurrentLevel].get()->Render();
}


