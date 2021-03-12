#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include "InputManager.h"
#include "Timer.h"
#include "CommonUtilities/Random.h"
#include "Camera.h"
#include "StateManager.h"

#include "LevelLoader.h"
#include "Player.h"

#include "CollisionManager.h"

CGameWorld::CGameWorld()
{
	myTga2dLogoSprite = nullptr;
}

CGameWorld::~CGameWorld() 
{
	delete myTga2dLogoSprite;
	myTga2dLogoSprite = nullptr;
}

void CGameWorld::Init()  
{
	CollisionManager::Init();
	StateManager::Init();
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });
	myCamera = std::make_unique<Camera>();
	
	//myCollider = new Collider({ 0.5f, 0.9f }, 1.0f, 0.2f);

	myPlayer = std::make_unique<Player>();
	myCamera = std::make_shared<Camera>();
	myPlayer->Init();
}

void CGameWorld::Update(float /*aTimeDelta*/)
{ 	
	StateManager::GetInstance().Update();
	myCamera->Update(myPlayer->GetPosition());

	//myCollider->Draw();
	//If you want to render something send in the sprite to the Camera
	myPlayer->Update();
	CollisionManager::GetInstance().Update();
	
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
	//myTga2dLogoSprite->Render();
	myPlayer->Render(myCamera);
	/*myTga2dLogoSprite->Render();*/
}