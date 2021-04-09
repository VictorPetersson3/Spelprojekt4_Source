#include "stdafx.h"
#include "MovingPlatform.h"
#include "Camera.h"
#include "AnimationClip.h"


MovingPlatform::MovingPlatform(Vector2 aStartPoint)
{
	myPosition = aStartPoint;
	myRenderCommand = std::make_shared<RenderCommand>("Sprites/Tilesets/tiles_Sheet_01.dds", 0, 0);
	myTravelPoints.push_back(aStartPoint);
}

void MovingPlatform::AddPoint(Vector2 aPoint)
{
	myTravelPoints.push_back(aPoint);
}

void MovingPlatform::Update(float aDeltatime)
{
	if (myPosition.Distance(myPosition, myTravelPoints[myNextPointIndex]) < aDeltatime * mySpeed)
	{
		myPosition = myTravelPoints[myNextPointIndex];
		myNextPointIndex += myDirection;
	}
	if (myNextPointIndex > myTravelPoints.size() - 1 || myNextPointIndex < 0)
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
	myRenderCommand->Update(myPosition);
}

void MovingPlatform::Render(const std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(*myRenderCommand);
}

void MovingPlatform::SetCollider(std::shared_ptr<Collider> aCollider)
{
	myCollider = aCollider;
}

void MovingPlatform::SetRepeating(bool aRepeating)
{
	myRepeating = aRepeating;
}

void MovingPlatform::SetSize(Vector2 aRenderSize, float aGridSize)
{
	CommonUtilities::Vector2f imageSize;
	imageSize.x = myRenderCommand->GetImageSize().x;
	imageSize.y = myRenderCommand->GetImageSize().y;

	myRenderCommand->SetTextureRect(0,0, 1 / (imageSize.X / aRenderSize.X), 1 / (imageSize.Y / aRenderSize.Y));
	myRenderCommand->SetSizeRelativeToImage({ 1/(imageSize.X / aRenderSize.X), 1/(imageSize.Y / aRenderSize.Y)});
}
