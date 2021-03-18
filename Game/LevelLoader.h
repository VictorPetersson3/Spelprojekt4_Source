#pragma once
#include <vector>
#include <memory>
#include<CommonUtilities/Vector2.hpp>
#include "rapidjson\document.h"

namespace Tga2D
{
	class CSprite;
	class CSpriteBatch;
}
class Camera;
class LevelData;
class Saw;
class RenderCommand;
struct TerrainTile;

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	void Update(const std::shared_ptr<Camera> aCamera);


	std::shared_ptr<LevelData> LoadLevel(const char* aLevelPath);
	std::shared_ptr<TerrainTile> LoadTileMap(const char* aImagePath, int aGridSize, int aLayerIndex, int aTileIndex, std::shared_ptr<Tga2D::CSpriteBatch> aSpriteBatch);
	std::shared_ptr<LevelData> LoadLevel(int aLevelIndex);

private:
	std::vector<TerrainTile> myTiles;
	std::vector<Saw> mySaws;

	Tga2D::Vector2f GetPlayerStartPosition();

	void SetRect(RenderCommand& aRenderCommand, int gridTileindex, int layerIndex);
	void SetPosition(RenderCommand& aRenderCommand, int aGridTileIndex, int aLayerIndex);
	void SetSpriteSize(RenderCommand& aRenderCommand, float aGridSize);

	std::shared_ptr<Saw> AddSaw(int aGridSize, int aEntityIndex, int aLayerIndex, int aRenderSizeX, int aRenderSizeY);

	rapidjson::Document document;

};

