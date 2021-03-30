#include "stdafx.h"
#include "CameraBehavoir.h"
#include "Camera.h"
void CameraBehavoir::Init(std::shared_ptr<Camera> aCamera, std::shared_ptr<Player> aPlayer)
{
	myMovementFunctions[0] = &CameraBehavoir::Static;
	myMovementFunctions[1] = &CameraBehavoir::MoveX;
	myMovementFunctions[2] = &CameraBehavoir::MoveY;

}

void CameraBehavoir::Update(const float aDt)
{	
	const int moveX = (myMoveX * (!myStatic));
	const int moveY = ((myMoveY * 2) * (!myStatic));

	(this->*myMovementFunctions[moveX])(aDt);
	(this->*myMovementFunctions[moveY])(aDt);
	
	myPosition += myFrameVelocity * aDt;
	myCameraToMove->SetPosition(myPosition);
}

void CameraBehavoir::MoveY(const float aDt)
{	

}

void CameraBehavoir::MoveX(const float aDt)
{

}

void CameraBehavoir::Static(const float aDt)
{

}
