#include "stdafx.h"
#include "Bullet.h"
#include "RenderCommand.h"

Bullet::Bullet()
{
	myIsActive = false;
	myCollider = Collider(mySize / 2, myPosition);
	myCollider.SetTag(EColliderTag::KillZone);
	myRenderCommand = std::make_unique<RenderCommand>("Sprites/TempBullet.dds", 1);
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
		myCollider.UpdateCollider(myPosition);
		myRenderCommand->Update(myPosition);
	}
}

void Bullet::Render()
{
	if (myIsActive)
	{
		myRenderCommand->Render();
	}
}
