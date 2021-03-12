#include "stdafx.h"
#include "Level.h"
#include "LevelLoader.h"
#include "Player.h"
#include "Timer.h"
#include "LevelLoader.h"
#include "Player.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::Render()
{
	for (auto t : myTerrain)
	{
		t.get()->mySprite.get()->Render();
	}
	for (auto t : mySaws)
	{
		t.get()->mySprite.Render();
	}
}

void Level::Update()
{
	float deltaTime = Timer::GetInstance().GetDeltaTime();

	for (auto t : mySaws)
	{
		t.get()->Update(deltaTime);
	}

}

void Level::Load(std::shared_ptr<LevelData> aData)
{
	myTerrain = aData.get()->GetTiles();
	mySaws = aData.get()->GetSaws();
}

void Level::Init(const EStateType& aState)
{
	std::cout << "level inited\n";
	
	LevelLoader levelLoader;

	Load(levelLoader.LoadLevel("Json/Levels/CollisionTest.json"));

}
