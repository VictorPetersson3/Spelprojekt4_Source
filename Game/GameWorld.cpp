#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include "InputManager.h"
#include "Timer.h"
#include "CommonUtilities/Random.h"
#include "Camera.h"
#include "LevelLoader.h"
#include "Player.h"
CGameWorld::CGameWorld()
{
	myTga2dLogoSprite = nullptr;
	myLevelLoader = nullptr;
}

CGameWorld::~CGameWorld() 
{
	delete myTga2dLogoSprite;
	myTga2dLogoSprite = nullptr;

	delete myLevelLoader;
	myLevelLoader = nullptr;
}

void CGameWorld::Init()  
{
	myPlayer = std::make_unique<Player>();
	myCamera = std::make_shared<Camera>();
	myPlayer->Init();
	myLevelLoader = new LevelLoader();

	myLevelLoader->LoadLevel("Json/Levels/Runtfaff.json");

}


void CGameWorld::Update(float /*aTimeDelta*/)
{ 	
	myPlayer->Update();
	myCamera->Update(myPlayer->GetPosition());
	myLevelLoader->Update(myCamera);
	//If you want to render something send in the sprite to the Camera

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