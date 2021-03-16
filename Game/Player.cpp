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
#include "AnimationClip.h"
#include "RenderCommand.h"
#include "Enums.h"

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



	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_idle_R.dds", 0, (int)EPlayerAnimationClips::eIdleR));
	myAnimations[0]->Init({ 8, 1 }, { 7, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_idle_L.dds", 0, (int)EPlayerAnimationClips::eIdleL));
	myAnimations[1]->Init({ 8, 1 }, { 7, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_run_R.dds", 0, (int)EPlayerAnimationClips::eRunR));
	myAnimations[2]->Init({ 8, 1 }, { 5, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_run_L.dds", 0, (int)EPlayerAnimationClips::eRunL));
	myAnimations[3]->Init({ 8, 1 }, { 5, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_sprint_R.dds", 0, (int)EPlayerAnimationClips::eSprintR));
	myAnimations[4]->Init({ 8, 1 }, { 5, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_sprint_L.dds", 0, (int)EPlayerAnimationClips::eSprintL));
	myAnimations[5]->Init({ 8, 1 }, { 5, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_jump_R.dds", 0, (int)EPlayerAnimationClips::eJumpR));
	myAnimations[6]->Init({ 8, 1 }, { 5, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_jump_L.dds", 0, (int)EPlayerAnimationClips::eJumpL));
	myAnimations[7]->Init({ 8, 1 }, { 5, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_land_R.dds", 0, (int)EPlayerAnimationClips::eLandR));
	myAnimations[8]->Init({ 8, 1 }, { 5, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_land_L.dds", 0, (int)EPlayerAnimationClips::eLandL));
	myAnimations[9]->Init({ 8, 1 }, { 5, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_wallidle_R.dds", 0, (int)EPlayerAnimationClips::eWallIdleR));
	myAnimations[10]->Init({ 4, 1 }, { 4, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_wallidle_L.dds", 0, (int)EPlayerAnimationClips::eWallIdleL));
	myAnimations[11]->Init({ 4, 1 }, { 4, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_wallDown_R.dds", 0, (int)EPlayerAnimationClips::eWallDownR));
	myAnimations[12]->Init({ 4, 1 }, { 4, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_wallDown_L.dds", 0, (int)EPlayerAnimationClips::eWallDownL));
	myAnimations[13]->Init({ 4, 1 }, { 4, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_wallUp_R.dds", 0, (int)EPlayerAnimationClips::eWallUpR));
	myAnimations[14]->Init({ 4, 1 }, { 4, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_wallUp_L.dds", 0, (int)EPlayerAnimationClips::eWallUpL));
	myAnimations[15]->Init({ 4, 1 }, { 4, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_wallJump_R.dds", 0, (int)EPlayerAnimationClips::eWallJumpR));
	myAnimations[16]->Init({ 8, 1 }, { 6, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_wallJump_L.dds", 0, (int)EPlayerAnimationClips::eWallJumpL));
	myAnimations[17]->Init({ 8, 1 }, { 6, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_death_R.dds", 0, (int)EPlayerAnimationClips::eDeathR));
	myAnimations[18]->Init({ 16, 1 }, { 9, 1 });
	myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State1/player_death_L.dds", 0, (int)EPlayerAnimationClips::eDeathL));
	myAnimations[19]->Init({ 16, 1 }, { 9, 1 });

	myAnimations[(int)EPlayerAnimationClips::eIdleR]->PlayAnimLoop();

	mySprite = std::make_shared<Tga2D::CSprite>("sprites/Player.dds");
	mySprite->SetSizeRelativeToImage({ 0.1f,0.1f });
	mySprite->SetPosition(Tga2D::Vector2f(myPosition.x, myPosition.y));
	mySprite->SetPivot({ 0.5f,0.5f });

	myCollider = std::make_shared<Collider>(myPosition, mySprite->GetSize().x * (9.0f / 16.0f), mySprite->GetSize().y);
	myCollider->SetTag(EColliderTag::Player);
}

void Player::Update()
{
	Movement();
	std::printf("%d", myMoveState);
	UpdatePhysics();

	for (auto& anim : myAnimations)
	{
		anim->UpdateAnimation(myPosition);
	}
	PlayAnimation(myCurrentAnimation);
	//aCamera->BatchRenderSprite(myAnimations[(int)myCurrentAnimation]->GetRenderCommand());
}

void Player::Render(std::shared_ptr<Camera> aCamera)
{
	myAnimations[(int)myCurrentAnimation]->Render();
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

	CommonUtilities::Vector2f normal;
	CommonUtilities::Vector2f positionCorrection;

	myHugsLeftWall = false;
	myHugsRightWall = false;

	auto delta = myOldPosition - myPosition;
	for (int i = 0; i < myCollider->GetCollidedWith().size(); i++)
	{
		if (CollisionManager::GetInstance().CheckCollision(myCollider.get(), myCollider->GetCollidedWith()[i]))
		{
			positionCorrection = CollisionManager::GetInstance().AABBOverlap(myCollider.get(), myCollider->GetCollidedWith()[i]);
			normal += myCollider->GetCollisionNormal(i);

			/*positionCorrection.x += 1.0f / Tga2D::CEngine::GetInstance()->GetRenderSize().x * normal.GetNormalized().x;
			positionCorrection.y += 1.0f / Tga2D::CEngine::GetInstance()->GetRenderSize().y * normal.GetNormalized().y;*/

			shouldRevert = true;
		}
	}
	if (shouldRevert)
	{
		if (normal.y > 0)
		{
			myPosition.y -= positionCorrection.y;
			myIsRoofied = true;
		}
		else if (normal.y < 0)
		{
			myPosition.y -= positionCorrection.y;
			myIsGrounded = true;
			myMoveState = EMovementState::Idle;
		}
		if (normal.x > 0)
		{
			myPosition.x += positionCorrection.x;
			myHugsLeftWall = true;
		}
		else if (normal.x < 0)
		{
			myPosition.x -= positionCorrection.x;
			myHugsRightWall = true;
		}
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
		Ledge();
		break;
	}
}

void Player::Idle()
{
	myCurrentVelocity = CommonUtilities::Vector2f::Zero();

	myCurrentAnimation = EAnimationState::Idle;

	if (!myIsGrounded)
	{
		if (myHugsLeftWall || myHugsRightWall) myMoveState = EMovementState::Ledge;
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
	myCurrentAnimation = EAnimationState::Run;

	if (INPUT.IsKeyDown(myLeft) == INPUT.IsKeyDown(myRight))
	{
		myMoveState = EMovementState::Idle;
		return;
	}
	else if (INPUT.IsKeyDown(myRight))
	{
		myDirection = 1;
		if (myHugsRightWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			if (INPUT.IsKeyDown(myBoost))
			{
				myCurrentAnimation = EAnimationState::Sprint;
				myCurrentVelocity.x = myWalkSpeed * myBoostFactor;
			}
			else myCurrentVelocity.x += myWalkSpeed;
		}
	}
	else if (INPUT.IsKeyDown(myLeft))
	{
		myDirection = -1;
		if (myHugsLeftWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			if (INPUT.IsKeyDown(myBoost))
			{
				myCurrentAnimation = EAnimationState::Sprint;
				myCurrentVelocity.x = -myWalkSpeed * myBoostFactor;
			}
			else myCurrentVelocity.x += -myWalkSpeed;
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
		if (myCurrentVelocity.x > 0) myCurrentVelocity.x -= myAirAcceleration * 0.5f;
		if (myCurrentVelocity.x < 0) myCurrentVelocity.x += myAirAcceleration * 0.5f;
	}
	else if (INPUT.IsKeyDown(myRight))
	{
		myDirection = 1;

		if (myHugsRightWall && !myIsGrounded)
		{
			myMoveState = EMovementState::Ledge;
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			if (INPUT.IsKeyDown(myBoost))
			{
				if (myCurrentVelocity.x <= myMaxAirSpeed * myBoostFactor) myCurrentVelocity.x += myAirAcceleration * myBoostFactor;
			}
			else if (myCurrentVelocity.x <= myMaxAirSpeed) myCurrentVelocity.x += myAirAcceleration;
		}
	}
	else if (INPUT.IsKeyDown(myLeft))
	{
		myDirection = -1;

		if (myHugsLeftWall && !myIsGrounded)
		{
			myMoveState = EMovementState::Ledge;
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			if (INPUT.IsKeyDown(myBoost))
			{
				if (myCurrentVelocity.x >= -myMaxAirSpeed * myBoostFactor) myCurrentVelocity.x -= myAirAcceleration * myBoostFactor;
			}
			else if (myCurrentVelocity.x >= -myMaxAirSpeed) myCurrentVelocity.x -= myAirAcceleration;
		}
	}
	if (!INPUT.IsKeyDown(myJump) && myCurrentVelocity.y < 0.0f)
	{
		myCurrentVelocity.y += myJumpDecceleration;
	}
}

void Player::Ledge()
{
	//ledge anim
	myCurrentVelocity.y += myGravity * DELTA_TIME;
	if (myCurrentVelocity.y <= myMaxWallSlideSpeed) myCurrentVelocity.y = myMaxWallSlideSpeed;
	if (myCurrentVelocity.y >= myMaxWallSlideSpeed) myCurrentVelocity.y = myMaxWallSlideSpeed;

	if (myIsGrounded)
	{
		myMoveState = EMovementState::Idle;
		return;
	}

	if (INPUT.IsKeyDown(myLeft) == INPUT.IsKeyDown(myRight))
	{
		myCurrentVelocity.x = 0;
		myMoveState = EMovementState::Idle;
	}
	else if (INPUT.IsKeyDown(myRight))
	{
		myDirection = 1;

		if (myHugsRightWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		if (INPUT.IsKeyDown(myJump))
		{
			myCurrentVelocity.x = -myJumpSpeed;
			myCurrentVelocity.y = -myJumpSpeed;
			//jump sfx ?
			myMoveState = EMovementState::Falling;
			return;
		}
	}
	else if (INPUT.IsKeyDown(myLeft))
	{
		myDirection = -1;
		if (myHugsLeftWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		if (INPUT.IsKeyDown(myJump))
		{
			myCurrentVelocity.x = myJumpSpeed;
			myCurrentVelocity.y = -myJumpSpeed;
			//jump sfx ?
			myMoveState = EMovementState::Falling;
			return;
		}
	}
}

void Player::PlayAnimation(EAnimationState anAnimEnum)
{
	for (auto& anim : myAnimations)
	{
		if (anim->GetAnimIsPlaying())
		{
			if (anim->GetAnimationTypeIndex() == (int)anAnimEnum * 2 || anim->GetAnimationTypeIndex() == (int)anAnimEnum * 2 + 1)
			{
				return;
			}
			if (myDirection > 0)
			{
				myAnimations[(int)anAnimEnum * 2]->PlayAnimLoop();
			}
			return;
			if (myDirection < 0)
			{
				myAnimations[(int)anAnimEnum * 2 + 1]->PlayAnimLoop();
			}
			return;
		}
	}
}

