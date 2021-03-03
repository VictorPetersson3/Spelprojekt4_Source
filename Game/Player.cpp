#include "stdafx.h"
#include "Timer.h"
#include "Player.h"
#include "InputManager.h"
#include <tga2d/sprite/sprite.h>
#include <iostream>
#define INPUT InputManager::GetInstance() 
#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

Player::Player()
{

}

Player::~Player()
{

}

void Player::Init()
{
	LoadJsonData();
	mySprite = std::make_shared<Tga2D::CSprite>("sprites/tga_logo.dds");
	mySprite->SetSizeRelativeToImage({ 0.1f,0.1f });

	myPosition = { 0.5f,0.1f };
	mySprite->SetPosition(Tga2D::Vector2f(myPosition.x, myPosition.y));
	mySprite->SetPivot({ 0.5f,0.5f });

}

void Player::Update()
{
	Movement();
	InputHandling();
	ApplyDrag();

	myPosition += myCurrentVelocity * DELTA_TIME;
	mySprite->SetPosition(Tga2D::Vector2f(myPosition.x, myPosition.y));
	//std::cout << "Pos x: " << myPosition.x << " " << "Pos y: " << myPosition.y << std::endl;
}

void Player::Render()
{
	mySprite->Render();

}

void Player::LoadJsonData()
{

}
void Player::InputHandling()
{
	float moveX = INPUT.IsKeyDown('D') + -INPUT.IsKeyDown('A');
	myInputVector = { moveX, static_cast<float>(INPUT.IsKeyDown('W')) };
}

void Player::JumpPhysics()
{
	if (myInputVector.y > 0)
	{
		if (myJumpTimer > myJumpTime)
		{
			myJumpTimer = 0;
			myIsGrounded = false;
			return;
		}
		else
		{
			myCurrentVelocity.y -= myJumpSpeed * DELTA_TIME;
			myJumpTimer += DELTA_TIME;
		}
	}
	if (INPUT.IsKeyUp('W'))
	{
		std::cout << "Key is up\n";
		myJumpTimer = 0;
		myIsGrounded = false;
	}

}
void Player::Movement()
{
	float moveThisFrameX = myInputVector.x * (myAcceleration * myAcceleration) * DELTA_TIME;

	if (!myIsGrounded)
	{
		PhysicsSimulation();
		moveThisFrameX *= 0.125f;
	}
	else
	{
		JumpPhysics();
	}
	if (std::abs(myCurrentVelocity.x) + moveThisFrameX <= myMaxVelocity)
	{
		myCurrentVelocity.x += moveThisFrameX;
	}

}

void Player::PhysicsSimulation()
{
	// Temp ground check (waiting for collision system)---- 
	if (mySprite->GetPosition().y > 0.9f)
	{
		myIsGrounded = true;
		myCurrentVelocity.y = 0;
		myPosition.y = .9f;
		return;
	}
	//End Temp ground check----

	if (!myIsGrounded)
	{
		myCurrentVelocity.y += (myGravity * 10) * DELTA_TIME;
		return;
	}
	if (myCurrentVelocity.y > 3.0f)
	{
		return;
	}
	myCurrentVelocity.y += std::abs((myCurrentVelocity.y + (myGravity * myGravity))) * DELTA_TIME;

}


void Player::ApplyDrag()
{
	if (myCurrentVelocity.x > 0)
	{
		myCurrentVelocity.x -= ((myDrag * myDrag) * DELTA_TIME) * myIsGrounded;
		return;
	}
	else if (myCurrentVelocity.x < 0)
	{
		myCurrentVelocity.x += ((myDrag * myDrag) * DELTA_TIME) * myIsGrounded;
	}
}
