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

	float colliderPosX = aPosition.x;
	float colliderPosY = aPosition.y;

	colliderPosX -= 16.f;
	colliderPosY -= 16.f;

	colliderPosX /= 1280.f;
	colliderPosY /= 720.f;

	float width = 32.f / 1280;
	float height = 32.f / 720 * (16.f / 9.f);

	InitAnimation();
	
	myAnimationClip->GetRenderCommand().Update({ posX,posY });
	
	CommonUtilities::Vector2f colliderPosition = {colliderPosX,colliderPosY };
	
	myCollider = std::make_shared<Collider>(colliderPosition, width/2.f, height/2.f);

}

CollapsingTile::~CollapsingTile()
{
	myCollider->RemoveFromManager();
}

void CollapsingTile::InitAnimation()
{
	myAnimationClip = std::make_shared<AnimationClip>("Sprites/Tilesets/breakableTileSet_spriteSheets/Tile_06_SpriteSheet.dds", 0, 0);
	myAnimationClip->Init({ 8,1 }, { 8,1 });
	myAnimationClip->GetRenderCommand().SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);
}


void CollapsingTile::Update(float aDeltaTime)
{

	myAnimationClip->UpdateAnimation(myAnimationClip->GetRenderCommand().GetPosition());

	if (myShouldBeRendered == true)
	{
		if (CollisionManager::GetInstance().GetPlayerCollider() != nullptr)
		{
			if (CollisionManager::GetInstance().CheckCollision(myCollider.get(), CollisionManager::GetInstance().GetPlayerCollider()) && myHasBeenHitByPlayer == false)
			{
				myHasBeenHitByPlayer = true;
				myAnimationClip->PlayAnimOnce(0.3f);
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
	}
}



std::vector<std::shared_ptr<Collider>> CollapsingTile::GetAllColliders()
{
	std::vector<std::shared_ptr<Collider>> returnVector;
	returnVector.push_back(myCollider);
	return returnVector;
}
