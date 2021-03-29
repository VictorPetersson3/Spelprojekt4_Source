#include "stdafx.h"
#include "Player.h"

#include "AnimationClip.h"
#include "Camera.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "JsonParser.h"
#include "RenderCommand.h"
#include "Timer.h"
#include "XController.h"

#define INPUT InputManagerS::GetInstance() 
#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

Player::Player(EPowerUp aPowerup) : 
	myCurrentPower(aPowerup) ,
	myController(1)
{
}
Player::~Player(){}

void Player::Init(CommonUtilities::Vector2f aPosition, EPowerUp aPower)
{
	if (myController.IsConnected())
	{
		ChangeInput(EInputType::Controller);
	}

	myAnimations.clear();
	
	myCurrentPower = aPower;
	myPosition = aPosition;

	myIsDead = false;
	myWasDead = false;
	myMoveState = EPlayerState::Idle;

	InitJSON();

	InitAnimations();

	InitCollider();
}

void Player::Render(Camera& aCamera)
{
	int thing = (int)myCurrentAnimation * 2 + (myDirection < 0);
	aCamera.RenderSprite(myAnimations[thing]->GetRenderCommand());
}

void Player::InitJSON()
{
	JsonParser parser;
	auto doc = parser.GetDocument("Json/Player.json");

	myWalkSpeed = doc["Walking and running"]["Speed"].GetFloat();
	myWalkDecceleration = doc["Walking and running"]["Decceleration"].GetFloat();

	myJumpSpeed = doc["Jumping"]["Speed"].GetFloat();
	myJumpDecceleration = doc["Jumping"]["Decceleration"].GetFloat();

	myWallJumpSpeed = doc["Wall stuff"]["Jump speed"].GetFloat();
	myWallJumpFactorX = doc["Wall stuff"]["X factor"].GetFloat();;
	myWallDrag = doc["Wall stuff"]["Wall drag"].GetFloat();
	myMaxWallSlideSpeed = doc["Wall stuff"]["Maximum wall slide speed"].GetFloat();;

	myAirAcceleration = doc["Air time"]["Acceleration"].GetFloat();
	myAirDecceleration = doc["Air time"]["Decceleration"].GetFloat();
	myMaxAirSpeed = doc["Air time"]["Maximum speed"].GetFloat();

	myMaxHorizontalVelocity = doc["Maximum velocities and gravity"]["Maximum horizontal velocity"].GetFloat();
	myMaxVerticalVelocity = doc["Maximum velocities and gravity"]["Maximum vertical velocity"].GetFloat();
	myGravity = doc["Maximum velocities and gravity"]["Gravity"].GetFloat();
	myBoostFactor = doc["Maximum velocities and gravity"]["Boost multiplier"].GetFloat();
	myGlideSpeed = doc["Maximum velocities and gravity"]["Glide falling speed"].GetFloat();

	mySize =
	{
		doc["Collider"]["Size in pixels"]["X"].GetFloat() / (float)Tga2D::CEngine::GetInstance()->GetRenderSize().x,
		doc["Collider"]["Size in pixels"]["Y"].GetFloat() / (float)Tga2D::CEngine::GetInstance()->GetRenderSize().y
	};
}

