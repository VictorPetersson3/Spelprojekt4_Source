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

#define INPUT InputManager::GetInstance() 
#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

Player::Player()
{

}

Player::~Player()
{

}

void Player::Init(CommonUtilities::Vector2f aPosition)
{
	myPosition = aPosition;

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

void Player::Update(Camera& aCamera)
{
	ManageStates();
	UpdatePhysics();

	for (auto& anim : myAnimations)
	{
		anim->UpdateAnimation(myPosition);
	}
	//printf("%d", myCurrentAnimation);
	PlayAnimation(myCurrentAnimation);

	int thing = (int)myCurrentAnimation * 2 + (myDirection < 0);
	aCamera.RenderSprite(myAnimations[thing]->GetRenderCommand());
}

void Player::Render(std::shared_ptr<Camera> aCamera)
{
	/*int thing = (int)myCurrentAnimation * 2 + (myDirection < 0);
	myAnimations[thing]->Render();*/
}

CommonUtilities::Vector2f Player::GetPosition() const
{
	return myPosition;
}
const bool Player::IsDead() const
{
	if (myIsDead)
	{
		int enumer = (int)EAnimationState::Death * 2 + (myDirection < 0);
		if (myAnimations[enumer]->GetAnimIsDone()) return true;
	}
	return false;
}
void Player::SetPosition(const CommonUtilities::Vector2f& aPosition)
{
	myPosition = aPosition;
}

std::shared_ptr<Collider> Player::GetCollider()
{
	return myCollider;
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
	myPosition += myCurrentVelocity * DELTA_TIME;

	CollisionManager::GetInstance().Update();

	CommonUtilities::Vector2f normal;
	CommonUtilities::Vector2f positionCorrection;
	CommonUtilities::Vector2f posCorrNormal;

	Collider* verticalCollider = nullptr;
	Collider* horizontalCollider = nullptr;

	myHugsLeftWall = false;
	myHugsRightWall = false;

	auto delta = myOldPosition - myPosition;

	for (int i = 0; i < myCollider->GetCollidedWith().size(); i++)
	{
		if (myCollider->GetCollidedWith()[i]->GetTag() == EColliderTag::KillZone)
		{
			myMoveState = EPlayerState::Death;
			break;
		}

		normal = myCollider->GetCollisionNormal(i);

		if (verticalCollider != nullptr && normal.y != 0)
		{
			if ((verticalCollider->GetPosition() - myCollider->GetPosition() * normal).Length() >= (myCollider->GetCollidedWith()[i]->GetPosition() - myCollider->GetPosition()).Length())
				verticalCollider = myCollider->GetCollidedWith()[i];
		}
		else if (verticalCollider == nullptr && normal.y != 0)
		{
			verticalCollider = myCollider->GetCollidedWith()[i];
		}
		if (horizontalCollider != nullptr && normal.x != 0)
		{
			if ((horizontalCollider->GetPosition() - myCollider->GetPosition() * normal).Length() >= (myCollider->GetCollidedWith()[i]->GetPosition() - myCollider->GetPosition()).Length())
				horizontalCollider = myCollider->GetCollidedWith()[i];
		}
		else if (horizontalCollider == nullptr && normal.x != 0)
		{
			horizontalCollider = myCollider->GetCollidedWith()[i];
		}
	}

	if (myCollider->GetCollidedWith().size())
	{
		if (horizontalCollider != nullptr)
		{
			positionCorrection.x = CollisionManager::GetInstance().AABBOverlap(myCollider.get(), horizontalCollider).x;
			posCorrNormal.x = CollisionManager::GetInstance().CollisionNormal(myCollider.get(), horizontalCollider).x;
		}
		if (verticalCollider != nullptr)
		{
			positionCorrection.y = CollisionManager::GetInstance().AABBOverlap(myCollider.get(), verticalCollider).y;
			posCorrNormal.y = CollisionManager::GetInstance().CollisionNormal(myCollider.get(), verticalCollider).y;
		}

		//positionCorrection.x -= 1.0f / Tga2D::CEngine::GetInstance()->GetRenderSize().x;
		//positionCorrection.y -= 1.0f / Tga2D::CEngine::GetInstance()->GetRenderSize().y;

		positionCorrection *= posCorrNormal;
		//myPosition += positionCorrection;

		if (posCorrNormal.y > 0)
		{
			myPosition.y += positionCorrection.y;
			myIsRoofied = true;
		}
		else if (posCorrNormal.y < 0)
			//else if (positionCorrection.y > -1.0f / Tga2D::CEngine::GetInstance()->GetRenderSize().x)
		{
			myPosition.y += positionCorrection.y;
			myIsGrounded = true;
			//myMoveState = EMovementState::Idle;
		}
		if (posCorrNormal.x > 0 &&
			myCollider->GetPosition().y < horizontalCollider->GetPosition().y + horizontalCollider->GetSize().y * 0.5f &&
			myCollider->GetPosition().y > horizontalCollider->GetPosition().y - horizontalCollider->GetSize().y * 0.5f)
		{
			myPosition.x += positionCorrection.x;
			myHugsLeftWall = true;
		}
		else if (posCorrNormal.x < 0 &&
			myCollider->GetPosition().y < horizontalCollider->GetPosition().y + horizontalCollider->GetSize().y * 0.5f &&
			myCollider->GetPosition().y > horizontalCollider->GetPosition().y - horizontalCollider->GetSize().y * 0.5f)
		{
			myPosition.x += positionCorrection.x;
			myHugsRightWall = true;
		}
	}
	else
	{
		myIsGrounded = false;
	}
	myCollider->UpdateCollider(myPosition);
}

void Player::CacheCurrentValues()
{
	myOldPosition = myPosition;
	myOldVelocity = myCurrentVelocity;
	myWasGrounded = myIsGrounded;
	myHuggedRightWall = myHugsRightWall;
	myHuggedLeftWall = myHugsLeftWall;
	myWasRoofied = myIsRoofied;
	myWasDead = myIsDead;
}

void Player::ManageStates()
{
	//std::printf("%d", myMoveState);

	switch (myMoveState)
	{
	case EPlayerState::Idle:
		Idle();
		break;
	case EPlayerState::Walk:
		Walk();
		break;
	case EPlayerState::Falling:
		Falling();
		break;
	case EPlayerState::Ledge:
		Ledge();
		break;
	case EPlayerState::Death:
		Die();
		break;
	}
}

void Player::Idle()
{
	if (!myWasGrounded)
	{
		if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eLandL);
		else PlaySpecificAnimation(EPlayerAnimationClips::eLandR);
	}
	//myCurrentVelocity = CommonUtilities::Vector2f::Zero();
	if (myCurrentVelocity.x > 0) myCurrentVelocity.x -= 0.001f; // g�nger deltatime? ??
	if (myCurrentVelocity.x < 0) myCurrentVelocity.x += 0.001f;

	myCurrentAnimation = EAnimationState::Idle;

	if (!myIsGrounded)
	{
		myMoveState = EPlayerState::Falling;
		/*if (myHugsLeftWall || myHugsRightWall) myMoveState = EMovementState::Ledge;*/
		return;
	}
	if (INPUT.IsKeyDown(myLeft) != INPUT.IsKeyDown(myRight))
	{
		myMoveState = EPlayerState::Walk;
		return;
	}
	else if (INPUT.IsKeyDown(myJump))
	{
		printf("jag borde bara skrivas ut en g�ng per hopp\n");
		myCurrentVelocity.y = -myJumpSpeed;
		myMoveState = EPlayerState::Falling;
		return;
	}
}

