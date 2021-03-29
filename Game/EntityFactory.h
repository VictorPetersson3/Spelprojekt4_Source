#pragma once
#include "Entity.h"
#include <vector>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

class Shooter;
class Saw;
class MovingPlatform;
class EntityFactory
{
public:
	std::vector<std::shared_ptr<Entity>> LoadEntities(const char* aPath);

	std::shared_ptr<Saw>				LoadSaw				(int aEntityIndex, int aLayerIndex);
	std::shared_ptr<Shooter>			LoadShooter			(int aEntityIndex, int aLayerIndex);

	std::shared_ptr<MovingPlatform>		LoadMovingPlatform	(int aEntityIndex, int aLayerIndex);

private:

	std::vector<std::shared_ptr<Entity>> myEntities;
	rapidjson::Document myDocument;
	float gridSize;
	float renderSizeX;
	float renderSizeY;
	
};

