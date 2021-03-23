#include "stdafx.h"
#include "EntityFactory.h"
#include "Saw.h"
#include "Shooter.h"
#include "JsonParser.h"

std::vector<std::shared_ptr<Entity>> EntityFactory::LoadEntities(const char* aPath)
{
	JsonParser jsonParser;

	myDocument = jsonParser.GetDocument(aPath);

	gridSize = myDocument["defs"]["layers"][0]["gridSize"].GetFloat();

	renderSizeX = 1280.f;
	renderSizeY = 720.f;

	std::cout << Tga2D::CEngine::GetInstance()->GetRenderSize().x << std::endl;

	for (int j = 0; j < myDocument["levels"][0]["layerInstances"].Capacity(); j++)
	{
		std::string layerType = myDocument["levels"][0]["layerInstances"][j]["__type"].GetString();

		if (layerType == "Entities")
		{
			int entityArrayLength = static_cast<int>(myDocument["levels"][0]["layerInstances"][j]["entityInstances"].Capacity());

			for (int i = 0; i < entityArrayLength; i++)
			{
				std::string entityType = myDocument["levels"][0]["layerInstances"][j]["entityInstances"][i]["__identifier"].GetString();

				if (entityType == "Saw" || entityType == "saw")
				{
					myEntities.push_back(LoadSaw(i, j));
				}
				if (entityType == "Shooter" || entityType == "shooter")
				{
					myEntities.push_back(LoadShooter(i, j));
				}
			}
		}
	}

	return myEntities;
}

std::shared_ptr<Saw> EntityFactory::LoadSaw(int aEntityIndex, int aLayerIndex)
{
	Saw aSawToPushBack = Saw({	myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize ,
								myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize });


	int currentSawPointAmounts = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].Capacity();

	for (int k = 0; k < currentSawPointAmounts; k++)
	{
		aSawToPushBack.AddPoint({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cx"].GetFloat() / renderSizeX * gridSize,
								  myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cy"].GetFloat() / renderSizeY * gridSize });

	}

	aSawToPushBack.myCollider = Collider(16, { myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize,
											   myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize });

	aSawToPushBack.myCollider.SetTag(EColliderTag::KillZone);

	return std::make_shared<Saw>(aSawToPushBack);

}
std::shared_ptr<Shooter> EntityFactory::LoadShooter(int aEntityIndex, int aLayerIndex)
{
	Shooter shooterToPushBack = Shooter();
	std::string shootDirection = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].GetString();
	float xPosition = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize;
	float yPosition = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize;

	if (shootDirection == "Up")
	{
		shooterToPushBack.Init({ xPosition, yPosition }, Shooter::EFireDirection::Up);
	}
	else if (shootDirection == "Down")
	{
		shooterToPushBack.Init({ xPosition, yPosition }, Shooter::EFireDirection::Down);
	}
	else if (shootDirection == "Right")
	{
		shooterToPushBack.Init({ xPosition, yPosition }, Shooter::EFireDirection::Right);
	}
	else
	{
		shooterToPushBack.Init({ xPosition, yPosition }, Shooter::EFireDirection::Left);
	}

	return std::make_shared<Shooter>(shooterToPushBack);

}
