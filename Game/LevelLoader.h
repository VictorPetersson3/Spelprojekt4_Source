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

class Camera;

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	void Render();
	void Update(const std::shared_ptr<Camera> aCamera);

	bool LoadLevel(const char* aLevelPath);

private:
	std::vector<TerrainTile> myTiles;
	std::vector<Saw> mySaws;
	std::unique_ptr< Camera> myCamera;

	void SetRect(Tga2D::CSprite& aSprite, int gridTileindex, int layerIndex);
	void SetPosition(Tga2D::CSprite& aSprite, int aGridTileIndex, int aLayerIndex);
	void SetSpriteSize(Tga2D::CSprite& aSprite, float aGridSize);

	rapidjson::Document document;

};

