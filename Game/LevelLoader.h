#pragma once
#include "rapidjson\rapidjson.h"
#include "rapidjson\document.h"
#include <iostream>
#include <vector>
#include "tga2d\sprite\sprite.h"



class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	void Render();

	bool LoadLevel(const char* aLevelPath);

private:
	std::vector<Tga2D::CSprite> mySprites;

	void SetRect(Tga2D::CSprite& aSprite, int gridTileindex, int layerIndex);
	void SetPosition(Tga2D::CSprite& aSprite, int aGridTileIndex, int aLayerIndex);
	void SetSpriteSize(Tga2D::CSprite& aSprite, float aGridSize);

	rapidjson::Document document;

};

