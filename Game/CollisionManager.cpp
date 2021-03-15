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
	if (myPlayerCollider == nullptr)
	{
		for (int i = 0; i < myColliders.size(); i++)
		{
			if (myColliders[i]->GetTag() == EColliderTag::Player)
			{
				myPlayerCollider = myColliders[i];
				myColliders.erase(myColliders.begin() + i);
				break;
			}
		}
	}
	else
	{
		myPlayerCollider->Update();
		for (auto& collider : myColliders)
		{
			if ((collider->GetPosition() - myPlayerCollider->GetPosition()).Length() < myCollisionDetection)
			{
				if (myPlayerCollider != collider && CheckCollision(myPlayerCollider, collider))
				{
					myPlayerCollider->SetCollidedWith(collider);
					myPlayerCollider->HasCollided() = true;
				}
			}
		}
	}
}


bool CollisionManager::CheckCollision(Collider* aCollider, Collider* anOtherCollider)
{
	if (aCollider->GetType() == ECollider::None || anOtherCollider->GetType() == ECollider::None) return false;
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::Circle) return CircleCircle(aCollider, anOtherCollider);
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::AABB) return CircleAABB(aCollider, anOtherCollider);
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::Circle) return CircleAABB(anOtherCollider, aCollider);
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::AABB) return AABBAABB(aCollider, anOtherCollider);
}

void CollisionManager::PointOfIntersection(Collider* aCollider, Collider* anOtherCollider, CommonUtilities::Vector2f& aVariable)
{
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::Circle)
	{
		aVariable =  aCollider->GetPosition() + CommonUtilities::Vector2f::Distance(aCollider->GetPosition(), anOtherCollider->GetPosition()) * 0.5f;
	}
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::AABB)
	{
		CommonUtilities::Vector2f circlePos = aCollider->GetPosition();
		float radius = aCollider->GetRadius();
		CommonUtilities::Vector2f LL = anOtherCollider->GetAABB().myLowerLeft;
		CommonUtilities::Vector2f UR = anOtherCollider->GetAABB().myUpperRight;

		/// om center är i aabbn
		if (circlePos.x > LL.x && circlePos.x < UR.x && circlePos.y < LL.y && circlePos.y > UR.y)
		{
			auto delta = (circlePos - anOtherCollider->GetPosition()).GetNormalized();
			aVariable =  anOtherCollider->GetPosition() + delta * CommonUtilities::Vector2f((UR.x - LL.x) * 0.5f, (LL.y - UR.y) * 0.5f);
		}

		/// annars
		if (aCollider->GetPosition().x + aCollider->GetRadius() <= anOtherCollider->GetAABB().myLowerLeft.x) aVariable =  { anOtherCollider->GetPosition().x - anOtherCollider->GetAABB().mySize.x * 0.5f, aCollider->GetPosition().y };
		if (aCollider->GetPosition().x - aCollider->GetRadius() >= anOtherCollider->GetAABB().myUpperRight.x) aVariable =  { anOtherCollider->GetPosition().x + anOtherCollider->GetAABB().mySize.x * 0.5f, aCollider->GetPosition().y };
		if (aCollider->GetPosition().y + aCollider->GetRadius() <= anOtherCollider->GetAABB().myUpperRight.y) aVariable =  { aCollider->GetPosition().x, anOtherCollider->GetPosition().y - anOtherCollider->GetAABB().mySize.y * 0.5f };
		if (aCollider->GetPosition().y - aCollider->GetRadius() >= anOtherCollider->GetAABB().myLowerLeft.y) aVariable =  { aCollider->GetPosition().x, anOtherCollider->GetPosition().y + anOtherCollider->GetAABB().mySize.y * 0.5f };

		/// om center är mer/mindre än båda x o y
		if (circlePos.x < LL.x && circlePos.y < UR.y) aVariable =  { LL.x, UR.y };
		if (circlePos.x < LL.x && circlePos.y > LL.y) aVariable =  { LL.x, LL.y };
		if (circlePos.x > UR.x && circlePos.y < UR.y) aVariable =  { UR.x, UR.y };
		if (circlePos.x > UR.x && circlePos.y > LL.y) aVariable =  { UR.x, LL.y };
	}
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::Circle)
	{
		CommonUtilities::Vector2f circlePos = anOtherCollider->GetPosition();
		float radius = anOtherCollider->GetRadius();
		CommonUtilities::Vector2f LL = aCollider->GetAABB().myLowerLeft;
		CommonUtilities::Vector2f UR = aCollider->GetAABB().myUpperRight;

		/// om center är i aabbn
		if (circlePos.x > LL.x && circlePos.x < UR.x && circlePos.y < LL.y && circlePos.y > UR.y)
		{
			auto delta = (circlePos - aCollider->GetPosition()).GetNormalized();
			aVariable =  aCollider->GetPosition() + delta * CommonUtilities::Vector2f((UR.x - LL.x) * 0.5f, (LL.y - UR.y) * 0.5f);
		}


		/// annars
		if (anOtherCollider->GetPosition().x + anOtherCollider->GetRadius() <= aCollider->GetAABB().myLowerLeft.x) aVariable =  { anOtherCollider->GetPosition().x + anOtherCollider->GetRadius(), anOtherCollider->GetPosition().y };
		if (anOtherCollider->GetPosition().x - anOtherCollider->GetRadius() >= aCollider->GetAABB().myUpperRight.x) aVariable =  { anOtherCollider->GetPosition().x - anOtherCollider->GetRadius(), anOtherCollider->GetPosition().y };
		if (anOtherCollider->GetPosition().y + anOtherCollider->GetRadius() <= aCollider->GetAABB().myUpperRight.y) aVariable =  { anOtherCollider->GetPosition().x, anOtherCollider->GetPosition().y + anOtherCollider->GetRadius() };
		if (anOtherCollider->GetPosition().y - anOtherCollider->GetRadius() >= aCollider->GetAABB().myLowerLeft.y) aVariable =  { anOtherCollider->GetPosition().x, anOtherCollider->GetPosition().y - anOtherCollider->GetRadius() };
		/// om center är mer/mindre än båda x o y
		if (circlePos.x < LL.x && circlePos.y < UR.y) aVariable =  { LL.x, UR.y };
		if (circlePos.x < LL.x && circlePos.y > LL.y) aVariable =  { LL.x, LL.y };
		if (circlePos.x > UR.x && circlePos.y < UR.y) aVariable =  { UR.x, UR.y };
		if (circlePos.x > UR.x && circlePos.y > LL.y) aVariable =  { UR.x, LL.y };
	}
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::AABB)
	{
		///
		/// Lägger till kod här senare om det skulle behövas <3
		/// 
	}
}