void Player::Walk()
{
	if (!myWasGrounded)
	{
		if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eLandL);
		else PlaySpecificAnimation(EPlayerAnimationClips::eLandR);
	}

	myCurrentAnimation = EAnimationState::Run;

	if (INPUT.IsKeyDown(myLeft) == INPUT.IsKeyDown(myRight))
	{
		myMoveState = EPlayerState::Idle;
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
				if (myCurrentVelocity.x <= myMaxAirSpeed * myBoostFactor) myCurrentVelocity.x += myWalkSpeed * myBoostFactor;
			}
			else if (myCurrentVelocity.x <= myMaxHorizontalVelocity) myCurrentVelocity.x += myWalkSpeed;
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
				if (myCurrentVelocity.x >= -myMaxAirSpeed * myBoostFactor) myCurrentVelocity.x -= myWalkSpeed * myBoostFactor;
			}
			else if (myCurrentVelocity.x >= -myMaxHorizontalVelocity) myCurrentVelocity.x -= myWalkSpeed;
		}
	}

	if (INPUT.IsKeyDown(myJump))
	{
		myCurrentVelocity.y = -myJumpSpeed;
		//jump sfx ?
		myMoveState = EPlayerState::Falling;
		//myCurrentAnimation = EAnimationState::Jump;
		printf("jag borde bara skrivas ut en g�ng per hopp\n");

		if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eJumpL);
		else PlaySpecificAnimation(EPlayerAnimationClips::eJumpR);
		return;
	}
	else if (!myIsGrounded)
	{
		myMoveState = EPlayerState::Falling;
		return;
	}
}