void Player::InitAnimations()
{
	std::string folder = "sprites/Player/State" + std::to_string((int)myCurrentPower);
	//printf(folder.c_str());

	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_idle_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eIdleR));
	myAnimations[0]->Init({ 8, 1 }, { 7, 1 });				
	myAnimations[0]->PlayAnimLoop();								
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_idle_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eIdleL));
	myAnimations[1]->Init({ 8, 1 }, { 7, 1 });				 
	myAnimations[1]->PlayAnimLoop();								 
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_run_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eRunR));
	myAnimations[2]->Init({ 8, 1 }, { 5, 1 });				
	myAnimations[2]->PlayAnimLoop();								
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_run_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eRunL));
	myAnimations[3]->Init({ 8, 1 }, { 5, 1 });				
	myAnimations[3]->PlayAnimLoop();								
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_sprint_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eSprintR));
	myAnimations[4]->Init({ 8, 1 }, { 5, 1 });				 
	myAnimations[4]->PlayAnimLoop();								 
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_sprint_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eSprintL));
	myAnimations[5]->Init({ 8, 1 }, { 5, 1 });				
	myAnimations[5]->PlayAnimLoop();								
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_jump_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eJumpR));
	myAnimations[6]->Init({ 8, 1 }, { 5, 1 });			
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_jump_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eJumpL));
	myAnimations[7]->Init({ 8, 1 }, { 5, 1 });				
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_land_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eLandR));
	myAnimations[8]->Init({ 8, 1 }, { 5, 1 });			
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_land_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eLandL));
	myAnimations[9]->Init({ 8, 1 }, { 5, 1 });			
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_wallidle_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eWallIdleR));
	myAnimations[10]->Init({ 4, 1 }, { 4, 1 });			 
	myAnimations[10]->PlayAnimLoop();						 
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_wallidle_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eWallIdleL));
	myAnimations[11]->Init({ 4, 1 }, { 4, 1 });				
	myAnimations[11]->PlayAnimLoop();							
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_wallDown_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eWallDownR));
	myAnimations[12]->Init({ 4, 1 }, { 4, 1 });			
	myAnimations[12]->PlayAnimLoop();						
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_wallDown_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eWallDownL));
	myAnimations[13]->Init({ 4, 1 }, { 4, 1 });				
	myAnimations[13]->PlayAnimLoop();							
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_wallUp_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eWallUpR));
	myAnimations[14]->Init({ 4, 1 }, { 4, 1 });				 
	myAnimations[14]->PlayAnimLoop();							 
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_wallUp_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eWallUpL));
	myAnimations[15]->Init({ 4, 1 }, { 4, 1 });			
	myAnimations[15]->PlayAnimLoop();						
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_wallJump_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eWallJumpR));
	myAnimations[16]->Init({ 8, 1 }, { 6, 1 });				
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_wallJump_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eWallJumpL));
	myAnimations[17]->Init({ 8, 1 }, { 6, 1 });				 
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_death_R.dds").c_str(), 0, (int)EPlayerAnimationClips::eDeathR));
	myAnimations[18]->Init({ 16, 1 }, { 9, 1 });				
	myAnimations.push_back(std::make_shared<AnimationClip>((folder + "/player_death_L.dds").c_str(), 0, (int)EPlayerAnimationClips::eDeathL));
	myAnimations[19]->Init({ 16, 1 }, { 9, 1 });

	switch (myCurrentPower)
	{
	case EPowerUp::DoubleJump:
		myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State2/player_doubleJump_R.dds", 0, (int)EPlayerAnimationClips::eDoubleJumpR));
		myAnimations[20]->Init({ 16, 1 }, { 9, 1 });
		myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State2/player_doubleJump_L.dds", 0, (int)EPlayerAnimationClips::eDoubleJumpL));
		myAnimations[21]->Init({ 16, 1 }, { 9, 1 });
		break;
	case EPowerUp::Glide:
		myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State3/player_glidflyg_R.dds", 0, (int)EPlayerAnimationClips::eGlideR));
		myAnimations[20]->Init({ 16, 1 }, { 9, 1 });
		myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State3/player_glidflyg_L.dds", 0, (int)EPlayerAnimationClips::eGlideL));
		myAnimations[21]->Init({ 16, 1 }, { 9, 1 });
		break;
	}
}

void Player::InitCollider()
{
	myCollider = std::make_shared<Collider>(myPosition, mySize.x/* * (9.0f / 16.0f)*/, mySize.y);
	myCollider->SetTag(EColliderTag::Player);
}

