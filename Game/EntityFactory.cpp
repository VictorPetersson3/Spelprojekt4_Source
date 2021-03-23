#include "stdafx.h"
#include "EntityFactory.h"
#include "Saw.h"
#include "Shooter.h"

std::vector<std::shared_ptr<Entity>> EntityFactory::LoadEntities(const rapidjson::Document aDocument)
{
	myDocument = aDocument;
}

std::shared_ptr<Saw> EntityFactory::LoadSaw(int aEntityIndex, int aLayerIndex)
{
	Saw aSawToPushBack = Saw({	myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / aRenderSizeX * aGridSize ,
								myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / aRenderSizeY * aGridSize });


	int currentSawPointAmounts = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].Capacity();

	for (int k = 0; k < currentSawPointAmounts; k++)
	{
		aSawToPushBack.AddPoint({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cx"].GetFloat() / aRenderSizeX * aGridSize,
								  myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cy"].GetFloat() / aRenderSizeY * aGridSize });

	}

	aSawToPushBack.myCollider = Collider(16, { myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / aRenderSizeX * aGridSize,
											   myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / aRenderSizeY * aGridSize });

	aSawToPushBack.myCollider.SetTag(EColliderTag::KillZone);

	return std::make_shared<Saw>(aSawToPushBack);

}
std::shared_ptr<Shooter> EntityFactory::LoadShooter(int aEntityIndex, int aLayerIndex)
{
    
}
