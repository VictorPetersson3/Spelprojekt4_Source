#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include "InputManager.h"
#include "Timer.h"
#include "LevelLoader.h"

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
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });

	myLevelLoader = new LevelLoader();

	myLevelLoader->LoadLevel("Json/Levels/Runtfaff.json");

}


void CGameWorld::Update(float /*aTimeDelta*/)
{ 	
	if (InputManager::GetInstance().IsKeyPressed('S'))
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
	}
	//printf("Delta Time: %f\n", Timer::GetInstance().GetDeltaTime());

}

void CGameWorld::Render()
{
	myTga2dLogoSprite->Render();
	myLevelLoader->Render();
}