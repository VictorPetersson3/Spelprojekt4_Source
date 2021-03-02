#pragma once
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	bool AABBAABB();
	bool CircleCircle();
	bool CircleAABB();
	//bool LineVolumeCircle();
	//bool LineVolumeLineVolume();
	//bool LineVolumeAABB();

private:

};

