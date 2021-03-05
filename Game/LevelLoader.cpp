#include "stdafx.h"
#include "LevelLoader.h"

#include <fstream>
#include <sstream>
#include <string>

#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
#include "tga2d\engine.h"
#include "Camera.h"
#include "Collider.h"
#include "JsonParser.h"

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
        myCamera.get()->RenderSprite(s.mySprite);
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
                CommonUtilities::Vector2f aColliderPosition = { spriteToPushBack.GetPosition().x + gridSize / worldSize.x / 2,spriteToPushBack.GetPosition().y + gridSize / worldSize.y / 2 };

                Collider colliderToPushBack = Collider(aColliderPosition, gridSize / worldSize.x, gridSize / worldSize.y);

                myTiles.push_back(TerrainTile(spriteToPushBack, colliderToPushBack));

            }
            else
            {
                myTiles.push_back(TerrainTile(spriteToPushBack));
            }
            

        }
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

    aSprite.SetPosition({ posX / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x), posY / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y) });

}

void LevelLoader::SetSpriteSize(Tga2D::CSprite& aSprite, float aGridSize)
{
     aSprite.SetSizeRelativeToImage({ 1.f / (static_cast<float>(aSprite.GetImageSize().x) / aGridSize),1.f / (static_cast<float>(aSprite.GetImageSize().y) / aGridSize) });
}
