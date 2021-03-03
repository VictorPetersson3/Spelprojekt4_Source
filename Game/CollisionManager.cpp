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

bool CollisionManager::CheckCollision(const Collider& aCollider, const Collider& anOtherCollider)
{
	if (aCollider.GetType() == ECollider::Circle && anOtherCollider.GetType() == ECollider::Circle) return CircleCircle(aCollider, anOtherCollider);
	if (aCollider.GetType() == ECollider::Circle && anOtherCollider.GetType() == ECollider::AABB) return CircleAABB(aCollider, anOtherCollider);
	if (aCollider.GetType() == ECollider::AABB && anOtherCollider.GetType() == ECollider::Circle) return CircleAABB(anOtherCollider, aCollider);
	if (aCollider.GetType() == ECollider::AABB && anOtherCollider.GetType() == ECollider::AABB) return AABBAABB(aCollider, anOtherCollider);
}
bool CollisionManager::AABBAABB(const Collider& aCollider, const Collider& anOtherCollider)
{
	CommonUtilities::Vector2f pos0 = aCollider.GetPosition();
	CommonUtilities::Vector2f size0 = aCollider.GetPosition();
	CommonUtilities::Vector2f pos1 = anOtherCollider.GetPosition();
	CommonUtilities::Vector2f size1 = anOtherCollider.GetPosition();
	return (
		pos0.x + size0.x / 2 >= pos1.x - size1.x / 2 &&
		pos0.x - size0.x / 2 <= pos1.x + size1.x / 2 &&
		pos0.y + size0.y / 2 >= pos1.y - size1.y / 2 &&
		pos0.y - size0.y / 2 <= pos1.y + size1.y / 2
		);
}
bool CollisionManager::CircleCircle(const Collider& aCollider, const Collider& anOtherCollider)
{
	return aCollider.GetRadius() + anOtherCollider.GetRadius() <= CommonUtilities::Vector2f::Distance(aCollider.GetPosition(), anOtherCollider.GetPosition());
}
bool CollisionManager::CircleAABB(const Collider& aCollider, const Collider& anOtherCollider)
{
	CommonUtilities::Vector2f pos0 = anOtherCollider.GetPosition();
	CommonUtilities::Vector2f pos1 = aCollider.GetPosition();
	CommonUtilities::Vector2f size = anOtherCollider.GetSize();
	float radius = aCollider.GetRadius();
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