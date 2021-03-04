#include "stdafx.h"
#include "Collider.h"

Collider::Collider()
{
}

/// <summary>
/// Constructor for a circle collider.
/// </summary>
/// <param name="aRadius  :  The radius of the collider"></param>
/// <param name="aPosition  :  The coordinates of the center of the collider"></param>
Collider::Collider(float aRadius, CommonUtilities::Vector2f aPosition)
{
	myType = ECollider::Circle;
	myRadius = aRadius;
	myPosition = aPosition;
}

/// <summary>
/// Constructor for an AABB collider.
/// </summary>
/// <param name="aPosition  :  The coordinates of the center of the AABB"></param>
/// <param name="aWidth  :  The width of the AABB"></param>
/// <param name="aHeight  :  The height of the AABB"></param>
Collider::Collider(CommonUtilities::Vector2f aPosition, float aWidth, float aHeight)
{
	myType = ECollider::AABB;
	myAABB.myLowerLeft = { aPosition.x - aWidth * 0.5f, aPosition.y + aHeight * 0.5f };
	myAABB.myUpperRight = { aPosition.x + aWidth * 0.5f, aPosition.y - aHeight * 0.5f }; 
	myAABB.mySize = { aWidth, aHeight };
	myPosition = aPosition;
}

void Collider::UpdateCollider(CommonUtilities::Vector2f anUpdatedPosition)
{
	myPosition = anUpdatedPosition;
}

const void Collider::Draw() const
{
	switch (myType)
	{
	case ECollider::Circle:
		Tga2D::CDebugDrawer::DrawCircle({ myPosition.x, myPosition.y }, myRadius, { 0, 1, 1, 1 });
		break;
	case ECollider::AABB:
		Tga2D::CDebugDrawer::DrawLine({ myAABB.myLowerLeft.x, myAABB.myLowerLeft.y }, {myAABB.myLowerLeft.x, myAABB.myUpperRight.y}, {1, 0.5, 0, 1});
		Tga2D::CDebugDrawer::DrawLine({ myAABB.myLowerLeft.x, myAABB.myLowerLeft.y }, {myAABB.myUpperRight.x, myAABB.myLowerLeft.y}, {1, 0.5, 0, 1});
		Tga2D::CDebugDrawer::DrawLine({ myAABB.myUpperRight.x, myAABB.myUpperRight.y }, {myAABB.myLowerLeft.x, myAABB.myUpperRight.y}, {1, 0.5, 0, 1});
		Tga2D::CDebugDrawer::DrawLine({ myAABB.myUpperRight.x, myAABB.myUpperRight.y }, {myAABB.myUpperRight.x, myAABB.myLowerLeft.y}, {1, 0.5, 0, 1});
		break;
	}
}

/// <summary>
/// Allows you to change the size of the collider.
/// </summary>
/// <param name="aNewRadius  :  The new collider radius"></param>
void Collider::SetRadius(float aNewRadius)
{
	myRadius = aNewRadius;
}

/// <summary>
/// Practically a run-time copy constructor for an AABB.
/// Does not work for a circle collider.
/// </summary>
/// <param name="anAABB  :  A new AABB with different values"></param>
void Collider::SetAABB(AABB anAABB)
{
	if (myType == ECollider::AABB) myAABB = anAABB;
}

void Collider::SetLowerLeft(CommonUtilities::Vector2f aPoint)
{
	myAABB.myLowerLeft = aPoint;
}

void Collider::SetUpperRight(CommonUtilities::Vector2f aPoint)
{
	myAABB.myUpperRight = aPoint;
}

const float& Collider::GetRadius() const
{
	return myRadius;
}

const AABB& Collider::GetAABB() const
{
	return myAABB;
}

const CommonUtilities::Vector2f& Collider::GetSize() const
{
	return myAABB.mySize;
}

const CommonUtilities::Vector2f& Collider::GetPosition() const
{
	return myPosition;
}

const ECollider& Collider::GetType() const
{
	return myType;
}
