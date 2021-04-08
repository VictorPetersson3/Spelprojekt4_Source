#include "stdafx.h"
#include "LevelLoader.h"

#include <fstream>
#include <sstream>
#include <string>

#include "rapidjson\rapidjson.h"
#include "tga2d\engine.h"

#include "Camera.h"
#include "Collider.h"
#include "JsonParser.h"

#include "tga2d\sprite\sprite.h"
#include "tga2d/sprite/sprite_batch.h"


#include "LevelData.h"
#include "Level.h"
#include "RenderCommand.h"
#include "Saw.h"
#include "Shooter.h"
#include "TerrainTile.h"
#include "EntityFactory.h"

#include "LevelSelect_SpecificLevelData.h"

#define WINDOW_WIDTH 1280.0f
#define WINDOW_HEIGTH 720.0f

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{

}


int LevelLoader::GetAmountOfLevels()
{
	JsonParser jsonParser;

	rapidjson::Document document;

	document = jsonParser.GetDocument("Json/Levels.json");

	return document["levels"].Capacity();
}

std::shared_ptr<LevelData> LevelLoader::LoadLevel(LevelSelect_SpecificLevelData* someLevelData)
{
	JsonParser jsonParser;
	EntityFactory entityFactory;

	myDocument = jsonParser.GetDocument(someLevelData->myLevelPath.GetString());

	std::shared_ptr<LevelData> levelToPushBack = std::make_shared<LevelData>();

	float gridSize = myDocument["defs"]["layers"][0]["gridSize"].GetInt();
	Tga2D::Vector2f worldSize = { myDocument["levels"][0]["pxWid"].GetFloat(),myDocument["levels"][0]["pxHei"].GetFloat() };

	std::cout << gridSize << std::endl;
	std::cout << worldSize.x << " x " << worldSize.y << std::endl;

	float renderSizeX = 1280.f;
	float renderSizeY = 720.f;
	bool hasAddedPlayerStart = false;

	levelToPushBack->AddEntities(entityFactory.LoadEntities(someLevelData->myLevelPath.GetString()));

	for (int j = 0; j < myDocument["levels"][0]["layerInstances"].Capacity(); j++)
	{
		std::string layerType = myDocument["levels"][0]["layerInstances"][j]["__type"].GetString();

		if (layerType == "Tiles")
		{

			std::string layerIdentifier = myDocument["levels"][0]["layerInstances"][j]["__identifier"].GetString();


			if (layerIdentifier == "Props" || layerIdentifier == "props")
			{
				int tilesArrayLenght = static_cast<int>(myDocument["levels"][0]["layerInstances"][j]["gridTiles"].Capacity());

				std::shared_ptr<Tga2D::CSpriteBatch> spriteBatch = std::make_shared<Tga2D::CSpriteBatch>(false);

				const char* aTileSheetPath = someLevelData->myPropsTileSheetPath.GetString();

				spriteBatch->Init(aTileSheetPath);

				for (int i = 0; i < tilesArrayLenght; i++)
				{
					levelToPushBack.get()->AddTile(LoadTileMap(aTileSheetPath, gridSize, j, i, spriteBatch));
				}
				levelToPushBack->AddSpriteBatch(spriteBatch);
			}
			else
			{
				int tilesArrayLenght = static_cast<int>(myDocument["levels"][0]["layerInstances"][j]["gridTiles"].Capacity());

				std::shared_ptr<Tga2D::CSpriteBatch> spriteBatch = std::make_shared<Tga2D::CSpriteBatch>(false);

				const char* aTileSheetPath = someLevelData->myTileSheetPath.GetString();

				spriteBatch->Init(aTileSheetPath);

				for (int i = 0; i < tilesArrayLenght; i++)
				{
					levelToPushBack.get()->AddTile(LoadTileMap(aTileSheetPath, gridSize, j, i, spriteBatch));
				}
				levelToPushBack->AddSpriteBatch(spriteBatch);
			}
		}
		if (layerType == "Entities")
		{
			int entityArrayLength = static_cast<int>(myDocument["levels"][0]["layerInstances"][j]["entityInstances"].Capacity());

			for (int i = 0; i < entityArrayLength; i++)
			{
				std::string entityType = myDocument["levels"][0]["layerInstances"][j]["entityInstances"][i]["__identifier"].GetString();

				if (entityType == "PlayerStart")
				{
					float xPosition = myDocument["levels"][0]["layerInstances"][j]["entityInstances"][i]["px"][0].GetFloat();
					float yPosition = myDocument["levels"][0]["layerInstances"][j]["entityInstances"][i]["px"][1].GetFloat();

					xPosition /= WINDOW_WIDTH;
					yPosition /= WINDOW_HEIGTH;

					levelToPushBack.get()->AddPlayerStart({ xPosition,yPosition });

					hasAddedPlayerStart = true;
				}

				if (entityType == "LevelEnd")
				{
					float xPosition = myDocument["levels"][0]["layerInstances"][j]["entityInstances"][i]["px"][0].GetFloat();
					float yPosition = myDocument["levels"][0]["layerInstances"][j]["entityInstances"][i]["px"][1].GetFloat();

					xPosition -= 16.f;
					yPosition -= 16.f;

					xPosition /= 1280.f;
					yPosition /= 720.f;

					float width = myDocument["levels"][0]["layerInstances"][j]["entityInstances"][i]["width"].GetFloat();
					float height = myDocument["levels"][0]["layerInstances"][j]["entityInstances"][i]["height"].GetFloat();

					width /= WINDOW_WIDTH;
					height /= WINDOW_HEIGTH;

					CommonUtilities::Vector2f aColliderPosition = { xPosition,yPosition };

					std::shared_ptr<Collider> colliderToPushBack = std::make_shared<Collider>(aColliderPosition, width, height);

					colliderToPushBack.get()->SetTag(EColliderTag::EndZone);

					levelToPushBack.get()->AddLevelEnd(colliderToPushBack);
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

std::shared_ptr<TerrainTile> LevelLoader::LoadTileMap(const char* aImagePath, int aGridSize, int aLayerIndex, int aTileIndex, std::shared_ptr<Tga2D::CSpriteBatch> aSpriteBatch)
{
	RenderCommand tempRenderCommand = RenderCommand(aImagePath, aLayerIndex);

	tempRenderCommand.SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);

	SetRect(tempRenderCommand, aTileIndex, aLayerIndex);

	SetSpriteSize(tempRenderCommand, aGridSize);

	SetPosition(tempRenderCommand, aTileIndex, aLayerIndex);

	std::string layerIdentifier = myDocument["levels"][0]["layerInstances"][aLayerIndex]["__identifier"].GetString();

	aSpriteBatch->AddObject(tempRenderCommand.mySprite.get());

	tempRenderCommand.SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);

	if (layerIdentifier != "Background" && layerIdentifier != "background" && layerIdentifier != "Props" && layerIdentifier != "props")
	{
		CommonUtilities::Vector2f aColliderPosition = { tempRenderCommand.GetPosition().x, tempRenderCommand.GetPosition().y };

		float width = tempRenderCommand.GetSize().x;
		float height = tempRenderCommand.GetSize().y * (16.f / 9.f);

		std::shared_ptr<Collider> colliderToPushBack = std::make_shared<Collider>(aColliderPosition, width * 0.5f, height * 0.5f);

		colliderToPushBack->SetTag(EColliderTag::Terrain);

		return std::make_shared<TerrainTile>(colliderToPushBack, tempRenderCommand);
	}
	else
	{
		return std::make_shared<TerrainTile>(tempRenderCommand);
	}
}


void LevelLoader::SetRect(RenderCommand& aRenderCommand, int gridTileindex, int layerIndex)
{
	const float EPSILON = 0.000001f;

	float gridSize = myDocument["defs"]["layers"][0]["gridSize"].GetFloat();

	float startX = myDocument["levels"][0]["layerInstances"][layerIndex]["gridTiles"][gridTileindex]["src"][0].GetFloat();
	float startY = myDocument["levels"][0]["layerInstances"][layerIndex]["gridTiles"][gridTileindex]["src"][1].GetFloat();

	startX /= static_cast<float>(aRenderCommand.GetImageSize().x);
	startY /= static_cast<float>(aRenderCommand.GetImageSize().y);

	startX -= EPSILON;
	startY -= EPSILON;

	aRenderCommand.SetTextureRect(startX, startY, startX + 32.f / aRenderCommand.GetImageSize().x, startY + 32.f / aRenderCommand.GetImageSize().y);
}

void LevelLoader::SetPosition(RenderCommand& aRenderCommand, int aGridTileIndex, int aLayerIndex)
{
	float posX = myDocument["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][0].GetFloat();
	float posY = myDocument["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][1].GetFloat();

	aRenderCommand.SetPivot({ 0.5f,0.5f });
	aRenderCommand.Update({ posX / WINDOW_WIDTH, posY / WINDOW_HEIGTH });
}

void LevelLoader::SetSpriteSize(RenderCommand& aRenderCommand, float aGridSize)
{
	aRenderCommand.SetSizeRelativeToImage({ 1.f / (static_cast<float>(aRenderCommand.GetImageSize().x) / 32),1.f / (static_cast<float>(aRenderCommand.GetImageSize().y) / 32) });
}
