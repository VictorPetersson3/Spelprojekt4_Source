#include "stdafx.h"
#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider(float aRadius, CommonUtilities::Vector2f aPosition)
{
	myType = ECollider::Circle;
	myRadius = aRadius;
	myPosition = aPosition;
	CollisionManager::GetInstance().AddCollider(this);
}


Collider::Collider(CommonUtilities::Vector2f aPosition, float aWidth, float aHeight)
{
	myType = ECollider::AABB;
	myAABB.myLowerLeft = { aPosition.x - aWidth * 0.5f, aPosition.y + aHeight * 0.5f };
	myAABB.myUpperRight = { aPosition.x + aWidth * 0.5f, aPosition.y - aHeight * 0.5f }; 
	myAABB.mySize = { aWidth, aHeight };
	myPosition = aPosition;
	CollisionManager::GetInstance().AddCollider(this);
}

void Collider::Update()
{
	myCollision.myNormal = CollisionManager::GetInstance().CollisonNormal(this, myCollidedWith);
	myCollision.myPointOfIntersection = CollisionManager::GetInstance().PointOfIntersection(this, myCollidedWith);
}

void Collider::UpdateCollider(CommonUtilities::Vector2f anUpdatedPosition)
{
	myPosition = anUpdatedPosition;
}

Collider* Collider::GetCollidedWith()
{
	return myCollidedWith;
}

const CommonUtilities::Vector2f Collider::GetCollisionNormal() const
{
	return myCollision.myNormal;
}

const CommonUtilities::Vector2f Collider::GetPointOfIntersection() const
{
	return myCollision.myPointOfIntersection;
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


void Collider::SetRadius(float aNewRadius)
{
	myRadius = aNewRadius;
}


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

void Collider::SetCollidedWith(Collider* aCollider)
{
	myCollidedWith = aCollider;
}

bool& Collider::HasCollided()
{
	return myHasCollided;
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
