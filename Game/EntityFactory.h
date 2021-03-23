#pragma once
#include "Entity.h"
#include <vector>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

class Shooter;
class Saw;
class EntityFactory
{
	std::vector<std::shared_ptr<Entity>> LoadEntities(const rapidjson::Document aDocument);

	std::shared_ptr<Saw>		LoadSaw		(int aEntityIndex, int aLayerIndex);
	std::shared_ptr<Shooter>	LoadShooter	(int aEntityIndex, int aLayerIndex);

private:

	rapidjson::Document myDocument;
	int aGridSize;
	int aRenderSizeX;
	int aRenderSizeY;
	
};

