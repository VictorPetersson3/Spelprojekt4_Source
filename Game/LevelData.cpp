#include "stdafx.h"
#include "LevelData.h"

void LevelData::AddTile(std::shared_ptr<TerrainTile> aTile)
{
	myTiles.push_back(aTile);
}

std::vector<std::shared_ptr<TerrainTile>> LevelData::GetTiles()
{
	return myTiles;
}
