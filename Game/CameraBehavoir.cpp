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

	std::cout << myPosition.x << ", " << myPosition.y << std::endl;
	
	myPosition += myFrameVelocity * aDt;
	myPosition.Clamp({ 0.25f,0.25f, }, { 0.75f, 0.75f });
	myCameraToMove->SetPosition(myPosition - CommonUtilities::Vector2f(.5f, .5f));
	myFrameVelocity = CommonUtilities::Vector2f::Zero();

}

void CameraBehavoir::AddForce(CommonUtilities::Vector2f aForceToAdd)
{
	myFrameVelocity += aForceToAdd;
}

void CameraBehavoir::CenterCamera()
{
	CommonUtilities::Vector2f playerPos = myPlayerToFollow->GetPosition();

	if (playerPos != CommonUtilities::Vector2f::Zero())
	{
		std::cout << myPlayerToFollow->GetPosition().x << ", " << myPlayerToFollow->GetPosition().y << std::endl;
		CommonUtilities::Vector2f dir = playerPos - myPosition;
		AddForce((dir * myMoveX) * myAcceleration);
		
		
		
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


