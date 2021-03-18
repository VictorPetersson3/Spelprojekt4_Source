#pragma once
#include "CommonUtilities/Vector2.hpp"

class Collider;

class CollisionManager
{
	friend Collider;
public:
	static void Init();
	static void Destroy();
	static bool IsReady();
	static CollisionManager& GetInstance();
	bool CheckCollision(Collider* aCollider, Collider* anOtherCollider);
	CommonUtilities::Vector2f AABBOverlap(Collider* aCollider, Collider* anOtherCollider);
	CommonUtilities::Vector2f CollisionNormal(Collider* aCollider, Collider* anOtherCollider);
	void Clear();

	void Update();
private:
	
	void AddCollider(Collider* aCollider);
	void RemoveCollider(Collider* aCollider);
	bool AABBAABB(Collider* aCollider, Collider* anOtherCollider);
	bool CircleCircle(Collider* aCollider, Collider* anOtherCollider);
	bool CircleAABB(Collider* aCollider, Collider* anOtherCollider);

	std::vector<Collider*> myColliders;
	float myCollisionDetection = 0.3f;

	Collider* myPlayerCollider;

	CollisionManager() = default;
	static CollisionManager* myInstance;
};

