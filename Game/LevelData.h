#pragma once
#include <vector>
#include <memory>
#include <tga2d\math\vector2imp.h>
#include "Saw.h"

struct TerrainTile;

class Collider;

class LevelData
{
public:
	LevelData();
	~LevelData();

	void AddTile(std::shared_ptr<TerrainTile> aTile);
	void AddSaw(std::shared_ptr<Saw> aSaw);
	std::vector<std::shared_ptr<TerrainTile>> GetTiles();

private:
	std::vector<std::shared_ptr<TerrainTile>> myTiles;
	std::vector<std::shared_ptr<Saw>> mySaws;
	Tga2D::Vector2f myPlayerStartPosition;
	std::shared_ptr<Collider> myLevelEndCollider;
};

