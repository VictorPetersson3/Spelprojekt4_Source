#include "stdafx.h"
#include "Saw.h"
#include "Camera.h"


Saw::Saw(Vector2 aStartPoint)
{
	myPosition = aStartPoint;
	myCollider = Collider(myRadius, myPosition);
	mySprite = Tga2D::CSprite("");
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
		if (myNextPointIndex > myTravelPoints.size() -1 || myNextPointIndex < 0)
		{
			myDirection *= -1;
		}
		myNextPointIndex += myDirection;
	}
	myPosition += (myPosition - myTravelPoints[myNextPointIndex]).GetNormalized() * aDeltatime * mySpeed;
	myCollider.UpdateCollider(myPosition);
	mySprite.SetPosition({ myPosition.x, myPosition.y });
}

void Saw::Render(const std::shared_ptr<Camera> aCamera)
{
	aCamera.get()->RenderSprite(mySprite);
}