CommonUtilities::Vector2f CollisionManager::CollisonNormal(Collider* aCollider, Collider* anOtherCollider)
{
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::Circle) return (aCollider->GetPosition() - anOtherCollider->GetPosition()).GetNormalized();
	if (aCollider->GetType() == ECollider::Circle && anOtherCollider->GetType() == ECollider::AABB)
	{
		CommonUtilities::Vector2f circlePos = aCollider->GetPosition();
		float radius = aCollider->GetRadius();
		CommonUtilities::Vector2f LL = anOtherCollider->GetAABB().myLowerLeft;
		CommonUtilities::Vector2f UR = anOtherCollider->GetAABB().myUpperRight;

		if (circlePos.x > LL.x && circlePos.x < UR.x && circlePos.y < LL.y && circlePos.y > UR.y)
		{
			auto delta = (circlePos - aCollider->GetPosition()).GetNormalized();
			circlePos = aCollider->GetPosition() + delta * CommonUtilities::Vector2f((UR.x - LL.x) * 0.5f, (LL.y - UR.y) * 0.5f);
		}

		if (circlePos.y < UR.y) return{ 0, -1 };
		if (circlePos.y > LL.y) return{ 0, 1 };
		if (circlePos.x < LL.x) return{ -1, 0 };
		if (circlePos.x > UR.x) return{ 1, 0 };
	}
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::Circle)
	{
		CommonUtilities::Vector2f circlePos = anOtherCollider->GetPosition();
		float radius = anOtherCollider->GetRadius();
		CommonUtilities::Vector2f LL = aCollider->GetAABB().myLowerLeft;
		CommonUtilities::Vector2f UR = aCollider->GetAABB().myUpperRight;

		if (circlePos.x > LL.x && circlePos.x < UR.x && circlePos.y < LL.y && circlePos.y > UR.y)
		{
			auto delta = (circlePos - aCollider->GetPosition()).GetNormalized();
			circlePos = aCollider->GetPosition() + delta * CommonUtilities::Vector2f((UR.x - LL.x) * 0.5f, (LL.y - UR.y) * 0.5f);
		}
		if (circlePos.y < UR.y) return{ 0, -1 };
		if (circlePos.y > LL.y) return{ 0, 1 };
		if (circlePos.x < LL.x) return{ -1, 0 };
		if (circlePos.x > UR.x) return{ 1, 0 };
	}
	if (aCollider->GetType() == ECollider::AABB && anOtherCollider->GetType() == ECollider::AABB)
	{
		//meh pallar inte fixa den här delen idag ;D
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