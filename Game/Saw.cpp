#include "stdafx.h"
#include "Saw.h"
#include "Camera.h"


Saw::Saw(Vector2 aStartPoint)
{
	myPosition = aStartPoint;
	myCollider = Collider(myRadius, myPosition);
	mySprite = Tga2D::CSprite("Sprites/tempSaw.dds");
	mySprite.SetPivot({ 0.5f, 0.5f });
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
		myDirection *= -1;
		myNextPointIndex += myDirection;
	}
	myPosition += (myTravelPoints[myNextPointIndex] - myPosition).GetNormalized() * aDeltatime * mySpeed;
	myCollider.UpdateCollider(myPosition);
	mySprite.SetPosition({ myPosition.x, myPosition.y });
}

void Saw::Render(const std::shared_ptr<Camera> aCamera)
{
	aCamera.get()->RenderSprite(mySprite);
}


