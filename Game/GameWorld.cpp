#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include "InputManager.h"
#include "Player.h"
#include "Timer.h"
CGameWorld::CGameWorld()
{
	
}

CGameWorld::~CGameWorld() 
{
	
}

void CGameWorld::Init()  
{
	myPlayer = std::make_unique<Player>();
	myPlayer->Init();

}


void CGameWorld::Update(float /*aTimeDelta*/)
{ 	
	myPlayer->Update();
}

void CGameWorld::Render()
{
	myPlayer->Render();
}