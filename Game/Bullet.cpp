#include "stdafx.h"
#include "Bullet.h"
#include "RenderCommand.h"
#include "Camera.h"

Bullet::Bullet()
{
	myIsActive = false;
	myRenderCommand = new RenderCommand("Sprites/TempSaw.dds", 1);
	myPosition = { 0,0 };
	myDirection = { 0,0 };
	myCollider = std::make_shared<Collider>(mySize / 2, myPosition);
	myCollider->SetTag(EColliderTag::KillZone);
}

void Bullet::Call(Vector2 aPosition, Vector2 aDirection)
{
	myIsActive = true;
	myRemainingLifetime = myMaxLifetime;
	myPosition = aPosition;
	myDirection = aDirection;
}

void Bullet::Return()
{
	myIsActive = false;
}

bool Bullet::GetActive()
{
	return myIsActive;
}

void Bullet::Update(float aDeltaTime)
{
	if (myIsActive)
	{
		myPosition = myPosition + (myDirection.GetNormalized()) * mySpeed;
		myCollider->UpdateCollider(myPosition);
		myRenderCommand->Update(myPosition);
		myRemainingLifetime -= aDeltaTime;

		if (myRemainingLifetime <= 0)
		{
			Return();
		}
	}
}

void Bullet::Render(std::shared_ptr<Camera> aCamera)
{
	if (myIsActive)
	{
		aCamera->RenderSprite(*myRenderCommand);
	}
}
