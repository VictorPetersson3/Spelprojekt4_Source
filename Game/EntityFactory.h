#pragma once
#include "Entity.h"
#include <vector>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

class Shooter;
class Saw;
class EntityFactory
{
	std::vector<std::shared_ptr<Entity>> LoadEntities(rapidjson::Document& aDocument);

	std::shared_ptr<Saw>		LoadSaw		(int aGridSize, int aEntityIndex, int aLayerIndex, int aRenderSizeX, int aRenderSizeY);
	std::shared_ptr<Shooter>	LoadShooter	(int aGridSize, int aEntityIndex, int aLayerIndex, int aRenderSizeX, int aRenderSizeY);

private:

	rapidjson::Document* myDocument;
	
};

