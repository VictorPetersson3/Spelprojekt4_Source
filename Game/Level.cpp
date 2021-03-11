#include "stdafx.h"
#include "Level.h"

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
		t.get()->myCollider.get()->Draw();
	}
}

void Level::Update()
{
}
