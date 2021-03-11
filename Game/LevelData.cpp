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
