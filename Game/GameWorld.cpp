#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include "InputManager.h"
#include "Timer.h"
#include "CommonUtilities/Random.h"
#include "Camera.h"
#include "StateManager.h"
#include <CommonUtilities/Vector2.hpp>
#include "LevelLoader.h"
#include "Player.h"
#include "XController.h"
#include "CollisionManager.h"
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

	myCamera = std::make_unique<Camera>();

	myController = std::make_shared<XController>(1);

	//myCollider = new Collider({ 0.5f, 0.9f }, 1.0f, 0.2f);

	myPlayer = std::make_unique<Player>();
	myCamera = std::make_shared<Camera>();
	//myPlayer->Init();
}

void CGameWorld::Update(float /*aTimeDelta*/)
{ 	
	StateManager::GetInstance().Update();
	myCamera->Update(myPlayer->GetPosition());

	//myCollider->Draw();
	//If you want to render something send in the sprite to the Camera
	//myPlayer->Update();
	CollisionManager::GetInstance().Update();
	

	// Exempel på hur man använder controller input, passa igenom den där ni behöver den som en "shared_ptr"
	if (myController->IsConnected())
	{
		if (myController->IsButton_A_Pressed())
		{
			std::cout << "A is pressed " << sm << std::endl;
			sm++;
		}
		if (myController->IsButton_X_Pressed())
		{
			std::cout << "X is pressed " << sm << std::endl;
			sm++;
		}
		if (myController->IsButton_Y_Pressed())
		{
			std::cout << "Y is pressed " << sm << std::endl;
			sm++;
		}
		if (myController->IsButton_B_Pressed())
		{
			std::cout << "B is pressed " << sm << std::endl;
			sm++;
		}

		if (myController->GetLeftTumbStick() != CommonUtilities::Vector2f::Zero())
		{
			std::cout << "Moveing left thumbstick: " << myController->GetLeftTumbStick().x << " " <<myController->GetLeftTumbStick().y << std::endl;
		
		}
		if (myController->GetRightTumbStick() != CommonUtilities::Vector2f::Zero())
		{
			std::cout << "Moveing right thumbstick: " << myController->GetRightTumbStick().x << " " << myController->GetRightTumbStick().y << std::endl;
			
		}
		if (myController->GetDPadInput() != CommonUtilities::Vector2f::Zero())
		{
			std::cout << "DPad Input: " << myController->GetDPadInput().x << " " << myController->GetDPadInput().y << std::endl;
			
		}
		if (myController->IsButton_LS_Pressed())
		{
			std::cout << "LS Is Pressed " << sm << std::endl;
			sm++;
		}
		if (myController->IsButton_RS_Pressed())
		{
			std::cout << "RS Is Pressed " << sm << std::endl;
			sm++;
		}
		if (myController->IsButton_RT_Pressed())
		{
			std::cout << "RT Is Pressed " << sm << std::endl;
			sm++;
		}

		if (myController->IsButton_LT_Pressed())
		{
			std::cout << "LT Is Pressed " << sm << std::endl;
			sm++;
		}

	}


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
	//myPlayer->Render(myCamera);
	/*myTga2dLogoSprite->Render();*/
}