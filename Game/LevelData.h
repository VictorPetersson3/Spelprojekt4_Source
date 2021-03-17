#pragma once
#include <vector>
#include <memory>
#include <tga2d\math\vector2imp.h>
#include "CommonUtilities/GrowingArray.hpp"

struct TerrainTile;
class Saw;
class Collider;
namespace Tga2D
{
	class CSpriteBatch;
}
class LevelData
{
public:
	LevelData();
	~LevelData();

	void AddTile(std::shared_ptr<TerrainTile> aTile);
	void AddSaw(std::shared_ptr<Saw> aSaw);
	std::vector<std::shared_ptr<TerrainTile>> GetTiles();
	std::vector<std::shared_ptr<Saw>> GetSaws();
	CommonUtilities::GrowingArray<std::shared_ptr<Tga2D::CSpriteBatch>>& GetSpriteBatches();
	void AddPlayerStart(const Tga2D::Vector2f& aPosition);
	Tga2D::Vector2f GetPlayerStart();

	void AddLevelEnd(std::shared_ptr<Collider> aEndCollider);
	std::shared_ptr<Collider> GetLevelEnd();
	void AddSpriteBatch(std::shared_ptr<Tga2D::CSpriteBatch> aSpriteBatch);

private:
	CommonUtilities::GrowingArray<std::shared_ptr<Tga2D::CSpriteBatch>> mySpriteBatches;
	std::vector<std::shared_ptr<TerrainTile>> myTiles;
	std::vector<std::shared_ptr<Saw>> mySaws;
	Tga2D::Vector2f myPlayerStartPosition;
	std::shared_ptr<Collider> myLevelEndCollider;
};

