#include "stdafx.h"
#include "LevelLoader.h"

#include <fstream>
#include <sstream>
#include <string>

#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"
#include "tga2d\engine.h"

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
}

void LevelLoader::Render()
{
    for (Tga2D::CSprite s : mySprites)
    {
        s.Render();
    }
}

bool LevelLoader::LoadLevel(const char* aLevelPath)
{

    std::string text;
    std::fstream file;

    file.open(aLevelPath);
    {
        std::string line;
        while (std::getline(file, line))
        {
            text.append(line);
        }
    }
    file.close();
    document.Parse(text.c_str());

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
            
            mySprites.push_back(spriteToPushBack);
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
