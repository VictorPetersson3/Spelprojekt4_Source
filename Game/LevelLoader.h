#pragma once
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"
#include <iostream>
#include <vector>
#include<CommonUtilities/Vector2.hpp>
#include <memory>
#include "tga2d\sprite\sprite.h"
#include "TerrainTile.h"
#include "Saw.h"
#include "Level.h"
#include "LevelData.h"


class Camera;

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	void Update(const std::shared_ptr<Camera> aCamera);


	std::shared_ptr<LevelData> LoadLevel(const char* aLevelPath);
	std::shared_ptr<TerrainTile> LoadTileMap(const char* aImagePath, int aGridSize, int aLayerIndex, int aTileIndex);


private:
	std::vector<TerrainTile> myTiles;
	std::vector<Saw> mySaws;


	void SetRect(std::shared_ptr<Tga2D::CSprite> aSprite, int gridTileindex, int layerIndex);
	void SetPosition(std::shared_ptr<Tga2D::CSprite>, int aGridTileIndex, int aLayerIndex);
	void SetSpriteSize(std::shared_ptr<Tga2D::CSprite> aSprite, float aGridSize);

	std::shared_ptr<Saw> AddSaw(int aGridSize, int aEntityIndex, int aLayerIndex, int aRenderSizeX, int aRenderSizeY);

	rapidjson::Document document;

};

