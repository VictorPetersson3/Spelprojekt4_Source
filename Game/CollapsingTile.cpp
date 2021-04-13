#include "stdafx.h"
#include "CollapsingTile.h"
#include "RenderCommand.h"
#include "Collider.h"
#include "CollisionManager.h"
#include <iostream>
#include "AnimationClip.h"
#include "Camera.h"

CollapsingTile::CollapsingTile(CommonUtilities::Vector2f aPosition)
{
	float posX = aPosition.x / 1280.f;
	float posY = aPosition.y / 720.f;

	myAnimationClip = std::make_shared<AnimationClip>("Sprites/Tilesets/breakableTileSet_spriteSheets/Tile_06_SpriteSheet.dds", 1, 0);
	myAnimationClip->Init({ 7,1 }, { 6,1 });

	CommonUtilities::Vector2f colliderPosition = { posX,posY };

	float width = 32.f / 1280;
	float height = 32.f / 720 * (16.f / 9.f);

	myCollider = std::make_shared<Collider>(colliderPosition, width/2.f, height/2.f);

}

CollapsingTile::~CollapsingTile()
{
	myCollider->RemoveFromManager();
}

void CollapsingTile::Update(float aDeltaTime)
{
	if (myShouldBeRendered == true)
	{
		if (CollisionManager::GetInstance().GetPlayerCollider() != nullptr)
		{
			if (CollisionManager::GetInstance().CheckCollision(myCollider.get(), CollisionManager::GetInstance().GetPlayerCollider()) && myHasBeenHitByPlayer == false)
			{
				myHasBeenHitByPlayer = true;
				myAnimationClip->PlayAnimOnce();
			}
		}
		
		if (myHasBeenHitByPlayer)
		{
			myTimer += aDeltaTime;
			
			if (myTimer >= myCooldownTime)
			{
				myCollider->SetTag(EColliderTag::IgnoreCollision);
				myShouldBeRendered = false;
				myCollider->RemoveFromManager();
			}
		}
	}

}

void CollapsingTile::Render(const std::shared_ptr<Camera> aCamera)
{
	if (myShouldBeRendered)
	{
		aCamera->RenderSprite(myAnimationClip->GetRenderCommand());
		//myCollider->Draw();
	}

}

std::vector<std::shared_ptr<Collider>> CollapsingTile::GetAllColliders()
{
	std::vector<std::shared_ptr<Collider>> returnVector;
	returnVector.push_back(myCollider);
	return returnVector;
}
