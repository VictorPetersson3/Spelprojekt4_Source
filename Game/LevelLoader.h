#pragma once
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"
#include <iostream>
#include <vector>
#include<CommonUtilities/Vector2.hpp>
#include <memory>
#include "tga2d\sprite\sprite.h"
#include "TerrainTile.h"
#include "Level.h"
#include "LevelData.h"

class Camera;

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	void Update(const std::shared_ptr<Camera> aCamera);

	LevelData LoadLevel(const char* aLevelPath);
	std::shared_ptr<TerrainTile> LoadTileMap(const char* aImagePath, int aGridSize, int aLayerIndex, int aTileIndex);


private:
	std::vector<TerrainTile> myTiles;

	void SetRect(std::shared_ptr<Tga2D::CSprite> aSprite, int gridTileindex, int layerIndex);
	void SetPosition(std::shared_ptr<Tga2D::CSprite>, int aGridTileIndex, int aLayerIndex);
	void SetSpriteSize(std::shared_ptr<Tga2D::CSprite> aSprite, float aGridSize);

	rapidjson::Document document;

};

