#include "stdafx.h"
#include "Shooter.h"
#include "ShooterBulletManager.h"
#include "CommonUtilities/Timer.h"
#include "RenderCommand.h"

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

void Shooter::SetManager(std::shared_ptr<ShooterBulletManager> aBulletManager)
{
	myBulletManager = aBulletManager;
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
}

void Shooter::Render(std::shared_ptr<Camera> aCamera)
{
	myRenderCommand->Render();
}

const void Shooter::Shoot() const
{
	myBulletManager->CallBullet(myPosition, myFireDirection);
}
