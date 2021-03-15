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

	void Update();
private:
	bool CheckCollision(Collider* aCollider, Collider* anOtherCollider);
	void PointOfIntersection(Collider* aCollider, Collider* anOtherCollider, CommonUtilities::Vector2f& aVariable);
	CommonUtilities::Vector2f CollisonNormal(Collider* aCollider, Collider* anOtherCollider);
	void AddCollider(Collider* aCollider);
	bool AABBAABB(Collider* aCollider, Collider* anOtherCollider);
	bool CircleCircle(Collider* aCollider, Collider* anOtherCollider);
	bool CircleAABB(Collider* aCollider, Collider* anOtherCollider);

	//bool LineVolumeCircle();
	//bool LineVolumeLineVolume();
	//bool LineVolumeAABB();

	std::vector<Collider*> myColliders;
	float myCollisionDetection = 0.3f;

	Collider* myPlayerCollider;

	CollisionManager() = default;
	static CollisionManager* myInstance;
};

