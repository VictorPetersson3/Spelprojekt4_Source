#include "stdafx.h"
#include "ShooterBulletManager.h"

void ShooterBulletManager::Update(float aDeltaTime)
{
	for (int i = 0; i < 50; i++)
	{
		if (myBullets[i].GetActive())
		{
			myBullets[i].Update(aDeltaTime);
		}
	}
}

void ShooterBulletManager::Render()
{
	for (int i = 0; i < 50; i++)
	{
		if (myBullets[i].GetActive())
		{
			myBullets[i].Render();
		}
	}
}

void ShooterBulletManager::CallBullet(Vector2 aPosition, Vector2 aDirection)
{
	for (int i = 0; i < 50; i++)
	{
		if (!myBullets[i].GetActive())
		{
			myBullets[i].Call(aPosition, aDirection);
			return;
		}
	}
}
