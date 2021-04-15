#include "stdafx.h"
#include "Shooter.h"
#include "CommonUtilities/Timer.h"
#include "AnimationClip.h"
#include "Camera.h"

void Shooter::Init(Vector2 aPosition, Shooter::EFireDirection aFireDirection, bool aFlipped)
{
	myPosition = aPosition;
	myAnimationClip = std::make_shared<AnimationClip>("Sprites/obstacles/obstacle_shooter.dds", 0, 0);
	myAnimationClip->Init({ 16,1 }, { 9,1 });
	myAnimationClip->ActivateLooping();
	myFireTimer = myFireRate;

	switch (aFireDirection)
	{
	case Shooter::EFireDirection::Up:
		myFireDirection = { 0,-1 };
		break;
	case Shooter::EFireDirection::Down:
		myFireDirection = { 0,1 };
		break;
	case Shooter::EFireDirection::Right:
		myFireDirection = { 1,0 };
		break;
	case Shooter::EFireDirection::Left:
		myFireDirection = { -1,0 };
		break;
	default:
		break;
	}

	myAnimationClip->SetRotation(std::atan2(myFireDirection.Y, myFireDirection.X) + ((2 * PI) / 4) * 2);

	if (aFlipped)
	{
		if (aFireDirection == Shooter::EFireDirection::Right || aFireDirection == Shooter::EFireDirection::Left)
		{
			myAnimationClip->SetScaleRelativeToFrame({ 1, -1 });
		}
		else
		{
			myAnimationClip->SetScaleRelativeToFrame({ -1, 1 });
		}
	}
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

	if (myFireTimer <= (0.08333f * 7) && !myAnimationClip->GetAnimIsPlaying())
	{
		myAnimationClip->PlayAnimOnce();
	}

	myAnimationClip->UpdateAnimation(myPosition);

	for (int i = 0; i < 10; i++)
	{
		if (myBullets[i].GetActive())
		{
			myBullets[i].Update(aDeltaTime);
		}
	}

	if (myAnimationClip->GetAnimIsDone())
	{
		myAnimationClip->SetFrame({ 1,1 });
	}
}

void Shooter::Render(std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(myAnimationClip->GetRenderCommand());

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
	for (int i = 0; i < 10; i++)
	{
		if (!myBullets[i].GetActive())
		{
			myBullets[i].Call(myPosition, myFireDirection);
			return;
		}
	}
}

void Shooter::SetFireRate(const float& aFireRate)
{
	myFireRate = aFireRate;
}

std::vector<std::shared_ptr<Collider>> Shooter::GetAllColliders()
{
	std::vector<std::shared_ptr<Collider>> returnVector;
	returnVector.push_back(myCollider);

	for (Bullet& b : myBullets)
	{
		returnVector.push_back(b.GetCollider());
	}


	return returnVector;
}
