#include "stdafx.h"
#include "LevelLoader.h"

#include <fstream>
#include <sstream>
#include <string>

#include "rapidjson\document.h"
#include "tga2d\engine.h"

#include "Camera.h"
#include "Collider.h"
#include "JsonParser.h"

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{

}

void LevelLoader::Update(const std::shared_ptr<Camera> aCamera)
{
}

LevelData LevelLoader::LoadLevel(const char* aLevelPath)
{
	JsonParser jsonParser;

	document = jsonParser.GetDocument(aLevelPath);

	LevelData levelToPushBack;

	float gridSize = document["defs"]["layers"][0]["gridSize"].GetInt();
	Tga2D::Vector2f worldSize = { document["levels"][0]["pxWid"].GetFloat(),document["levels"][0]["pxHei"].GetFloat() };

	std::cout << gridSize << std::endl;
	std::cout << worldSize.x << " x " << worldSize.y << std::endl;
	float renderSizeX = static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x);
	float renderSizeY = static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y);


	for (int j = 0; j < document["levels"][0]["layerInstances"].Capacity(); j++)
	{
		std::string layerType = document["levels"][0]["layerInstances"][j]["__type"].GetString();

		if (layerType == "Tiles")
		{
			int tilesArrayLenght = static_cast<int>(document["levels"][0]["layerInstances"][j]["gridTiles"].Capacity());

			for (int i = 0; i < tilesArrayLenght; i++)
			{
				levelToPushBack.AddTile(LoadTileMap("Sprites/Tilesets/Tiles.dds", gridSize, j, i));
			}
		}
		if (layerType == "Entities")
		{
			int sawsArrayLength = static_cast<int>(document["levels"][0]["layerInstances"][j]["entityInstances"].Capacity());

			for (int i = 0; i < sawsArrayLength; i++)
			{
				levelToPushBack.AddSaw(AddSaw(gridSize, i, j, renderSizeX, renderSizeY));
			}
		}
	}

	return levelToPushBack;
}

std::shared_ptr<TerrainTile> LevelLoader::LoadTileMap(const char* aImagePath, int aGridSize, int aLayerIndex, int aTileIndex)
{
	std::shared_ptr<Tga2D::CSprite> spriteToPushBack = std::make_shared<Tga2D::CSprite>("Sprites/Tilesets/Tiles.dds");

	spriteToPushBack.get()->SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);

	SetRect(spriteToPushBack, aTileIndex, aLayerIndex);

	SetSpriteSize(spriteToPushBack, aGridSize);

	SetPosition(spriteToPushBack, aTileIndex, aLayerIndex);

	std::string layerIdentifier = document["levels"][0]["layerInstances"][aLayerIndex]["__identifier"].GetString();

	if (layerIdentifier != "Background" || layerIdentifier != "background")
	{
		CommonUtilities::Vector2f aColliderPosition = { spriteToPushBack.get()->GetPosition().x,spriteToPushBack.get()->GetPosition().y };

		float width = spriteToPushBack.get()->GetSize().x;
		float height = spriteToPushBack.get()->GetSize().y * Tga2D::CEngine::GetInstance()->GetWindowRatio();

		std::shared_ptr<Collider> colliderToPushBack = std::make_shared<Collider>(aColliderPosition, width * 0.5f, height * 0.5f);

		return std::make_shared<TerrainTile>(spriteToPushBack, colliderToPushBack);
	}
	else
	{
		return std::make_shared<TerrainTile>(spriteToPushBack);
	}

	return false;
}

void LevelLoader::SetRect(std::shared_ptr<Tga2D::CSprite> aSprite, int gridTileindex, int layerIndex)
{
	const float EPSILON = 0.000001f;

	float gridSize = document["defs"]["layers"][0]["gridSize"].GetInt();
	Tga2D::Vector2f worldSize = { document["levels"][0]["pxWid"].GetFloat(),document["levels"][0]["pxHei"].GetFloat() };

	float startX = document["levels"][0]["layerInstances"][layerIndex]["gridTiles"][gridTileindex]["src"][0].GetInt();
	float startY = document["levels"][0]["layerInstances"][layerIndex]["gridTiles"][gridTileindex]["src"][1].GetInt();

	startX /= static_cast<float>(aSprite.get()->GetImageSize().x);
	startY /= static_cast<float>(aSprite.get()->GetImageSize().y);

	startX += EPSILON;
	startY += EPSILON;

	aSprite.get()->SetTextureRect(startX, startY, startX + gridSize / worldSize.x, startY + gridSize / worldSize.y);
}

void LevelLoader::SetPosition(std::shared_ptr<Tga2D::CSprite> aSprite, int aGridTileIndex, int aLayerIndex)
{
	float posX = document["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][0].GetFloat();
	float posY = document["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][1].GetFloat();

	aSprite.get()->SetPivot({ 0.5f,0.5f });
	aSprite.get()->SetPosition({ posX / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x) + 0.2f, posY / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y) + 0.2f });
}

void LevelLoader::SetSpriteSize(std::shared_ptr<Tga2D::CSprite> aSprite, float aGridSize)
{
	aSprite.get()->SetSizeRelativeToImage({ 1.f / (static_cast<float>(aSprite.get()->GetImageSize().x) / aGridSize),1.f / (static_cast<float>(aSprite.get()->GetImageSize().y) / aGridSize) });
}

std::shared_ptr<Saw> LevelLoader::AddSaw(int aGridSize, int aEntityIndex, int aLayerIndex, int aRenderSizeX, int aRenderSizeY)
{

	Saw aSawToPushBack = Saw({ document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / aRenderSizeX * aGridSize + 0.2f,
							   document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / aRenderSizeY * aGridSize + 0.2f });


	int currentSawPointAmounts = document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].Capacity();

	for (int k = 0; k < currentSawPointAmounts; k++)
	{
		aSawToPushBack.AddPoint({ document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cx"].GetFloat() / aRenderSizeX * aGridSize + 0.2f,
								  document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cy"].GetFloat() / aRenderSizeY * aGridSize + 0.2f });

	}

	return std::make_shared<Saw>(aSawToPushBack);

}