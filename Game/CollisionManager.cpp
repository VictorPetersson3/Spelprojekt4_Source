#include "stdafx.h"
#include "CollisionManager.h"
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

bool CollisionManager::CheckCollision()
{
	return false;
}
bool CollisionManager::AABBAABB()
{
	return false;
}
bool CollisionManager::CircleCircle()
{
	return false;
}
bool CollisionManager::CircleAABB()
{
	return false;
}

CollisionManager& CollisionManager::GetInstance()
{
	assert(myInstance != nullptr && "Collision Manager is Nullptr");
	return *myInstance;
}