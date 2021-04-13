#include "stdafx.h"
#include "Saw.h"
#include "Camera.h"
#include "AnimationClip.h"
#include <math.h>

Saw::Saw(Vector2 aStartPoint, bool isFlipped)
{
	myPosition = aStartPoint;
	myAnimationClip = std::make_shared<AnimationClip>("Sprites/obstacles/obstacle_saw.dds", 0, 0);
	myAnimationClip->Init({ 4,1 }, { 2,1 });
	myAnimationClip->PlayAnimLoop();
	myTravelPoints.push_back(aStartPoint);

	if (isFlipped)
	{
		Flip();
	}
}

void Saw::AddPoint(Vector2 aPoint)
{
	if (myTravelPoints.size() == 1)
	{
		myAnimationClip = std::make_shared<AnimationClip>("Sprites/obstacles/obstacle_snail.dds", 0, 0);
		myAnimationClip->Init({ 8,1 }, { 5,1 });
		myAnimationClip->PlayAnimLoop();
		if (myFacingRight)
		{
			myAnimationClip->SetScaleRelativeToFrame({ -1, 1 });
		}
	}
	myAnimationClip->SetRotation(0);
	myDownVector = Vector2({ (myTravelPoints[0] - aPoint).myY, (myTravelPoints[0] - aPoint).myX });
	myTravelPoints.push_back(aPoint);
}

void Saw::Update(float aDeltatime)
{

	if (myPosition.Distance(myPosition, myTravelPoints[myNextPointIndex]) < aDeltatime * mySpeed)
	{
		myPosition = myTravelPoints[myNextPointIndex];
		myNextPointIndex += myDirection;

		if (myNextPointIndex > myTravelPoints.size() - 1 || myNextPointIndex < 0)
		{

			if (myRepeating)
			{
				myDirection *= -1;
				float floatDirection = myDirection;
				myNextPointIndex += myDirection * 2;
				Flip();
			}
			else
			{
				myNextPointIndex = 0;
			}
		}

		if (myFacingRight)
		{
			myDownVector = (myPosition - myTravelPoints[myNextPointIndex]) * 1;
		}
		else
		{
			myDownVector = (myPosition - myTravelPoints[myNextPointIndex]) * -1;
		}

		myAnimationClip->SetRotation(std::atan2(myDownVector.myY, myDownVector.myX) + ((2 * PI) / 4) * 2);
	}

	myPosition += (myTravelPoints[myNextPointIndex] - myPosition).GetNormalized() * aDeltatime * mySpeed;
	myCollider->UpdateCollider(myPosition);
	myAnimationClip->UpdateAnimation(myPosition);
}

void Saw::Render(const std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(myAnimationClip->GetRenderCommand());
}

void Saw::SetCollider(std::shared_ptr<Collider> aCollider)
{
	myCollider = aCollider;
}

void Saw::SetRepeating(bool aRepeating)
{
	myRepeating = aRepeating;
}
void Saw::Flip()
{
	if (myFacingRight)
	{
		myFacingRight = false;
		myAnimationClip->SetScaleRelativeToFrame({ 1, 1 });
	}
	else
	{
		myFacingRight = true;
		myAnimationClip->SetScaleRelativeToFrame({ -1, 1 });
	}
}


