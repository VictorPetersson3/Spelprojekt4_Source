#pragma once
#include <vector>
#include <memory>
#include<CommonUtilities/Vector2.hpp>
#include "rapidjson\document.h"
#include "Enums.h"

namespace Tga2D
{
	class CSprite;
	class CSpriteBatch;
}
class Camera;
class LevelData;
class Saw;
class Shooter;
class RenderCommand;
struct TerrainTile;
struct LevelSelect_SpecificLevelData;

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	int GetAmountOfLevels();

	std::shared_ptr<LevelData> LoadLevel(LevelSelect_SpecificLevelData* someLevelData);
	std::shared_ptr<TerrainTile> LoadTileMap(const char* aImagePath, int aGridSize, int aLayerIndex, int aTileIndex, std::shared_ptr<Tga2D::CSpriteBatch> aSpriteBatch);

private:
	std::vector<TerrainTile> myTiles;
	std::vector<Saw> mySaws;

	void SetRect(RenderCommand& aRenderCommand, int gridTileindex, int layerIndex);
	void SetPosition(RenderCommand& aRenderCommand, int aGridTileIndex, int aLayerIndex);
	void SetSpriteSize(RenderCommand& aRenderCommand, float aGridSize);

	int myLevelindex = 0;

	rapidjson::Document myDocument;
	std::shared_ptr<Saw> AddSaw(int aGridSize, int aEntityIndex, int aLayerIndex, int aRenderSizeX, int aRenderSizeY);
	EPowerUp mySelectedPower = EPowerUp::Default;
};

