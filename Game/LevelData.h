#pragma once
#include <vector>
#include <memory>
#include <tga2d\math\vector2imp.h>

struct TerrainTile;

class Collider;

class LevelData
{
public:
	LevelData();
	~LevelData();

	void AddTile(std::shared_ptr<TerrainTile> aTile);
	std::vector<std::shared_ptr<TerrainTile>> GetTiles();

private:
	std::vector<std::shared_ptr<TerrainTile>> myTiles;
	Tga2D::Vector2f myPlayerStartPosition;
	std::shared_ptr<Collider> myLevelEndCollider;
};

