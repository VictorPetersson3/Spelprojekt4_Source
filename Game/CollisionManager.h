#pragma once

class Collider;

class CollisionManager
{
public:
	static void Init();
	static void Destroy();
	static bool IsReady();
	static CollisionManager& GetInstance();
	bool CheckCollision(const Collider& aCollider, const Collider& anOtherCollider);

private:
	bool AABBAABB(const Collider& aCollider, const Collider& anOtherCollider);
	bool CircleCircle(const Collider& aCollider, const Collider& anOtherCollider);
	bool CircleAABB(const Collider& aCollider, const Collider& anOtherCollider);

	//bool LineVolumeCircle();
	//bool LineVolumeLineVolume();
	//bool LineVolumeAABB();

	CollisionManager() = default;
	static CollisionManager* myInstance;
};

