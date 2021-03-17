#include "stdafx.h"
#include "LevelData.h"

LevelData::LevelData()
{

}

LevelData::~LevelData()
{

}

void LevelData::AddTile(std::shared_ptr<TerrainTile> aTile)
{
	myTiles.push_back(aTile);
}

void LevelData::AddSaw(std::shared_ptr<Saw> aSaw)
{
	mySaws.push_back(aSaw);
}

std::vector<std::shared_ptr<TerrainTile>> LevelData::GetTiles()
{
	return myTiles;
}

std::vector<std::shared_ptr<Saw>> LevelData::GetSaws()
{
	return mySaws;
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



