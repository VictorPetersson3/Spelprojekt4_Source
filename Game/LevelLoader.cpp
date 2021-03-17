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

#include "tga2d\sprite\sprite.h"

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{

}

void LevelLoader::Update(const std::shared_ptr<Camera> aCamera)
{
}

std::shared_ptr<LevelData> LevelLoader::LoadLevel(const char* aLevelPath)
{
	JsonParser jsonParser;

	document = jsonParser.GetDocument(aLevelPath);

	std::shared_ptr<LevelData> levelToPushBack = std::make_shared<LevelData>();

	float gridSize = document["defs"]["layers"][0]["gridSize"].GetInt();
	Tga2D::Vector2f worldSize = { document["levels"][0]["pxWid"].GetFloat(),document["levels"][0]["pxHei"].GetFloat() };

	std::cout << gridSize << std::endl;
	std::cout << worldSize.x << " x " << worldSize.y << std::endl;

	float renderSizeX = static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x);
	float renderSizeY = static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y);
	bool hasAddedPlayerStart = false;

	for (int j = 0; j < document["levels"][0]["layerInstances"].Capacity(); j++)
	{
		std::string layerType = document["levels"][0]["layerInstances"][j]["__type"].GetString();

		if (layerType == "Tiles")
		{
			int tilesArrayLenght = static_cast<int>(document["levels"][0]["layerInstances"][j]["gridTiles"].Capacity());

			for (int i = 0; i < tilesArrayLenght; i++)
			{
				levelToPushBack.get()->AddTile(LoadTileMap("Sprites/Tilesets/tiles_Sheet_01.dds", gridSize, j, i));
			}
		}
		if (layerType == "Entities")
		{
			int entityArrayLength = static_cast<int>(document["levels"][0]["layerInstances"][j]["entityInstances"].Capacity());

			

			for (int i = 0; i < entityArrayLength; i++)
			{
				std::string entityType = document["levels"][0]["layerInstances"][j]["entityInstances"][i]["__identifier"].GetString();

				if (entityType == "Saw" || entityType == "saw")
				{
					levelToPushBack.get()->AddSaw(AddSaw(gridSize, i, j, renderSizeX, renderSizeY));
				}

				if (entityType == "PlayerStart")
				{
					float xPosition = document["levels"][0]["layerInstances"][j]["entityInstances"][i]["__grid"][0].GetFloat();
					float yPosition = document["levels"][0]["layerInstances"][j]["entityInstances"][i]["__grid"][1].GetFloat();


					xPosition /= static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x);
					yPosition /= static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y);

					std::cout << xPosition << "\n";


					levelToPushBack.get()->AddPlayerStart({ xPosition,yPosition });

					hasAddedPlayerStart = true;
				}
			}
		}
	}

	if (hasAddedPlayerStart == false)
	{
		levelToPushBack.get()->AddPlayerStart({ 0.5f,0.5f });
	}

	return levelToPushBack;
}

std::shared_ptr<TerrainTile> LevelLoader::LoadTileMap(const char* aImagePath, int aGridSize, int aLayerIndex, int aTileIndex)
{
	RenderCommand tempRenderCommand = RenderCommand(aImagePath, aLayerIndex);
	std::shared_ptr<Tga2D::CSprite> spriteToPushBack = std::make_shared<Tga2D::CSprite>("Sprites/Tilesets/Tiles.dds");

	spriteToPushBack.get()->SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);

	tempRenderCommand.SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);

	SetRect(spriteToPushBack, aTileIndex, aLayerIndex);
	SetRect(tempRenderCommand, aTileIndex, aLayerIndex);

	SetSpriteSize(spriteToPushBack, aGridSize);
	SetSpriteSize(tempRenderCommand, aGridSize);

	SetPosition(spriteToPushBack, aTileIndex, aLayerIndex);
	SetPosition(tempRenderCommand, aTileIndex, aLayerIndex);

	std::string layerIdentifier = document["levels"][0]["layerInstances"][aLayerIndex]["__identifier"].GetString();

	if (layerIdentifier != "Background" || layerIdentifier != "background")
	{
		CommonUtilities::Vector2f aColliderPosition = { spriteToPushBack.get()->GetPosition().x,spriteToPushBack.get()->GetPosition().y };

		float width = spriteToPushBack.get()->GetSize().x;
		float height = spriteToPushBack.get()->GetSize().y * Tga2D::CEngine::GetInstance()->GetWindowRatio();

		std::shared_ptr<Collider> colliderToPushBack = std::make_shared<Collider>(aColliderPosition, width * 0.5f, height * 0.5f);

		return std::make_shared<TerrainTile>(colliderToPushBack, tempRenderCommand);
	}
	else
	{
		return std::make_shared<TerrainTile>(tempRenderCommand);
	}
}

