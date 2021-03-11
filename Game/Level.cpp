#include "stdafx.h"
#include "Level.h"
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
		//t.get()->myCollider.get()->Draw();
	}
}

void Level::Update()
{

}

void Level::Load(std::shared_ptr<LevelData> aData)
{
	myTerrain = aData.get()->GetTiles();
}

void Level::Init(const EStateType& aState)
{
	std::cout << "level inited\n";
	
	LevelLoader levelLoader;

	Load(levelLoader.LoadLevel("Json/Levels/CollisionTest.json"));
}
