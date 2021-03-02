#include "stdafx.h"
#include "LevelLoader.h"

#include <fstream>
#include <sstream>
#include <string>

#include "rapidjson\document.h"
#include "rapidjson\filereadstream.h"

LevelLoader::LevelLoader()
{
}

LevelLoader::~LevelLoader()
{
}

bool LevelLoader::LoadLevel(const char* aLevelPath)
{
    rapidjson::Document document;

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

    int gridSize = document["defs"]["layers"][0]["gridSize"].GetInt();
    Tga2D::Vector2f worldSize = { document["levels"][0]["pxWid"].GetFloat(),document["levels"][0]["pxHei"].GetFloat() };

    std::cout << gridSize << std::endl;
    std::cout << worldSize.x << " x " << worldSize.y << std::endl;

    return false;
}
