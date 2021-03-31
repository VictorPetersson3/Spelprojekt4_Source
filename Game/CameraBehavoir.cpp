#include "stdafx.h"
#include "CameraBehavoir.h"
#include "Camera.h"
#include "Player.h"
void CameraBehavoir::Init(std::shared_ptr<Camera> aCamera, std::shared_ptr<Player> aPlayer)
{
	myMovementFunctions[0] = &CameraBehavoir::Static;
	myMovementFunctions[1] = &CameraBehavoir::MoveX;
	myMovementFunctions[2] = &CameraBehavoir::MoveY;
	
	myCameraToMove = aCamera;
	myPlayerToFollow = aPlayer;

	myPosition = myCameraToMove->GetPosition();
}

void CameraBehavoir::Update(const float aDt)
{	
	const int moveX = (myMoveX * (!myStatic));
	const int moveY = ((myMoveY * 2) * (!myStatic));

	if (GetPlayerDistance() > myRangeToMove)
	{
		(this->*myMovementFunctions[moveX])(aDt);
		(this->*myMovementFunctions[moveY])(aDt);
	}
	else 
	{
		CenterCamera();
	}
	
	myPosition += myFrameVelocity * aDt;
	myCameraToMove->SetPosition(myPosition);

}

void CameraBehavoir::AddForce(CommonUtilities::Vector2f aForceToAdd)
{
	myFrameVelocity += aForceToAdd;
}

void CameraBehavoir::CenterCamera()
{
	CommonUtilities::Vector2f dir = myPlayerToFollow->GetPosition() - myPosition;
	AddForce({ dir * myAcceleration });
}

void CameraBehavoir::MoveY(const float aDt)
{	
	if (GetPlayerNextFramePos().y > myPosition.y)
	{
		// move up
		AddForce({ 0, -myAcceleration * myPlayerToFollow->GetCurrentVelocity().y});
		return;
	}
	// move down
	AddForce({ 0, myAcceleration * myPlayerToFollow->GetCurrentVelocity().y });
}

void CameraBehavoir::MoveX(const float aDt)
{
	if (GetPlayerNextFramePos().x > myPosition.x)
	{
		// move right
		AddForce({ myAcceleration * myPlayerToFollow->GetCurrentVelocity().x, 0 });
		return;
	}
	// move left
	AddForce({ -myAcceleration * myPlayerToFollow->GetCurrentVelocity().x, 0 });
}

void CameraBehavoir::Static(const float aDt)
{
	
}

float CameraBehavoir::GetPlayerDistance() const
{
	return CommonUtilities::Vector2f::Distance(myPosition, myPlayerToFollow->GetPosition() + myPlayerToFollow->GetCurrentVelocity());
}

CommonUtilities::Vector2f CameraBehavoir::GetPlayerNextFramePos() const
{
	return myPlayerToFollow->GetPosition() + myPlayerToFollow->GetCurrentVelocity();
}


