#include "stdafx.h"
#include "LevelData.h"

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
<<<<<<< Updated upstream
=======

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
>>>>>>> Stashed changes
