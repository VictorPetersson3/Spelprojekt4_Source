#include "stdafx.h"
#include "CollisionManager.h"
#include "Collider.h"
#include <assert.h>

CollisionManager* CollisionManager::myInstance = nullptr;

void CollisionManager::Destroy()
{
	assert(myInstance != nullptr && "Collision Manager have already been destroyed");
	delete myInstance;
	myInstance = nullptr;
}
void CollisionManager::Init()
{
	assert(myInstance == nullptr && "Collision Manager have already been Created");
	myInstance = new CollisionManager();
}
bool CollisionManager::IsReady()
{
	return myInstance != nullptr;
}

void CollisionManager::Update()
{
	for (auto& collider : myColliders)
	{
		if (collider->GetPosition().x < 1 && collider->GetPosition().x > 0 && collider->GetPosition().y < 1 && collider->GetPosition().y > 0)
		{
			for (auto& anotherCollider : myColliders)
			{
				if (CheckCollision(anotherCollider, collider))
				{
					collider->SetCollidedWith(anotherCollider);
					anotherCollider->SetCollidedWith(collider);
				}
			}
		collider->Update();
		}
	}
}

bool CollisionManager::CheckCollision(Collider* aCollider, Collider* anOtherCollider)
{
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::Circle) return CircleCircle(aCollider, anOtherCollider);
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::AABB) return CircleAABB(aCollider, anOtherCollider);
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::Circle) return CircleAABB(anOtherCollider, aCollider);
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::AABB) return AABBAABB(aCollider, anOtherCollider);
}

CommonUtilities::Vector2f CollisionManager::PointOfIntersection(Collider* aCollider, Collider* anOtherCollider)
{
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::Circle)
	{
		return aCollider->GetPosition() + CommonUtilities::Vector2f::Distance(aCollider->GetPosition(), anOtherCollider->GetPosition()) * 0.5f;
	}
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::AABB)
	{
		if (aCollider->GetPosition().x + aCollider->GetRadius() <= anOtherCollider->GetAABB().myLowerLeft.x) return { aCollider->GetPosition().x + aCollider->GetRadius(), aCollider->GetPosition().y };
		if (aCollider->GetPosition().x - aCollider->GetRadius() >= anOtherCollider->GetAABB().myUpperRight.x) return { aCollider->GetPosition().x - aCollider->GetRadius(), aCollider->GetPosition().y };
		if (aCollider->GetPosition().y + aCollider->GetRadius() <= anOtherCollider->GetAABB().myUpperRight.y) return { aCollider->GetPosition().x, aCollider->GetPosition().y + aCollider->GetRadius() };
		if (aCollider->GetPosition().y - aCollider->GetRadius() >= anOtherCollider->GetAABB().myLowerLeft.y) return { aCollider->GetPosition().x, aCollider->GetPosition().y - aCollider->GetRadius() };
	}
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::Circle)
	{
		if (anOtherCollider->GetPosition().x + anOtherCollider->GetRadius() <= aCollider->GetAABB().myLowerLeft.x) return { anOtherCollider->GetPosition().x + anOtherCollider->GetRadius(), anOtherCollider->GetPosition().y };
		if (anOtherCollider->GetPosition().x - anOtherCollider->GetRadius() >= aCollider->GetAABB().myUpperRight.x) return { anOtherCollider->GetPosition().x - anOtherCollider->GetRadius(), anOtherCollider->GetPosition().y };
		if (anOtherCollider->GetPosition().y + anOtherCollider->GetRadius() <= aCollider->GetAABB().myUpperRight.y) return { anOtherCollider->GetPosition().x, anOtherCollider->GetPosition().y + anOtherCollider->GetRadius() };
		if (anOtherCollider->GetPosition().y - anOtherCollider->GetRadius() >= aCollider->GetAABB().myLowerLeft.y) return { anOtherCollider->GetPosition().x, anOtherCollider->GetPosition().y - anOtherCollider->GetRadius() };
	}
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::AABB)
	{
		///
		// H�r saknas massa kod som jag inte orkat l�gga in �n o__o liksom kolla ovanf�r, sjukt tedious
		///
	}
	return { 0, 0 };
}

CommonUtilities::Vector2f CollisionManager::CollisonNormal(Collider* aCollider, Collider* anOtherCollider)
{
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::Circle) return (aCollider->GetPosition() - anOtherCollider->GetPosition()).GetNormalized();
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::AABB)
	{
		if (aCollider->GetPosition().y < anOtherCollider->GetAABB().myUpperRight.y) return{ 0, -1 };
		if (aCollider->GetPosition().y > anOtherCollider->GetAABB().myLowerLeft.y) return{ 0, 1 };
		if (aCollider->GetPosition().x < anOtherCollider->GetAABB().myLowerLeft.x) return{ -1, 0 };
		if (aCollider->GetPosition().x > anOtherCollider->GetAABB().myUpperRight.x) return{ 1, 0 };
	}
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::Circle)
	{
		if (anOtherCollider->GetPosition().y < aCollider->GetAABB().myUpperRight.y) return{ 0, 1 };
		if (anOtherCollider->GetPosition().y > aCollider->GetAABB().myLowerLeft.y) return{ 0, -1 };
		if (anOtherCollider->GetPosition().x < aCollider->GetAABB().myLowerLeft.x) return{ 1, 0 };
		if (anOtherCollider->GetPosition().x > aCollider->GetAABB().myUpperRight.x) return{ -1, 0 };
	}
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::AABB)
	{
		//meh pallar inte fixa den h�r delen idag ;D
	}
	return { 0, 0 };
}

void CollisionManager::AddCollider(Collider* aCollider)
{
	myColliders.emplace_back(aCollider);
}


bool CollisionManager::AABBAABB(Collider* aCollider, Collider* anOtherCollider)
{
	CommonUtilities::Vector2f pos0 = aCollider->GetPosition();
	CommonUtilities::Vector2f size0 = aCollider->GetPosition();
	CommonUtilities::Vector2f pos1 = anOtherCollider->GetPosition();
	CommonUtilities::Vector2f size1 = anOtherCollider->GetPosition();
	return (
		pos0.x + size0.x / 2 >= pos1.x - size1.x / 2 &&
		pos0.x - size0.x / 2 <= pos1.x + size1.x / 2 &&
		pos0.y + size0.y / 2 >= pos1.y - size1.y / 2 &&
		pos0.y - size0.y / 2 <= pos1.y + size1.y / 2
		);
}
bool CollisionManager::CircleCircle(Collider* aCollider, Collider* anOtherCollider)
{
	return aCollider->GetRadius() + anOtherCollider->GetRadius() <= CommonUtilities::Vector2f::Distance(aCollider->GetPosition(), anOtherCollider->GetPosition());
}
bool CollisionManager::CircleAABB(Collider* aCollider, Collider* anOtherCollider)
{
	CommonUtilities::Vector2f pos0 = anOtherCollider->GetPosition();
	CommonUtilities::Vector2f pos1 = aCollider->GetPosition();
	CommonUtilities::Vector2f size = anOtherCollider->GetSize();
	float radius = aCollider->GetRadius();
	return (
		pos0.x + size.x / 2 >= pos1.x - radius &&
		pos0.x - size.x / 2 <= pos1.x + radius &&
		pos0.y + size.y / 2 >= pos1.y - radius &&
		pos0.y - size.y / 2 <= pos1.y + radius
		);
}

CollisionManager& CollisionManager::GetInstance()
{
	assert(myInstance != nullptr && "Collision Manager is Nullptr");
	return *myInstance;
}