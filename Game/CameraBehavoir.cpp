#include "stdafx.h"
#include "CameraBehavoir.h"
#include "Camera.h"
#include "Player.h"
#include <iostream>
void CameraBehavoir::Init(std::shared_ptr<Camera> aCamera, std::shared_ptr<Player> aPlayer)
{
	myCameraToMove = aCamera;
	myPlayerToFollow = aPlayer;

	myPosition = CommonUtilities::Vector2f(.5f, .5f);
}

void CameraBehavoir::Update(const float aDt)
{
	CenterCamera();
	
	myPosition += myFrameVelocity * aDt;
	myPosition.Clamp({ myMinBoarderX, myMinBoarderY, }, { myMaxBoarderX, myMaxBoarderY });
	myCameraToMove->SetPosition(myPosition - CommonUtilities::Vector2f(.5f, .5f));
	myFrameVelocity = CommonUtilities::Vector2f::Zero();
}

void CameraBehavoir::AddForce(const CommonUtilities::Vector2f aForceToAdd)
{
	myFrameVelocity += aForceToAdd;
}

void CameraBehavoir::CenterCamera()
{
	const CommonUtilities::Vector2f playerPos = myPlayerToFollow->GetPosition();

	if (playerPos != CommonUtilities::Vector2f::Zero())
	{
		const CommonUtilities::Vector2f dir = playerPos - myPosition;
		AddForce({ (dir.x * myMoveX) * myAcceleration, 0 });
		AddForce({ 0 , (dir.y * myMoveY) * myAcceleration });
	}
}

float CameraBehavoir::GetPlayerDistance() const
{
	return CommonUtilities::Vector2f::Distance(myPosition, myPlayerToFollow->GetPosition() + myPlayerToFollow->GetCurrentVelocity());
}

CommonUtilities::Vector2f CameraBehavoir::GetPlayerNextFramePos() const
{
	return myPlayerToFollow->GetPosition() + myPlayerToFollow->GetCurrentVelocity();
}


