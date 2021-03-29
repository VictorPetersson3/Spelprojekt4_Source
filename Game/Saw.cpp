#include "stdafx.h"
#include "Saw.h"
#include "Camera.h"
#include "AnimationClip.h"


Saw::Saw(Vector2 aStartPoint)
{
	myPosition = aStartPoint;
	myAnimationClip = std::make_shared<AnimationClip>("Sprites/obstacles/obstacle_snail.dds", 0, 0);
	myAnimationClip->Init({ 8,1 }, { 5,1 });
	myAnimationClip->PlayAnimLoop();
	myTravelPoints.push_back(aStartPoint);
}

void Saw::AddPoint(Vector2 aPoint)
{
	myTravelPoints.push_back(aPoint);
}

void Saw::Update(float aDeltatime)
{
	if (myPosition.Distance(myPosition, myTravelPoints[myNextPointIndex]) < EPSILON)
	{
		myNextPointIndex += myDirection;
	}
	if (myNextPointIndex > myTravelPoints.size() - 1|| myNextPointIndex < 0)
	{
		if (myRepeating)
		{
			myDirection *= -1;
			myNextPointIndex += myDirection;
		}
		else
		{
			myNextPointIndex = 0;
		}
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


