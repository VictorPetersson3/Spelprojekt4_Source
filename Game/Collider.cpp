#include "stdafx.h"
#include "Collider.h"

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

float Collider::GetRadius()
{
	return myRadius;
}

AABB Collider::GetAABB()
{
	return myAABB;
}

CommonUtilities::Vector2f Collider::GetSize()
{
	return myAABB.mySize;
}
