#include "stdafx.h"
#include "Shooter.h"
#include "CommonUtilities/Timer.h"
#include "AnimationClip.h"
#include "Camera.h"

void Shooter::Init(Vector2 aPosition, Shooter::EFireDirection aFireDirection)
{
	myPosition = aPosition;
	myAnimationClip = std::make_shared<AnimationClip>("Sprites/obstacles/obstacle_shooter.dds", 0, 0);
	myAnimationClip->Init({ 16,1 }, { 9,1 });
	myAnimationClip->ActivateLooping();
	myFireTimer = myFireRate;

	switch (aFireDirection)
	{
	case Shooter::EFireDirection::Up:
		myFireDirection = { 0,1 };
		break;
	case Shooter::EFireDirection::Down:
		myFireDirection = { 0,-1 };
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
			break;
		}
	}
}
