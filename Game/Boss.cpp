#include "stdafx.h"
#include "Boss.h"
#include "Player.h"
#include "RenderCommand.h"
#include "Camera.h"
#include <CommonUtilities/Random.h>
void Boss::Init(const std::shared_ptr<Player> aPlayer) 
{
	myPlayerToAttack = aPlayer;
	myPosition = { 0.5f, 0.5f };
	myPostionsToMoveTo.emplace_back(myPosition);
	myRenderCommand->SetSpritePosition(myPosition);
}

void Boss::Update(const float aDt)
{
	Move(aDt);
	myPosition += myDirection * aDt;
	myDirection = CommonUtilities::Vector2f::Zero();
	myRenderCommand->SetSpritePosition(myPosition);
}

void Boss::Render(const std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(*myRenderCommand);
}

void Boss::AddForce(const CommonUtilities::Vector2f aForce)
{
	myDirection += aForce;
}

void Boss::Move(const float aDt)
{
	PickNewPosition(aDt);
	const float dist = CommonUtilities::Vector2f::Distance(myPostionsToMoveTo[myPositionIndex], myPlayerToAttack->GetPosition());	
	if (dist > 0.01f)
	{
		const CommonUtilities::Vector2f direction = myPostionsToMoveTo[myPositionIndex] - myPosition;
		AddForce(direction);
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
		myMoveTime = CommonUtilities::GetRandomFloat(5.f, 7.f);
		return;
	}
	myMoveTimer += aDt;
}
