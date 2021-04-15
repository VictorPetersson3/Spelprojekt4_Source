#include "stdafx.h"
#include "EntityFactory.h"
#include "Saw.h"
#include "Shooter.h"
#include "MovingPlatform.h"
#include "JsonParser.h"
#include "CollapsingTile.h"
#include "KillZone.h"
#include "Key.h"
#include "Door.h"

std::vector<std::shared_ptr<Entity>> EntityFactory::LoadEntities(const char* aPath)
{
	JsonParser jsonParser;

	myDocument = jsonParser.GetDocument(aPath);

	gridSize = myDocument["defs"]["layers"][0]["gridSize"].GetFloat();


	renderSizeX = Tga2D::CEngine::GetInstance()->GetTargetSize().myX;
	renderSizeY = Tga2D::CEngine::GetInstance()->GetTargetSize().myY;


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
				if (entityType == "CollapsingTile")
				{
					myEntities.push_back(LoadCollapsingTile(i, j));
				}
				if (entityType == "KillZone")
				{
					myEntities.push_back(LoadKillZone(i, j));
				}
				
				
				
				
				
				
				
				
			}
		}
	}
	return myEntities;
}

std::shared_ptr<Saw> EntityFactory::LoadSaw(int aEntityIndex, int aLayerIndex)
{
	bool isFlipped = false;

	if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"].Capacity() > 2)

	{
		isFlipped = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][2]["__value"].GetBool();
	}
	Saw aSawToPushBack = Saw({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize ,
								myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize },
								isFlipped);

	std::shared_ptr<Collider> collider;

	int currentSawPointAmounts = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].Capacity();

	for (int k = 0; k < currentSawPointAmounts; k++)
	{
		aSawToPushBack.AddPoint({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cx"].GetFloat() / renderSizeX * gridSize,
								  myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cy"].GetFloat() / renderSizeY * gridSize });

	}

	

	if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"].Capacity() > 1)
	{
		aSawToPushBack.SetRepeating(myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][1]["__value"].GetBool());

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
	float xPosition = (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize) - (1/ renderSizeX * gridSize);
	float yPosition = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize;
	bool isFlipped = false;
	float fireRate = 5;

	std::shared_ptr<Collider> collider = std::make_shared<Collider>(gridSize / renderSizeX, CommonUtilities::Vector2f{ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize,
													myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize });

	collider->SetTag(EColliderTag::IgnoreCollision);

	shooterToPushBack.myCollider = collider;

	if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"].Capacity() > 1)

	{
		isFlipped = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][1]["__value"].GetBool();
	}
	if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"].Capacity() > 2)

	{
		shooterToPushBack.SetFireRate(myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][2]["__value"].GetFloat());
	}

	if (shootDirection == "Up")
	{
		shooterToPushBack.Init({ xPosition, yPosition }, Shooter::EFireDirection::Up, isFlipped);
	}
	else if (shootDirection == "Down")
	{
		shooterToPushBack.Init({ xPosition, yPosition }, Shooter::EFireDirection::Down, isFlipped);
	}
	else if (shootDirection == "Right")
	{
		shooterToPushBack.Init({ xPosition, yPosition }, Shooter::EFireDirection::Right, isFlipped);
	}
	else
	{
		shooterToPushBack.Init({ xPosition, yPosition }, Shooter::EFireDirection::Left, isFlipped);
	}

	return std::make_shared<Shooter>(shooterToPushBack);

}
std::shared_ptr<MovingPlatform> EntityFactory::LoadMovingPlatform(int aEntityIndex, int aLayerIndex)
{
	MovingPlatform aPlatformToPushBack = MovingPlatform({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize ,
								myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize });

	std::shared_ptr<Collider> collider;

	int pointAmounts = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"].Capacity();

	for (int k = 0; k < pointAmounts; k++)
	{
		aPlatformToPushBack.AddPoint({ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cx"].GetFloat() / renderSizeX * gridSize,
								  myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][0]["__value"][k]["cy"].GetFloat() / renderSizeY * gridSize });

	}

	if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"].Capacity() > 1)
	{
		if (myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][1].IsBool())
		{
			aPlatformToPushBack.SetRepeating(myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["fieldInstances"][1].GetBool());
		}
	}

	Vector2 position = CommonUtilities::Vector2f{ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][0].GetFloat() / renderSizeX * gridSize,
													myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["__grid"][1].GetFloat() / renderSizeY * gridSize };
	Vector2 size = Vector2{ myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["width"].GetFloat(),
							myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["height"].GetFloat() };

	aPlatformToPushBack.SetSize(size, gridSize);
	collider = std::make_shared<Collider>(position, size.X / renderSizeX, size.Y / renderSizeY);

	collider->SetTag(EColliderTag::MovingPlatform);

	aPlatformToPushBack.SetCollider(collider);

	return std::make_shared<MovingPlatform>(aPlatformToPushBack);

}
std::shared_ptr<CollapsingTile> EntityFactory::LoadCollapsingTile(int aEntityIndex, int aLayerindex)
{
	float xPosition = myDocument["levels"][0]["layerInstances"][aLayerindex]["entityInstances"][aEntityIndex]["px"][0].GetFloat();
	float yPosition = myDocument["levels"][0]["layerInstances"][aLayerindex]["entityInstances"][aEntityIndex]["px"][1].GetFloat();


	return std::make_shared<CollapsingTile>(CommonUtilities::Vector2f(xPosition, yPosition));
}
std::shared_ptr<KillZone> EntityFactory::LoadKillZone(int aEntityIndex, int aLayerIndex)
{
	float width = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["width"].GetFloat();
	float height = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["height"].GetFloat();

	float xPosition = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["px"][0].GetFloat();
	float yPosition = myDocument["levels"][0]["layerInstances"][aLayerIndex]["entityInstances"][aEntityIndex]["px"][1].GetFloat();

	return std::make_shared<KillZone>(width, height, CommonUtilities::Vector2f{ xPosition,yPosition });
}
