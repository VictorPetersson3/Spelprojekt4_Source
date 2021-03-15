#include "stdafx.h"
#include "Timer.h"
#include "Player.h"
#include "InputManager.h"
#include <tga2d/sprite/sprite.h>
#include <iostream>
#include <Xinput.h>
#include "Camera.h"
#include "Collider.h"
#include "CollisionManager.h"

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
	myPosition = { 0.5f,0.1f };

	mySprite = std::make_shared<Tga2D::CSprite>("sprites/Player.dds");
	mySprite->SetSizeRelativeToImage({ 0.1f,0.1f });
	mySprite->SetPosition(Tga2D::Vector2f(myPosition.x, myPosition.y));
	mySprite->SetPivot({ 0.5f,0.5f });

	auto wideboi = mySprite->GetSize().x * Tga2D::CEngine::GetInstance()->GetRenderSize().x;
	auto heity = mySprite->GetSize().y * Tga2D::CEngine::GetInstance()->GetRenderSize().y;

	myCollider = std::make_shared<Collider>(myPosition, mySprite->GetSize().x * (9.0f / 16.0f), mySprite->GetSize().y);
	myCollider->SetTag(EColliderTag::Player);
}

void Player::Update()
{
	Movement();

	UpdatePhysics();

	mySprite->SetPosition({ myPosition.x, myPosition.y });
}

void Player::Render(std::shared_ptr<Camera> aCamera)
{
	aCamera->RenderSprite(*mySprite);
}

CommonUtilities::Vector2f Player::GetPosition() const
{
	return myPosition;
}

void Player::ChangeInput(EInputType anInputType)
{
	switch (anInputType)
	{
	case EInputType::ArrowKeys:
		myUp = VK_UP;
		myLeft = VK_LEFT;
		myDown = VK_DOWN;
		myRight = VK_RIGHT;
		myJump = 'X';
		myBoost = 'Z';
		break;
	case EInputType::WASD:
		myUp = 'W';
		myLeft = 'A';
		myDown = 'S';
		myRight = 'D';
		myJump = VK_SPACE;
		myBoost = VK_SHIFT;
		break;
	case EInputType::Controller:
		myUp = XINPUT_GAMEPAD_DPAD_UP;
		myLeft = XINPUT_GAMEPAD_DPAD_LEFT;
		myDown = XINPUT_GAMEPAD_DPAD_DOWN;
		myRight = XINPUT_GAMEPAD_DPAD_RIGHT;
		myJump = XINPUT_GAMEPAD_A;
		myBoost = XINPUT_GAMEPAD_B;
		break;
	}
}

void Player::UpdatePhysics()
{
	CacheCurrentValues();

	myPosition += myCurrentVelocity * Timer::GetInstance().GetDeltaTime();
	myCollider->UpdateCollider(myPosition);

	CollisionManager::GetInstance().Update();
	bool shouldRevert = false;
	for (int i = 0; i < myCollider->GetCollidedWith().size(); i++)
	{
		if (CollisionManager::GetInstance().CheckCollision(myCollider.get(), myCollider->GetCollidedWith()[i]))
		{
			shouldRevert = true;
		}
	}
	if (shouldRevert)
	{
		myPosition = myOldPosition;
		myIsGrounded = true;
		myMoveState = EMovementState::Idle;
	}
	else
	{
		myIsGrounded = false;
	}
}

void Player::CacheCurrentValues()
{
	myOldPosition = myPosition;
	myOldVelocity = myCurrentVelocity;
	myWasGrounded = myIsGrounded;
	myHuggedRightWall = myHugsRightWall;
	myHuggedLeftWall = myHugsLeftWall;
	myWasRoofied = myIsRoofied;
}

void Player::Movement()
{
	switch (myMoveState)
	{
	case EMovementState::Idle:
		Idle();
		break;
	case EMovementState::Walk:
		Walk();
		break;
	case EMovementState::Falling:
		Falling();
		break;
	case EMovementState::Ledge:
		break;
	}
}

void Player::Idle()
{
	myCurrentVelocity = CommonUtilities::Vector2f::Zero();
	//Idle anim

	if (!myIsGrounded)
	{
		myMoveState = EMovementState::Falling;
		return;
	}
	if (INPUT.IsKeyDown(myLeft) != INPUT.IsKeyDown(myRight))
	{
		myMoveState = EMovementState::Walk;
		return;
	}
	else if (INPUT.IsKeyDown(myJump))
	{
		myCurrentVelocity.y = -myJumpSpeed;
		myMoveState = EMovementState::Falling;
		return;
	}
}

void Player::Walk()
{
	//walk anim

	if (INPUT.IsKeyDown(myLeft) == INPUT.IsKeyDown(myRight))
	{
		myMoveState = EMovementState::Idle;
		myCurrentVelocity = CommonUtilities::Vector2f::Zero();
		return;
	}
	else if (INPUT.IsKeyDown(myRight))
	{
		if (myHugsRightWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			myCurrentVelocity.x = myWalkSpeed;
		}
	}
	else if (INPUT.IsKeyDown(myLeft))
	{
		if (myHugsLeftWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			myCurrentVelocity.x = -myWalkSpeed;
		}
	}

	if (INPUT.IsKeyDown(myJump))
	{
		myCurrentVelocity.y = -myJumpSpeed;
		//jump sfx ?
		myMoveState = EMovementState::Falling;
		return;
	}
	else if (!myIsGrounded)
	{
		myMoveState = EMovementState::Falling;
		return;
	}
}

void Player::Falling()
{
	//anim

	if (myCurrentVelocity.y >= myMaxVelocity) myCurrentVelocity.y = myMaxVelocity;
	else myCurrentVelocity.y += myGravity * DELTA_TIME;

	if (INPUT.IsKeyDown(myLeft) == INPUT.IsKeyDown(myRight))
	{
		myCurrentVelocity.x = 0;
	}
	else if (INPUT.IsKeyDown(myRight))
	{
		if (myHugsRightWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			if (myCurrentVelocity.x >= myMaxAirSpeed) myCurrentVelocity.x = myMaxAirSpeed;
			else myCurrentVelocity.x += myAirAcceleration;
		}
	}
	else if (INPUT.IsKeyDown(myLeft))
	{
		if (myHugsLeftWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			if (myCurrentVelocity.x <= -myMaxAirSpeed) myCurrentVelocity.x = -myMaxAirSpeed;
			else myCurrentVelocity.x -= myAirAcceleration;
		}
	}
	if (!INPUT.IsKeyDown(myJump) && myCurrentVelocity.y < 0.0f)
	{
		myCurrentVelocity.y += myJumpDecceleration;
	}
}

