#include "stdafx.h"
#include "LevelLoader.h"

#include <fstream>
#include <sstream>
#include <string>

#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
#include "tga2d\engine.h"

#include "tga2d\sprite\textured_quad.h"

#include "Camera.h"
#include "Collider.h"
#include "JsonParser.h"

#include "Camera.h"
#include "Collider.h"
#include "JsonParser.h"

#include <assert.h> 

LevelLoader::LevelLoader()
{
	myCamera = std::make_unique<Camera>();
}

LevelLoader::~LevelLoader()
{
}

void LevelLoader::Render()
{

}

void LevelLoader::Update(const std::shared_ptr<Camera> aCamera)
{
	for (TerrainTile s : myTiles)
	{

		aCamera.get()->RenderSprite(s.mySprite);
		s.myCollider.Draw();


	}

	for (Saw s : mySaws)
	{
		s.Update(0.001);
		aCamera.get()->RenderSprite(s.mySprite);
		s.myCollider.Draw();
	}


}

bool LevelLoader::LoadLevel(const char* aLevelPath)
{
	JsonParser jsonParser;

	document = jsonParser.GetDocument(aLevelPath);

	float gridSize = document["defs"]["layers"][0]["gridSize"].GetInt();
	Tga2D::Vector2f worldSize = { document["levels"][0]["pxWid"].GetFloat(),document["levels"][0]["pxHei"].GetFloat() };

	std::cout << gridSize << std::endl;
	std::cout << worldSize.x << " x " << worldSize.y << std::endl;


	for (int j = 0; j < document["levels"][0]["layerInstances"].Capacity(); j++)
	{
		int tilesArrayLenght = static_cast<int>(document["levels"][0]["layerInstances"][j]["gridTiles"].Capacity());

		for (int i = 0; i < tilesArrayLenght; i++)
		{
			Tga2D::CSprite spriteToPushBack = Tga2D::CSprite("Sprites/Tilesets/Tiles.dds");

			spriteToPushBack.SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);

			SetRect(spriteToPushBack, i, j);

			SetSpriteSize(spriteToPushBack, gridSize);

			SetPosition(spriteToPushBack, i, j);



			std::string layerIdentifier = document["levels"][0]["layerInstances"][j]["__identifier"].GetString();

			if (layerIdentifier != "Background" || layerIdentifier != "background")
			{

				CommonUtilities::Vector2f aColliderPosition = { spriteToPushBack.GetPosition().x,spriteToPushBack.GetPosition().y };

				float width = spriteToPushBack.GetSize().x;
				float height = spriteToPushBack.GetSize().y * Tga2D::CEngine::GetInstance()->GetWindowRatio();

				Collider colliderToPushBack = Collider(aColliderPosition, width * 0.5f, height * 0.5f);

				myTiles.push_back(TerrainTile(spriteToPushBack, colliderToPushBack));
			}
			else
			{
				myTiles.push_back(TerrainTile(spriteToPushBack));
			}
		}

	/*	int sawsArrayLength = static_cast<int>(document["levels"][0]["layerInstances"][j]["entityInstances"].Capacity());

		for (int i = 0; i < sawsArrayLength; i++)
		{
			Saw aSawToPushBack = Saw({ document["levels"][0]["layerInstances"][j]["entityInstances"][i]["px"][0].GetFloat(),
									   document["levels"][0]["layerInstances"][j]["entityInstances"][i]["px"][1].GetFloat() });


			int currentSawPointAmounts = document["levels"][0]["layerInstances"][j]["entityInstances"][i]["fieldInstances"][0]["__value"].Capacity();
			for (int k = 0; k < currentSawPointAmounts; k++)
			{
				aSawToPushBack.AddPoint({ document["levels"][0]["layerInstances"][j]["entityInstances"][i]["fieldInstances"][0]["__value"][k]["cx"].GetFloat(),
										  document["levels"][0]["layerInstances"][j]["entityInstances"][i]["fieldInstances"][0]["__value"][k]["cy"].GetFloat() });
			}
		}*/
	}


	return false;
}

void LevelLoader::SetRect(Tga2D::CSprite& aSprite, int gridTileindex, int layerIndex)
{
	const float EPSILON = 0.000001f;

	float gridSize = document["defs"]["layers"][0]["gridSize"].GetInt();
	Tga2D::Vector2f worldSize = { document["levels"][0]["pxWid"].GetFloat(),document["levels"][0]["pxHei"].GetFloat() };

	float startX = document["levels"][0]["layerInstances"][layerIndex]["gridTiles"][gridTileindex]["src"][0].GetInt();
	float startY = document["levels"][0]["layerInstances"][layerIndex]["gridTiles"][gridTileindex]["src"][1].GetInt();

	startX /= static_cast<float>(aSprite.GetImageSize().x);
	startY /= static_cast<float>(aSprite.GetImageSize().y);

	startX += EPSILON;
	startY += EPSILON;

	aSprite.SetTextureRect(startX, startY, startX + gridSize / worldSize.x, startY + gridSize / worldSize.y);
}

void LevelLoader::SetPosition(Tga2D::CSprite& aSprite, int aGridTileIndex, int aLayerIndex)
{
	float posX = document["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][0].GetFloat();
	float posY = document["levels"][0]["layerInstances"][aLayerIndex]["gridTiles"][aGridTileIndex]["px"][1].GetFloat();

	aSprite.SetPivot({ 0.5f,0.5f });
	aSprite.SetPosition({ posX / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x) + 0.2f, posY / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y) + 0.2f });

}

void LevelLoader::SetSpriteSize(Tga2D::CSprite& aSprite, float aGridSize)
{
	aSprite.SetSizeRelativeToImage({ 1.f / (static_cast<float>(aSprite.GetImageSize().x) / aGridSize),1.f / (static_cast<float>(aSprite.GetImageSize().y) / aGridSize) });
}
