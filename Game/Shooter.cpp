#include "stdafx.h"
#include "Shooter.h"
#include "CommonUtilities/Timer.h"
#include "RenderCommand.h"
#include "Camera.h"

void Shooter::Init(Vector2 aPosition, Shooter::EFireDirection aFireDirection)
{
	myPosition = aPosition;
	myRenderCommand = std::make_shared<RenderCommand>("Sprites/tempSaw.dds", 0);

	switch (aFireDirection)
	{
	case Shooter::EFireDirection::Up:
		myFireDirection = { 1,0 };
		break;
	case Shooter::EFireDirection::Down:
		myFireDirection = { -1,0 };
		break;
	case Shooter::EFireDirection::Right:
		myFireDirection = { 0,1 };
		break;
	case Shooter::EFireDirection::Left:
		myFireDirection = { 0,-1};
		break;
	default:
		break;
	}
}

std::shared_ptr<RenderCommand> Shooter::GetRenderCommand()
{
	return myRenderCommand;
}

void Shooter::Update(float aDeltaTime)
{
	if (myFireTimer <= 0)
	{
		Shoot();
		myFireTimer = myFireRate;
	}
	else
	{
		myFireTimer -= aDeltaTime;
	}

	myRenderCommand->Update(myPosition);

	for (int i = 0; i < 10; i++)
	{
		if (myBullets[i].GetActive())
		{
			myBullets[i].Update(aDeltaTime);
		}
	}
}

void Shooter::Render(std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(*myRenderCommand);	

	for (int i = 0; i < 10; i++)
	{
		if (myBullets[i].GetActive())
		{
			myBullets[i].Render(aCamera);
		}
	}
}

void Shooter::Shoot()
{
	/*for (int i = 0; i < 10; i++)
	{
		if (!myBullets[i].GetActive())
		{
			myBullets[i].Call(myPosition, myFireDirection);
		}
	}*/
}
