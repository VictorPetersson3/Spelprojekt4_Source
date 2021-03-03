#pragma once
class CollisionManager
{
public:
	static void Init();
	static void Destroy();
	static bool IsReady();

	bool CheckCollision();
	bool AABBAABB();
	bool CircleCircle();
	bool CircleAABB();

	static CollisionManager& GetInstance();
	//bool LineVolumeCircle();
	//bool LineVolumeLineVolume();
	//bool LineVolumeAABB();

private:
	CollisionManager() = default;
	static CollisionManager* myInstance;
};