bool Player::Input(int anInput)
{
	switch (anInput)
	{
	case DIK_UP: case DIK_LEFT: case DIK_DOWN: case DIK_RIGHT: case DIK_X: case DIK_Z:
	case DIK_W: case DIK_A: case DIK_S: case DIK_D: case DIK_SPACE: case DIK_LSHIFT:
		return INPUT.GetKey(anInput);
		break;
	case XINPUT_GAMEPAD_DPAD_UP:
		return myController.GetLeftTumbStick().y > 0 || myController.GetDPadInput().y > 0;
	case XINPUT_GAMEPAD_DPAD_LEFT:
		return myController.GetLeftTumbStick().x < 0 || myController.GetDPadInput().x < 0;
	case XINPUT_GAMEPAD_DPAD_DOWN:
		return myController.GetLeftTumbStick().y < 0 || myController.GetDPadInput().y < 0;
	case XINPUT_GAMEPAD_DPAD_RIGHT:
		return myController.GetLeftTumbStick().x > 0 || myController.GetDPadInput().x > 0;
	case XINPUT_GAMEPAD_A:
		return myController.IsButton_A_Pressed();
	case XINPUT_GAMEPAD_B:
		return (myController.IsButton_B_Pressed() || myController.IsButton_X_Pressed());
	}
}

//temp
void Player::ChangePower()
{
	if (INPUT.GetKeyDown(DIK_1) && myCurrentPower != EPowerUp::Default)
	{
		myCurrentPower = EPowerUp::Default;
	}
	if (INPUT.GetKeyDown(DIK_2) && myCurrentPower != EPowerUp::DoubleJump)
	{
		myCurrentPower = EPowerUp::DoubleJump;
	}
	if (INPUT.GetKeyDown(DIK_3) && myCurrentPower != EPowerUp::Glide)
	{
		myCurrentPower = EPowerUp::Glide;
	}
}

void Player::Update()
{
	//Sleep(1);
	ChangePower();

	UpdateJumping();

	ManageStates();
	
	UpdatePhysics();

	HandleAnimations();
}

void Player::HandleAnimations()
{
	for (auto& anim : myAnimations)
	{
		anim->UpdateAnimation(myPosition);
	}
}

CommonUtilities::Vector2f Player::GetPosition() const
{
	return myPosition;
}

CommonUtilities::Vector2f& Player::GetCurrentVelocity()
{
	return myCurrentVelocity;
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
		myUp    = DIK_UP;
		myLeft  = DIK_LEFT;
		myDown  = DIK_DOWN;
		myRight = DIK_RIGHT;
		myJump  = DIK_X;
		myBoost = DIK_Z;
		break;
	case EInputType::WASD:
		myUp    = DIK_W;
		myLeft  = DIK_A;
		myDown  = DIK_S;
		myRight = DIK_D;
		myJump  = DIK_SPACE;
		myBoost = DIK_LSHIFT;
		break;
	case EInputType::Controller:
		myUp    = XINPUT_GAMEPAD_DPAD_UP;
		myLeft  = XINPUT_GAMEPAD_DPAD_LEFT;
		myDown  = XINPUT_GAMEPAD_DPAD_DOWN;
		myRight = XINPUT_GAMEPAD_DPAD_RIGHT;
		myJump  = XINPUT_GAMEPAD_A;
		myBoost = XINPUT_GAMEPAD_B;
		break;
	}
}

