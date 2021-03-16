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
			if (myPlayerCollider != collider)
			{
				if ((collider->GetPosition() - myPlayerCollider->GetPosition()).Length() < myCollisionDetection)
				{
					if (CheckCollision(myPlayerCollider, collider))
					{
						myPlayerCollider->SetCollidedWith(collider);
						myPlayerCollider->HasCollided() = true;
					}
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
		CommonUtilities::Vector2f delta = anOtherCollider->GetPosition() - aCollider->GetPosition();
		if (aCollider->GetSize().x * 0.5f + anOtherCollider->GetSize().x * 0.5f - std::abs(anOtherCollider->GetPosition().x - aCollider->GetPosition().x) <
			aCollider->GetSize().y * 0.5f + anOtherCollider->GetSize().y * 0.5f - std::abs(anOtherCollider->GetPosition().y - aCollider->GetPosition().y))
		{
			if (delta.x < 0)
			{
				return { 1, 0 };
			}
			else return{ -1, 0 };
		}
		else
		{
			if (delta.y < 0)
			{
				return { 0, 1 };
			}
			else return{ 0, -1 };
		}
	}
	return { 0, 0 };
}

CommonUtilities::Vector2f CollisionManager::AABBOverlap(Collider* aCollider, Collider* anOtherCollider)
{
	CommonUtilities::Vector2f A1 = { aCollider->GetPosition().x - aCollider->GetSize().x * 0.5f, aCollider->GetPosition().y - aCollider->GetSize().y * 0.5f };
	CommonUtilities::Vector2f A2 = { aCollider->GetPosition().x + aCollider->GetSize().x * 0.5f, aCollider->GetPosition().y + aCollider->GetSize().y * 0.5f };

	CommonUtilities::Vector2f B1 = { anOtherCollider->GetPosition().x - anOtherCollider->GetSize().x * 0.5f, anOtherCollider->GetPosition().y - anOtherCollider->GetSize().y * 0.5f };
	CommonUtilities::Vector2f B2 = { anOtherCollider->GetPosition().x + anOtherCollider->GetSize().x * 0.5f, anOtherCollider->GetPosition().y + anOtherCollider->GetSize().y * 0.5f };

	CommonUtilities::Vector2f overlap =
	{
		std::fminf(A2.x, B2.x) - std::fmaxf(A1.x, B1.x),
		std::fminf(A2.y, B2.y) - std::fmaxf(A1.y, B1.y)
	};

	return overlap;
}

void CollisionManager::Clear()
{
	myColliders.clear();
}

void CollisionManager::AddCollider(Collider* aCollider)
{
	myColliders.emplace_back(aCollider);
}

bool CollisionManager::AABBAABB(Collider* aCollider, Collider* anOtherCollider)
{
	if (std::abs(aCollider->GetPosition().x - anOtherCollider->GetPosition().x) > aCollider->GetSize().x * 0.5f + anOtherCollider->GetSize().x * 0.5f) return false;
	if (std::abs(aCollider->GetPosition().y - anOtherCollider->GetPosition().y) > aCollider->GetSize().y * 0.5f + anOtherCollider->GetSize().y * 0.5f) return false;
	return true;
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