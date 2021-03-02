#pragma once
#include "rapidjson\rapidjson.h"
#include <iostream>


class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();

	bool LoadLevel(const char* aLevelPath);
};

