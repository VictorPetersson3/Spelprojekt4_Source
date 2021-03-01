#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include <iostream>


CGameWorld::CGameWorld(CommonUtilities::InputManager* aInputManager, CommonUtilities::Timer* aTimer) :
	myInputManager(aInputManager),
	myGameTimer(aTimer)
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
}


void CGameWorld::Update(float /*aTimeDelta*/)
{ 	
	for (int i = 0; i < 1000000; i++)
	{
		int j = i;
	}
	if (myInputManager->IsKeyPressed(VK_SPACE))
	{
		std::cout << "Was Pressed\n";
	}
	if (myInputManager->IsKeyUp('S'))
	{
		std::cout << "Was Released\n";
	}
	if (myInputManager->IsKeyDown('S'))
	{
		std::cout << "Is Held\n";
	}
}

void CGameWorld::Render()
{
	myTga2dLogoSprite->Render();
}