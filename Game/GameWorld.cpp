#include "stdafx.h"
#include "GameWorld.h"
#include "InputManager.h"
#include "Timer.h"
#include "CommonUtilities/Random.h"
#include "Camera.h"
#include "StateManager.h"
#include "LevelLoader.h"
#include "Player.h"
#include "XController.h"
#include "CollisionManager.h"
#include "Door.h"
#include "Key.h"
#include "CameraBehavoir.h"
#include <tga2d/sprite/sprite.h>
#include <CommonUtilities/Vector2.hpp>
#include <iostream>

CGameWorld::CGameWorld()
{
}

CGameWorld::~CGameWorld()
{
}

void CGameWorld::Init()
{
	myController = std::make_shared<XController>(1);
	CollisionManager::Init();
	StateManager::Init(myController.get());
}

void CGameWorld::Update(float /*aTimeDelta*/)
{
	StateManager::GetInstance().Update();
	CollisionManager::GetInstance().Update();
}

void CGameWorld::Render()
{
	StateManager::GetInstance().Render();
}