#include "stdafx.h"
#include "EntityFactory.h"
#include "Saw.h"
#include "Shooter.h"
#include "MovingPlatform.h"
#include "JsonParser.h"

std::vector<std::shared_ptr<Entity>> EntityFactory::LoadEntities(const char* aPath)
{
	JsonParser jsonParser;

	myDocument = jsonParser.GetDocument(aPath);

	gridSize = myDocument["defs"]["layers"][0]["gridSize"].GetFloat();

	renderSizeX = 1280.f;
	renderSizeY = 720.f;


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
				if (entityType == "MovingPlatform" || entityType == "movingplatform")
				{
					myEntities.push_back(LoadMovingPlatform(i, j));
				}
			}
		}
	}

	return myEntities;
}

std::shared_ptr<Saw> EntityFactory::LoadSaw(int aEntityIndex, int aLayerIndex)
{
	Saw aSawToPushBack = Saw({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * 16 ,
								myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * 16 });

	std::shared_ptr<Collider> collider;

	int currentSawPointAmounts = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].Capacity();

	for (int k = 0; k < currentSawPointAmounts; k++)
	{
		aSawToPushBack.AddPoint({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cx"].GetFloat() / renderSizeX * 16,
								  myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cy"].GetFloat() / renderSizeY * 16 });

	}

	if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"].Capacity() > 1)
	{
		if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][1].IsBool())
		{
			aSawToPushBack.SetRepeating(myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][1].GetBool());
		}
	}

	collider = std::make_shared<Collider>(16 / renderSizeX, CommonUtilities::Vector2f{ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize,
													myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize });

	collider->SetTag(EColliderTag::KillZone);

	aSawToPushBack.SetCollider(collider);

	return std::make_shared<Saw>(aSawToPushBack);

}
std::shared_ptr<Shooter> EntityFactory::LoadShooter(int aEntityIndex, int aLayerIndex)
{
	Shooter shooterToPushBack = Shooter();
	std::string shootDirection = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].GetString();
	float xPosition = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * 16;
	float yPosition = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * 16;

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
std::shared_ptr<MovingPlatform> EntityFactory::LoadMovingPlatform(int aEntityIndex, int aLayerIndex)
{
	MovingPlatform aPlatformToPushBack = MovingPlatform({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * 16 ,
								myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * 16 });

	std::shared_ptr<Collider> collider;

	int pointAmounts = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].Capacity();

	for (int k = 0; k < pointAmounts; k++)
	{
		aPlatformToPushBack.AddPoint({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cx"].GetFloat() / renderSizeX * 16,
								  myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cy"].GetFloat() / renderSizeY * 16 });

	}

	if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"].Capacity() > 1)
	{
		if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][1].IsBool())
		{
			aPlatformToPushBack.SetRepeating(myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][1].GetBool());
		}
	}

	Vector2 position = CommonUtilities::Vector2f{	myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize,
													myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize };
	Vector2 size = Vector2{ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["width"].GetFloat(),
							myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["height"].GetFloat() };

	aPlatformToPushBack.SetSize(size, gridSize);
	collider = std::make_shared<Collider>(position, size.X / renderSizeX, size.Y / renderSizeY);

	collider->SetTag(EColliderTag::Terrain);

	aPlatformToPushBack.SetCollider(collider);

	return std::make_shared<MovingPlatform>(aPlatformToPushBack);

}