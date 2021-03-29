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
#include "RenderCommand.h"
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

	myKey = std::make_shared<Key>();
	myKey->Init(myPlayer, 1);

	myDoors = std::make_shared<Door>();
	myDoors->Init(myKey);
	myDoors->SetPosition({ 0.5f, 0.1f });



	myCamera = std::make_unique<Camera>();
	myController = std::make_shared<XController>(1);

	//myCollider = new Collider({ 0.5f, 0.9f }, 1.0f, 0.2f);

	myCamera = std::make_shared<Camera>();
	//myPlayer->Init();
}

void CGameWorld::Update(float /*aTimeDelta*/)
{
	StateManager::GetInstance().Update();
	myCamera->Update(myPlayer->GetPosition());
	myKey->Update();


	myDoors->Update();

	//myCollider->Draw();
	//If you want to render something send in the sprite to the Camera
	//myPlayer->Update();
	CollisionManager::GetInstance().Update();


	// Exempel på hur man använder controller input, passa igenom den där ni behöver den som en "shared_ptr"
	/*if (InputManager::GetInstance().IsKeyPressed('S'))
	{
		printf("Was Pressed\n");
	}
	if (InputManager::GetInstance().IsKeyUp('S'))
	{
		printf("Was Released\n");
	}
	if (InputManager::GetInstance().IsKeyDown('S'))
	{
		printf("Is Held\n");
	}*/
	//printf("Delta Time: %f\n", Timer::GetInstance().GetDeltaTime());

}

void CGameWorld::Render()
{
	 
	myKey->Render(myCamera);
	myDoors->Render(myCamera);
	//myTga2dLogoSprite->Render();
	//myPlayer->Render(myCamera);
	/*myTga2dLogoSprite->Render();*/
}