void Player::Falling()
{
	myCurrentAnimation = EAnimationState::Jump;

	if (myCurrentVelocity.y >= myMaxVerticalVelocity) myCurrentVelocity.y = myMaxVerticalVelocity;
	else myCurrentVelocity.y += myGravity * DELTA_TIME;

	//std::printf("%d", myIsGrounded);

	if (INPUT.IsKeyDown(myLeft) == INPUT.IsKeyDown(myRight))
	{
		if (myIsGrounded) myMoveState = EPlayerState::Idle;
		if (myCurrentVelocity.x > 0) myCurrentVelocity.x -= 0.00025f;
		if (myCurrentVelocity.x < 0) myCurrentVelocity.x += 0.00025f;
	}
	else if (INPUT.IsKeyDown(myRight))
	{
		myDirection = 1;

		if (myIsGrounded) myMoveState = EPlayerState::Walk;
		if (myHugsRightWall && !myIsGrounded && !myWasGrounded)
		{
			myMoveState = EPlayerState::Ledge;
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

		if (myIsGrounded) myMoveState = EPlayerState::Walk;
		if (myHugsLeftWall && !myIsGrounded && !myWasGrounded)
		{
			myMoveState = EPlayerState::Ledge;
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
	if (myIsGrounded)
	{
		myMoveState = EPlayerState::Idle;
		return;
	}

	if (myCurrentVelocity.y == 0) myCurrentAnimation = EAnimationState::W_Idle;
	else if (myCurrentVelocity.y > 0) myCurrentAnimation = EAnimationState::W_Down;
	else if (myCurrentVelocity.y < 0) myCurrentAnimation = EAnimationState::W_Up;

	myCurrentVelocity.y += myGravity * DELTA_TIME;
	if (myCurrentVelocity.y <= myMaxWallSlideSpeed) myCurrentVelocity.y = myMaxWallSlideSpeed;
	if (myCurrentVelocity.y >= myMaxWallSlideSpeed) myCurrentVelocity.y = myMaxWallSlideSpeed;


	if (INPUT.IsKeyDown(myLeft) == INPUT.IsKeyDown(myRight))
	{
		myCurrentVelocity.x = 0;
		myMoveState = EPlayerState::Idle;
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

			printf("jag borde bara skrivas ut en g�ng per hopp\n");
			//jump sfx ?
			PlaySpecificAnimation(EPlayerAnimationClips::eWallJumpL);

			myMoveState = EPlayerState::Falling;
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

			printf("jag borde bara skrivas ut en g�ng per hopp\n");
			//jump sfx ?
			PlaySpecificAnimation(EPlayerAnimationClips::eWallJumpR);

			myMoveState = EPlayerState::Falling;
			return;
		}
	}
}

void Player::Die()
{
	if (!myWasDead)
	{
		myIsDead = true;
		if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eDeathL);
		else PlaySpecificAnimation(EPlayerAnimationClips::eDeathR);
	}
}

void Player::PlayAnimation(EAnimationState anAnimEnum)
{
	//printf("%d", myDirection);

	for (auto& anim : myAnimations)
	{
		if (anim->GetAnimIsDone())
		{
			if (anim->GetAnimationTypeIndex() == (int)anAnimEnum * 2 + (myDirection < 0)) return;
			int enumer = (int)anAnimEnum * 2 + (myDirection < 0);
			myAnimations[enumer]->PlayAnimLoop();
			return;
		}
		else if (anim->GetAnimIsPlaying() && anim->GetAnimIsLooping())
		{
			if (anim->GetAnimationTypeIndex() == (int)anAnimEnum * 2 + (myDirection < 0)) return;

			anim->Deactivate();

			if (myDirection > 0)
			{
				int enumer = (int)anAnimEnum * 2;
				myAnimations[enumer]->PlayAnimLoop();
				return;
			}
			if (myDirection < 0)
			{
				int enumer = (int)anAnimEnum * 2 + 1;

				myAnimations[enumer]->PlayAnimLoop();
				return;
			}
		}
	}
	myAnimations[0]->PlayAnimLoop();
}

void Player::PlaySpecificAnimation(EPlayerAnimationClips anAnimEnum)
{
	for (auto& anim : myAnimations)
	{
		anim->Deactivate();
	}
	myAnimations[(int)anAnimEnum]->PlayAnimOnce();
}