#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Collider.h"
#include <iostream>
#include <CommonUtilities/Random.h>
void Boss::Init(const std::shared_ptr<Player> aPlayer) 
{
	myCollider = std::make_shared<Collider>(myPosition, 0.2f, 0.2f);
	myCollider->SetTag(EColliderTag::KillZone);

	myRenderCommand = std::make_shared<RenderCommand>("sprites/HästfanDDS.dds", 1, true);
	myRenderCommand->SetSizeRelativeToImage({ 3.f,3.f });
	myPlayerToAttack = aPlayer;
	myPosition = { 0.5f, 0.5f }; // start pos
	myPostionsToMoveTo.emplace_back(myPosition);
	myRenderCommand->SetSpritePosition(myPosition);

}

void Boss::Update(const float aDt)
{

	if (!myIsDead)
	{
		Move(aDt);		
		CheckCollisionWithPlayer();
		myPosition += myDirection * aDt;
		myDirection = CommonUtilities::Vector2f::Zero();
		myRenderCommand->SetSpritePosition(myPosition);
		myRenderCommand->Update(myPosition);
		myCollider->Update();
		myCollider->UpdateCollider(myPosition);
	}
}

void Boss::Render(Camera& aCamera)
{
	if (!myIsDead)
		aCamera.RenderSprite(*myRenderCommand);
}

void Boss::AddForce(const CommonUtilities::Vector2f aForce)
{
	myDirection += aForce;
}

void Boss::CheckCollisionWithPlayer()
{
	for (int i = 0; i < myCollider->GetCollidedWith().size(); i++)
	{
		if (myCollider->GetCollidedWith()[i]->GetTag() == EColliderTag::Player)
		{
			std::cout << "Kill the player\n";
		}
	}
}

void Boss::Move(const float aDt)
{
	PickNewPosition(aDt);
	const float dist = CommonUtilities::Vector2f::Distance(myPostionsToMoveTo[myPositionIndex], myPlayerToAttack->GetPosition());	
	if (dist > 0.01f)
	{
		const float maxSpeed = mySpeed * 2;
		CommonUtilities::Vector2f direction = myPostionsToMoveTo[myPositionIndex] - myPosition;
		AddForce((direction.Clamp(-maxSpeed, maxSpeed) * mySpeed));
	}
}

int Boss::PickPosition()
{
	int index = 0;
	float dist = 0, closestDist = 0;
	for (int i = 0; i < myPostionsToMoveTo.size(); ++i)
	{
		dist = CommonUtilities::Vector2f::Distance(myPostionsToMoveTo[i], myPlayerToAttack->GetPosition());	
		if (dist < closestDist || closestDist == 0)
		{
			closestDist = dist;
			index = i;
		}
	}	
	return index;
}

void Boss::PickNewPosition(const float aDt)
{
	if (myMoveTimer >= myMoveTime)
	{
		myPositionIndex = PickPosition();
		myMoveTimer = 0;
		myMoveTime = CommonUtilities::GetRandomFloat(2.f, 4.f);
		return;
	}
	myMoveTimer += aDt;
}
