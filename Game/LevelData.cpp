#include "stdafx.h"
#include "LevelData.h"
#include "Saw.h"
#include "TerrainTile.h"
#include "tga2d/sprite/sprite_batch.h"
#include "Collider.h"
#include "Shooter.h"


LevelData::LevelData()
{
	mySpriteBatches.Init(10);
}

LevelData::~LevelData()
{

}

void LevelData::AddTile(std::shared_ptr<TerrainTile> aTile)
{
	myTiles.push_back(aTile);
}

void LevelData::AddEntities(std::vector<std::shared_ptr<Entity>> someEntities)
{
	myEntities = someEntities;
}

std::vector<std::shared_ptr<TerrainTile>> LevelData::GetTiles()
{
	return myTiles;
}

std::vector<std::shared_ptr<Entity>> LevelData::GetEntities()
{
	return myEntities;
}
CommonUtilities::GrowingArray<std::shared_ptr<Tga2D::CSpriteBatch>>& LevelData::GetSpriteBatches()
{
	return mySpriteBatches;
}

void LevelData::AddPlayerStart(const Tga2D::Vector2f& aPosition)
{
	myPlayerStartPosition = aPosition;
}

Tga2D::Vector2f LevelData::GetPlayerStart()
{
	return myPlayerStartPosition;
}

void LevelData::AddLevelEnd(std::shared_ptr<Collider> aEndCollider)
{
	myLevelEndCollider = aEndCollider;
}

std::shared_ptr<Collider> LevelData::GetLevelEnd()
{
	return myLevelEndCollider;
}

void LevelData::AddSpriteBatch(std::shared_ptr<Tga2D::CSpriteBatch> aSpriteBatch)
{
	mySpriteBatches.Add(aSpriteBatch);
}



