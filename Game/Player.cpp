#include "stdafx.h"
#include "Timer.h"
#include "Player.h"
#include "InputManager.h"
#include <tga2d/sprite/sprite.h>
#include <iostream>
#include <Xinput.h>
#include "Camera.h"
#include "Collider.h"
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
	myCanJump = true;
	myCollider = std::make_shared<Collider>(0.01f, myPosition);
	
	myPosition = { 0.5f,0.1f };
	
	LoadJsonData();
	
	mySprite = std::make_shared<Tga2D::CSprite>("sprites/Player.dds");
	mySprite->SetSizeRelativeToImage({ 0.1f,0.1f });
	mySprite->SetPosition(Tga2D::Vector2f(myPosition.x, myPosition.y));
	mySprite->SetPivot({ 0.5f,0.5f });

}

void Player::Update()
{
	timer -= DELTA_TIME;
	if (timer >  0)
	{
		return;
	}

	Movement();
	InputHandling();
	myPosition += myCurrentVelocity * DELTA_TIME;

	myCollider->UpdateCollider(myPosition);
	myCollider->Draw();
	mySprite->SetPosition(Tga2D::Vector2f(myPosition.x, myPosition.y));
	//std::cout << "Pos x: " << myPosition.x << " " << "Pos y: " << myPosition.y << std::endl;
}

void Player::Render(std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(*mySprite);
}

CommonUtilities::Vector2f Player::GetPosition() const
{
	return myPosition;
}

void Player::LoadJsonData()
{

}
void Player::InputHandling()
{
	myBoostInput = INPUT.IsKeyDown('Z') || INPUT.IsKeyDown(VK_LSHIFT);

	float moveY = INPUT.IsKeyDown('W') || INPUT.IsKeyDown(VK_UP) || INPUT.IsKeyDown(VK_SPACE) || INPUT.IsKeyDown('X');

	const bool isKeyUp = INPUT.IsKeyUp('W') || INPUT.IsKeyUp(VK_UP) || INPUT.IsKeyUp(VK_SPACE) || INPUT.IsKeyUp('X');
	const float moveX = (INPUT.IsKeyDown('D') || INPUT.IsKeyDown(VK_RIGHT)) - (INPUT.IsKeyDown('A') || INPUT.IsKeyDown(VK_LEFT));
	
	if (!myIsGrounded)
		if (isKeyUp)
			myCanJump = true;

	moveY *= myCanJump;
	myInputVector = { moveX,  moveY };
}

void Player::JumpPhysics()
{
	if (myInputVector.y > 0)
	{		
		if (myJumpTimer > myJumpTime)
		{
			myJumpTimer = 0;
			myIsGrounded = false;
			myCanJump = false;
			return;
		}
		else
		{
			myCurrentVelocity.y -= myJumpSpeed * DELTA_TIME;
			myJumpTimer += DELTA_TIME;
		}
	}
	bool isKeyUp = INPUT.IsKeyUp('W') || INPUT.IsKeyUp(VK_UP) || INPUT.IsKeyUp(VK_SPACE) || INPUT.IsKeyUp('X');
	if (isKeyUp)
	{
		myCanJump = true;
		myJumpTimer = 0;
		myIsGrounded = false;
	}

}
void Player::Movement()
{
	float moveThisFrameX = (((myAcceleration * myAcceleration) + (myBoostAcceleration * myBoostInput)) * DELTA_TIME) * myInputVector.x;
	if (!myIsGrounded)
	{
		PhysicsSimulation();
		moveThisFrameX *= 0.125f;
	}
	else
	{
		JumpPhysics();
	}
	ApplyDrag(moveThisFrameX);


	CollisionSolver(myCurrentVelocity);

	if (std::abs(myCurrentVelocity.x) + moveThisFrameX <= myMaxVelocity + (myBoostInput * myMaxBoostVelocity))	
		myCurrentVelocity.x += moveThisFrameX;
}

void Player::PhysicsSimulation()
{
	// Temp ground check (waiting for collision system)---- 
	/*if (mySprite->GetPosition().y > 0.9f)
	{
		myIsGrounded = true;
		myCurrentVelocity.y = 0;
		myPosition.y = .9f;
		return;
	}*/
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


void Player::ApplyDrag(const float aFrameVel)
{	
	float graceValue = (aFrameVel + 0.001f) * DELTA_TIME;
	float absoluteVelocity = std::abs(myCurrentVelocity.x) * DELTA_TIME;
	
	if (absoluteVelocity <= graceValue)
	{
		myCurrentVelocity.x = 0;
		return;
	}

	float currentDrag = (myDrag * myDrag) + (myBoostDrag * myBoostInput);
	if (myCurrentVelocity.x > 0)
	{
		myCurrentVelocity.x -= (currentDrag * DELTA_TIME) * myIsGrounded;
		return;
	}
	else if (myCurrentVelocity.x < 0)
	{
		myCurrentVelocity.x += (currentDrag * DELTA_TIME) * myIsGrounded;
	}
}

void Player::CollisionSolver(CommonUtilities::Vector2f aFrameDirection)
{
	CommonUtilities::Vector2f normal = myCollider->GetCollisionNormal();
	if (normal != CommonUtilities::Vector2f::Zero())
	{
		myCurrentVelocity = CommonUtilities::Vector2f::Zero();
	}

}
