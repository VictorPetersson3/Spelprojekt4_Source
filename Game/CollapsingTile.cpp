#include "stdafx.h"
#include "CollapsingTile.h"
#include "RenderCommand.h"
#include "Collider.h"
#include "Timer.h"
#include "CollisionManager.h"
#include <iostream>

CollapsingTile::CollapsingTile(CommonUtilities::Vector2f aPosition)
{
	float posX = aPosition.x / 1280.f;
	float posY = aPosition.y / 720.f;

	myRenderCommand = std::make_shared<RenderCommand>("Sprites/Tilesets/breakableTileSet_01.dds",1,CommonUtilities::Vector2(posX,posY));

	float startX = 0.f;
	float startY = 0.f;

	myRenderCommand->SetTextureRect(startX, startY, startX + 32.f / myRenderCommand->GetImageSize().x, startY + 32.f / myRenderCommand->GetImageSize().y);

	myRenderCommand->SetSizeRelativeToImage({ 1.f / (static_cast<float>(myRenderCommand->GetImageSize().x) / 32),1.f / (static_cast<float>(myRenderCommand->GetImageSize().y) / 32) });


	CommonUtilities::Vector2f colliderPosition = { posX,posY };

	float width = myRenderCommand->GetSize().x;
	float height = myRenderCommand->GetSize().y * (16.f / 9.f);

	myCollider = std::make_shared<Collider>(colliderPosition, width/2.f, height/2.f);

	std::cout << "ColliderPosition : " << colliderPosition.x << " x " << colliderPosition.y << std::endl;
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
			if (CollisionManager::GetInstance().CheckCollision(myCollider.get(), CollisionManager::GetInstance().GetPlayerCollider()))
			{
				myHasBeenHitByPlayer = true;
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
		myRenderCommand->Render();
		myCollider->Draw();
	}

}
