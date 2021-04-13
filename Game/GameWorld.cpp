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
	CollisionManager::Init();
	StateManager::Init();
	myPlayer = std::make_shared<Player>();
	 
	myCamera = std::make_unique<Camera>();
	myController = std::make_shared<XController>(1);
	//myCollider = new Collider({ 0.5f, 0.9f }, 1.0f, 0.2f);
	myCamera = std::make_shared<Camera>();
	myCameraController = std::make_shared<CameraBehavoir>();
	myCameraController->Init(myCamera, myPlayer);
	//myPlayer->Init();
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