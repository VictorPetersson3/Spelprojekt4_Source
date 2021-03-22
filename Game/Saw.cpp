#include "stdafx.h"
#include "Saw.h"
#include "Camera.h"
#include "RenderCommand.h"


Saw::Saw(Vector2 aStartPoint)
{
	myPosition = aStartPoint;
	myCollider = Collider(myRadius, myPosition);
	myRenderCommand = std::make_shared<RenderCommand>("Sprites/tempSaw.dds", 0);
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
	myRenderCommand->Update(myPosition);
}

void Saw::Render(const std::shared_ptr<Camera> aCamera)
{
	myRenderCommand->Render();
}

const std::shared_ptr<RenderCommand> Saw::GetRenderCommand() const
{
	return myRenderCommand;
}


