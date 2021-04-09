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
	if (!myCollidedWith.empty())
	{
		myCollidedWith.clear();
		myHasCollided = false;
	}	
	else
	{
		myHasCollided = false;
	}
}

void Collider::UpdateCollider(CommonUtilities::Vector2f anUpdatedPosition)
{
	myPlatformSpeed = anUpdatedPosition - myPosition;
	myPosition = anUpdatedPosition;
}

const CommonUtilities::Vector2f& Collider::GetPlatformSpeed()
{
	return myPlatformSpeed;
}

std::vector<Collider*>& Collider::GetCollidedWith()
{
	return myCollidedWith;
}

const CommonUtilities::Vector2f Collider::GetCollisionNormal(const int anIndex)
{
	return CollisionManager::GetInstance().CollisionNormal(this, myCollidedWith[anIndex]);
}

const void Collider::Draw() const
{
#ifdef _DEBUG
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
#endif _DEBUG
}


void Collider::SetTag(EColliderTag aColliderTag)
{
	myTag = aColliderTag;
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
	myCollidedWith.emplace_back(aCollider);
}

void Collider::RemoveFromManager()
{
	CollisionManager::GetInstance().RemoveCollider(this);
}

void Collider::AddToManager()
{
	CollisionManager::GetInstance().AddCollider(this);
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

const EColliderTag& Collider::GetTag() const
{
	return myTag;
}
