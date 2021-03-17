#include "stdafx.h"
#include "Shooter.h"
#include "ShooterBulletManager.h"
#include "CommonUtilities/Timer.h"
#include "RenderCommand.h"

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
}

void Shooter::Render()
{
	myRenderCommand->Render();
}

const void Shooter::Shoot() const
{
	myBulletManager->CallBullet(myPosition, myFireDirection);
}
