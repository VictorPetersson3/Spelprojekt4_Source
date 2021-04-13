#include "stdafx.h"
#include "Bullet.h"
#include "AnimationClip.h"
#include "Camera.h"

Bullet::Bullet()
{
	myIsActive = false;
	myAnimationClip = std::make_shared<AnimationClip>("Sprites/obstacles/obstacle_shot.dds", 0, 0);
	myAnimationClip->Init({ 4,1 }, { 2,1 });
	myAnimationClip->PlayAnimLoop();
	myPosition = { 50000,50000 };
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
	myAnimationClip->SetRotation(std::atan2(myDirection.Y, myDirection.X) + ((2 * PI) / 4) * 2);
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
		myAnimationClip->UpdateAnimation(myPosition);
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
		aCamera->RenderSprite(myAnimationClip->GetRenderCommand());

	}
}

std::shared_ptr<Collider> Bullet::GetCollider()
{
	return myCollider;
}