void Player::UpdateJumping()
{
	if (myIsGrounded) myCanDoubleJump = true;
	if (!Input(myJump)) // kanske buggar här
	{
		myCanJumpAgain = true;
		myIsGliding = false;
		myCanGlide = true;
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
			continue;
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

		positionCorrection *= posCorrNormal;

		if (posCorrNormal.y > 0)
		{
			myPosition.y += positionCorrection.y;
			myCurrentVelocity.y = 0;
			myIsRoofied = true;
		}
		else if (posCorrNormal.y < 0)
		{
			myPosition.y += positionCorrection.y;
			myIsGrounded = true;
		}
		else
		{
			myIsGrounded = false;
			myIsRoofied = false;
		}
		if (posCorrNormal.x > 0 &&
			myCollider->GetPosition().y < horizontalCollider->GetPosition().y + horizontalCollider->GetSize().y * 0.5f &&
			myCollider->GetPosition().y > horizontalCollider->GetPosition().y - horizontalCollider->GetSize().y * 0.5f)
		{
			myPosition.x += positionCorrection.x;
			if (myCurrentVelocity.x < 0) myHugsLeftWall = true;
		}
		else if (posCorrNormal.x < 0 &&
			myCollider->GetPosition().y < horizontalCollider->GetPosition().y + horizontalCollider->GetSize().y * 0.5f &&
			myCollider->GetPosition().y > horizontalCollider->GetPosition().y - horizontalCollider->GetSize().y * 0.5f)
		{
			myPosition.x += positionCorrection.x;
			if (myCurrentVelocity.x > 0) myHugsRightWall = true;
		}
		else
		{
			myHugsLeftWall = false;
			myHugsRightWall = false;
		}
	}
	else
	{
		myIsGrounded = false;
		myIsRoofied = false;
		myHugsLeftWall = false;
		myHugsRightWall = false;
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

	if (myCurrentVelocity.x > 0) myCurrentVelocity.x -= myWalkDecceleration * DELTA_TIME;
	if (myCurrentVelocity.x < 0) myCurrentVelocity.x += myWalkDecceleration * DELTA_TIME;

	myCurrentAnimation = EAnimationState::Idle;

	if (!myIsGrounded)
	{
		myMoveState = EPlayerState::Falling;
		return;
	}
	if (Input(myLeft) != Input(myRight))
	{
		myMoveState = EPlayerState::Walk;
		return;
	}
	else if (Input(myJump) && myCanJumpAgain)
	{
		myCurrentVelocity.y = -myJumpSpeed;
		if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eJumpL);
		else PlaySpecificAnimation(EPlayerAnimationClips::eJumpR);
		myMoveState = EPlayerState::Falling;

		myCanJumpAgain = false;
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

	if (Input(myLeft) == Input(myRight))
	{
		myMoveState = EPlayerState::Idle;
		return;
	}
	else if (Input(myRight))
	{
		myDirection = 1;
		if (myHugsRightWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			if (Input(myBoost))
			{
				myCurrentAnimation = EAnimationState::Sprint;
				if (myCurrentVelocity.x <= myMaxAirSpeed * myBoostFactor) myCurrentVelocity.x += myWalkSpeed * DELTA_TIME * myBoostFactor;
			}
			else if (myCurrentVelocity.x <= myMaxHorizontalVelocity) myCurrentVelocity.x += myWalkSpeed * DELTA_TIME;
		}
	}
	else if (Input(myLeft))
	{
		myDirection = -1;
		if (myHugsLeftWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		else
		{
			if (Input(myBoost))
			{
				myCurrentAnimation = EAnimationState::Sprint;
				if (myCurrentVelocity.x >= -myMaxAirSpeed * myBoostFactor) myCurrentVelocity.x -= myWalkSpeed * DELTA_TIME * myBoostFactor;
			}
			else if (myCurrentVelocity.x >= -myMaxHorizontalVelocity) myCurrentVelocity.x -= myWalkSpeed * DELTA_TIME;
		}
	}

	if (Input(myJump) && myCanJumpAgain)
	{
		myCurrentVelocity.y = -myJumpSpeed;
		myMoveState = EPlayerState::Falling;

		if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eJumpL);
		else PlaySpecificAnimation(EPlayerAnimationClips::eJumpR);
		
		myCanJumpAgain = false;
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
	if (myHuggedLeftWall || myHuggedRightWall) myCurrentAnimation = EAnimationState::W_Jump;
	else myCurrentAnimation = EAnimationState::Jump;

	if (myCurrentVelocity.y >= myMaxVerticalVelocity) myCurrentVelocity.y = myMaxVerticalVelocity;
	else if (myIsGliding) myCurrentVelocity.y = myGlideSpeed;
	else myCurrentVelocity.y += myGravity * DELTA_TIME;

	if (Input(myLeft) == Input(myRight))
	{
		if (myIsGrounded) myMoveState = EPlayerState::Idle;
		if (myCurrentVelocity.x > 0) myCurrentVelocity.x -= myAirDecceleration * DELTA_TIME;
		if (myCurrentVelocity.x < 0) myCurrentVelocity.x += myAirDecceleration * DELTA_TIME;
	}
	else if (Input(myRight))
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
			if (Input(myBoost))
			{
				if (myCurrentVelocity.x <= myMaxAirSpeed * myBoostFactor) myCurrentVelocity.x += myAirAcceleration * DELTA_TIME * myBoostFactor;
			}
			else if (myCurrentVelocity.x <= myMaxAirSpeed) myCurrentVelocity.x += myAirAcceleration * DELTA_TIME;
		}
	}
	else if (Input(myLeft))
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
			if (Input(myBoost))
			{
				if (myCurrentVelocity.x >= -myMaxAirSpeed * myBoostFactor) myCurrentVelocity.x -= myAirAcceleration * DELTA_TIME * myBoostFactor;
			}
			else if (myCurrentVelocity.x >= -myMaxAirSpeed) myCurrentVelocity.x -= myAirAcceleration * DELTA_TIME;
		}
	}

	switch (myCurrentPower)
	{
	case EPowerUp::DoubleJump:
		if (Input(myJump) && myCanDoubleJump && myCanJumpAgain)
		{
			myCurrentVelocity.y = -myJumpSpeed;

		/*	if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eDoubleJumpL);
			else PlaySpecificAnimation(EPlayerAnimationClips::eDoubleJumpR);*/

			myCanDoubleJump = false;
			myCanJumpAgain = false;
		}
		break;
	case EPowerUp::Glide:
		if (Input(myJump) && myCanGlide && myCurrentVelocity.y > 0.0f && myCanJumpAgain)
		{
			//myCurrentAnimation = EAnimationState::Glide;

			myIsGliding = true;
			myCanGlide = false;
		}
		break;
	default:
		break;
	}
	if (!Input(myJump) && myCurrentVelocity.y < 0.0f)
	{
		myCurrentVelocity.y += myJumpDecceleration * DELTA_TIME;
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

   if (myCurrentVelocity.y < 0) myCurrentVelocity.y += myWallDrag * DELTA_TIME;
	myCurrentVelocity.y += myGravity * DELTA_TIME;
	if (myCurrentVelocity.y >= myMaxWallSlideSpeed) myCurrentVelocity.y = myMaxWallSlideSpeed;


	if (Input(myLeft) == Input(myRight))
	{
		myCurrentVelocity.x = 0;
		myMoveState = EPlayerState::Idle;
	}
	else if (Input(myRight))
	{
		myDirection = 1;

		if (myHugsRightWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		if (Input(myJump) && myCanJumpAgain && !myIsGliding)
		{
			myCurrentVelocity.x = -myWallJumpSpeed * myWallJumpFactorX;
			myCurrentVelocity.y = -myWallJumpSpeed;

			PlaySpecificAnimation(EPlayerAnimationClips::eWallJumpL);

			myMoveState = EPlayerState::Falling;
			
			myCanJumpAgain = false;
			return;
		}
	}
	else if (Input(myLeft))
	{
		myDirection = -1;
		if (myHugsLeftWall)
		{
			myCurrentVelocity.x = 0.0f;
		}
		if (Input(myJump) && myCanJumpAgain && !myIsGliding)
		{
			myCurrentVelocity.x = myWallJumpSpeed * myWallJumpFactorX;
			myCurrentVelocity.y = -myWallJumpSpeed;

			PlaySpecificAnimation(EPlayerAnimationClips::eWallJumpR);

			myMoveState = EPlayerState::Falling;
			myCurrentAnimation = EAnimationState::W_Jump;
			
			myCanJumpAgain = false;
			return;
		}
	}
}

void Player::Die()
{
	if (!myWasDead)
	{
		myIsDead = true;
		myCurrentVelocity.x = 0;

		myCurrentAnimation = EAnimationState::Death;

		if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eDeathL);
		else PlaySpecificAnimation(EPlayerAnimationClips::eDeathR);

		myDeathTimer = Timer::GetInstance().GetTotalTime();
	}
}

void Player::PlaySpecificAnimation(EPlayerAnimationClips anAnimEnum)
{
	if (anAnimEnum == EPlayerAnimationClips::eJumpL ||
		anAnimEnum == EPlayerAnimationClips::eJumpR ||
		anAnimEnum == EPlayerAnimationClips::eWallJumpL ||
		anAnimEnum == EPlayerAnimationClips::eWallJumpR)
		myAnimations[(int)anAnimEnum]->PlayAnimOnce(0.1666666666666667f);
	else myAnimations[(int)anAnimEnum]->PlayAnimOnce();
}