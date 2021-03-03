#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include "InputManager.h"
#include "Timer.h"
#include "CommonUtilities/Random.h"
#include "testObjectsWithPositions.h"
#include "Camera.h"

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
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });
	for (int i = 0; i < 100; i++)
	{
		testObjects[i] = new testObjectsWithPositions;
		testObjects[i]->Init({CommonUtilities::GetRandomFloat(-1, 1), CommonUtilities::GetRandomFloat(-1, 1) });
	}
	myCamera = new Camera;
}


void CGameWorld::Update(float /*aTimeDelta*/)
{ 	
	myCamera->Update();
	for (int i = 0; i < 100; i++)
	{
		//testObjects[i]->GetSprite()->Render();
		myCamera->RenderSprite(*testObjects[i]->GetSprite());
	}
	//if (InputManager::GetInstance().IsKeyPressed('S'))
	//{
	//	printf("Was Pressed\n");
	//}
	//if (InputManager::GetInstance().IsKeyUp('S'))
	//{
	//	printf("Was Released\n");
	//}
	//if (InputManager::GetInstance().IsKeyDown('S'))
	//{
	//	printf("Is Held\n");
	//}
	//printf("Delta Time: %f\n", Timer::GetInstance().GetDeltaTime());
}

void CGameWorld::Render()
{
	
	//myTga2dLogoSprite->Render();
}