std::shared_ptr<LevelData> LevelLoader::LoadLevel(int aLevelIndex)
{
	JsonParser jsonParser;

	rapidjson::Document document;

	document = jsonParser.GetDocument("Json/Levels.json");

	assert(aLevelIndex <= document["levels"].Capacity());

	const char* path = document["levels"][aLevelIndex]["path"].GetString();

	return LoadLevel(path);
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

	startX -= EPSILON;
	startY -= EPSILON;

	aSprite.get()->SetTextureRect(startX, startY, startX + gridSize / worldSize.x, startY + gridSize / worldSize.y);
}

void LevelLoader::SetPosition(std::shared_ptr<Tga2D::CSprite> aSprite, int aGridTileIndex, int aLayerIndex)
{
	float posX = document["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][0].GetFloat();
	float posY = document["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][1].GetFloat();

	aSprite.get()->SetPivot({ 0.5f,0.5f });
	aSprite.get()->SetPosition({ posX / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x), posY / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y) });
}

void LevelLoader::SetSpriteSize(std::shared_ptr<Tga2D::CSprite> aSprite, float aGridSize)
{
	aSprite.get()->SetSizeRelativeToImage({ 1.f / (static_cast<float>(aSprite.get()->GetImageSize().x) / aGridSize),1.f / (static_cast<float>(aSprite.get()->GetImageSize().y) / aGridSize) });
}

void LevelLoader::SetRect(RenderCommand& aRenderCommand, int gridTileindex, int layerIndex)
{
	const float EPSILON = 0.000001f;

	float gridSize = document["defs"]["layers"][0]["gridSize"].GetInt();
	Tga2D::Vector2f worldSize = { document["levels"][0]["pxWid"].GetFloat(),document["levels"][0]["pxHei"].GetFloat() };

	float startX = document["levels"][0]["layerInstances"][layerIndex]["gridTiles"][gridTileindex]["src"][0].GetInt();
	float startY = document["levels"][0]["layerInstances"][layerIndex]["gridTiles"][gridTileindex]["src"][1].GetInt();

	startX /= static_cast<float>(aRenderCommand.GetImageSize().x);
	startY /= static_cast<float>(aRenderCommand.GetImageSize().y);

	startX -= EPSILON;
	startY -= EPSILON;

	aRenderCommand.SetTextureRect(startX, startY, startX + gridSize / worldSize.x, startY + gridSize / worldSize.y);
}

void LevelLoader::SetPosition(RenderCommand& aRenderCommand, int aGridTileIndex, int aLayerIndex)
{
	float posX = document["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][0].GetFloat();
	float posY = document["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][1].GetFloat();

	aRenderCommand.SetPivot({ 0.5f,0.5f });
	aRenderCommand.Update({ posX / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x), posY / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y) });
}

void LevelLoader::SetSpriteSize(RenderCommand& aRenderCommand, float aGridSize)
{
	aRenderCommand.SetSizeRelativeToImage({ 1.f / (static_cast<float>(aRenderCommand.GetImageSize().x) / aGridSize),1.f / (static_cast<float>(aRenderCommand.GetImageSize().y) / aGridSize) });
}

Tga2D::Vector2f LevelLoader::GetPlayerStartPosition()
{
	return Tga2D::Vector2f();
}

std::shared_ptr<Saw> LevelLoader::AddSaw(int aGridSize, int aEntityIndex, int aLayerIndex, int aRenderSizeX, int aRenderSizeY)
{

	Saw aSawToPushBack = Saw({ document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / aRenderSizeX * aGridSize ,
							   document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / aRenderSizeY * aGridSize });


	int currentSawPointAmounts = document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].Capacity();

	for (int k = 0; k < currentSawPointAmounts; k++)
	{
		aSawToPushBack.AddPoint({ document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cx"].GetFloat() / aRenderSizeX * aGridSize,
								  document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cy"].GetFloat() / aRenderSizeY * aGridSize });

	}

	aSawToPushBack.myCollider = Collider(16, { document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / aRenderSizeX * aGridSize,
											   document["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / aRenderSizeY * aGridSize }); 

	aSawToPushBack.myCollider.SetTag(EColliderTag::KillZone);

	return std::make_shared<Saw>(aSawToPushBack);

}