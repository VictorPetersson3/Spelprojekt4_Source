#include "stdafx.h"
#include "Player.h"

#include "AnimationClip.h"
#include "AudioManager.h"
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

Player::Player(std::shared_ptr<XController> aController, EPowerUp aPowerup) :
	myCurrentPower(aPowerup),
	myController(aController)
{
}
Player::~Player() {}

void Player::Init(CommonUtilities::Vector2f aPosition, EPowerUp aPower)
{
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

	// Sound
	for (auto& ele : mySounds)
	{
		ele = "Audio/Player/";
	}
	mySounds[0] += doc["Audio"]["Looping"][0]["Running"].GetString();
	mySounds[1] = doc["Audio"]["Looping"][1]["Sprinting"].GetString();
	mySounds[2] = doc["Audio"]["Looping"][2]["Gliding"].GetString();
	mySounds[3] = doc["Audio"]["Looping"][3]["Wall sliding"].GetString();

	mySounds[4] = doc["Audio"]["One shot"][0]["Jump"].GetString();
	mySounds[5] = doc["Audio"]["One shot"][1]["Double jump"].GetString();
	mySounds[6] = doc["Audio"]["One shot"][2]["Wall jump"].GetString();
	mySounds[7] = doc["Audio"]["One shot"][3]["Landing"].GetString();

	mySounds[8] = doc["Audio"]["Death by"][0]["Snail"].GetString();
	mySounds[9] = doc["Audio"]["Death by"][1]["Lava"].GetString();
	mySounds[10] = doc["Audio"]["Death by"][2]["Saw"].GetString();
	mySounds[11] = doc["Audio"]["Death by"][3]["Lizard"].GetString();

	printf("\"");
	printf(mySounds[0].c_str());
	printf("\"");
	printf("\n");
}

void Player::InitAnimations()
{
	std::string folder = "sprites/Player/State" + std::to_string((int)myCurrentPower);

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
		myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State2/player_doubleJump_R.dds", 0, (int)EPlayerAnimationClips::ePowerR));
		myAnimations[20]->Init({ 4, 1 }, { 4, 1 });
		myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State2/player_doubleJump_L.dds", 0, (int)EPlayerAnimationClips::ePowerL));
		myAnimations[21]->Init({ 4, 1 }, { 4, 1 });
		break;
	case EPowerUp::Glide:
		myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State3/player_glidflyg_R.dds", 0, (int)EPlayerAnimationClips::ePowerR));
		myAnimations[20]->Init({ 4, 1 }, { 3, 1 });
		myAnimations[20]->PlayAnimLoop();
		myAnimations.push_back(std::make_shared<AnimationClip>("sprites/Player/State3/player_glidflyg_L.dds", 0, (int)EPlayerAnimationClips::ePowerL));
		myAnimations[21]->Init({ 4, 1 }, { 3, 1 });
		myAnimations[21]->PlayAnimLoop();
		break;
	}
}

void Player::InitCollider()
{
	float resolutionscale = (Tga2D::CEngine::GetInstance()->GetRenderSize().x / 1280.0f);
	myCollider = std::make_shared<Collider>(myPosition, mySize.x * resolutionscale, mySize.y * resolutionscale);
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
		return myController->GetLeftTumbStick().y > 0 || myController->GetDPadInput().y > 0;
	case XINPUT_GAMEPAD_DPAD_LEFT:
		return myController->GetLeftTumbStick().x < 0 || myController->GetDPadInput().x < 0;
	case XINPUT_GAMEPAD_DPAD_DOWN:
		return myController->GetLeftTumbStick().y < 0 || myController->GetDPadInput().y < 0;
	case XINPUT_GAMEPAD_DPAD_RIGHT:
		return myController->GetLeftTumbStick().x > 0 || myController->GetDPadInput().x > 0;
	case XINPUT_GAMEPAD_A:
		return myController->IsButton_A_Pressed();
	case XINPUT_GAMEPAD_B:
		return (myController->IsButton_B_Pressed() || myController->IsButton_X_Pressed());
	}
}

void Player::Action(EAnimationState anAnimState)
{
	switch (anAnimState)
	{
	case EAnimationState::Jump:
		myIsGrounded = false;
		myCurrentVelocity.y = -myJumpSpeed;
		if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eJumpL);
		else PlaySpecificAnimation(EPlayerAnimationClips::eJumpR);
		myMoveState = EPlayerState::Falling;

		myCanJumpAgain = false;
		break;
	case EAnimationState::Power:
		switch (myCurrentPower)
		{
		case EPowerUp::DoubleJump:
			if (Input(myJump) && myCanDoubleJump && myCanJumpAgain)
			{
				myCurrentVelocity.y = -myJumpSpeed;

				myCurrentAnimation = EAnimationState::Power;
				if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::ePowerL);
				else PlaySpecificAnimation(EPlayerAnimationClips::ePowerR);

				myCanDoubleJump = false;
				myCanJumpAgain = false;
			}
			break;
		case EPowerUp::Glide:
			if (Input(myJump) && myCanGlide && myCurrentVelocity.y > 0.0f && myCanJumpAgain)
			{
				myCurrentAnimation = EAnimationState::Power;

				myIsGliding = true;
				myCanGlide = false;
			}
			break;
		default:
			break;
		}
		break;
	case EAnimationState::W_Jump:
		if (myDirection)
		{
			myCurrentVelocity.x = -myWallJumpSpeed * myWallJumpFactorX;
			myCurrentVelocity.y = -myWallJumpSpeed;

			PlaySpecificAnimation(EPlayerAnimationClips::eWallJumpL);

			myMoveState = EPlayerState::Falling;

			myCanJumpAgain = false;
		}
		else
		{
			myCurrentVelocity.x = myWallJumpSpeed * myWallJumpFactorX;
			myCurrentVelocity.y = -myWallJumpSpeed;

			PlaySpecificAnimation(EPlayerAnimationClips::eWallJumpR);

			myMoveState = EPlayerState::Falling;
			myCurrentAnimation = EAnimationState::W_Jump;

			myCanJumpAgain = false;
		}
		break;
	case EAnimationState::Death:
		if (!myWasDead)
		{
			myIsDead = true;

			myCurrentAnimation = EAnimationState::Death;

			if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eDeathL);
			else PlaySpecificAnimation(EPlayerAnimationClips::eDeathR);



			myDeathTimer = Timer::GetInstance().GetTotalTime();
		}
		break;
	}
}

void Player::Update()
{
	//Sleep(1);

	UpdateJumping();

	ManageStates();

	UpdatePhysics();

	HandleAnimations();

	HandleAudio();
}

void Player::HandleAnimations()
{
	for (auto& anim : myAnimations)
	{
		anim->UpdateAnimation(myPosition);
	}
}

void Player::HandleAudio()
{
	int index = -1;
	switch (myCurrentAnimation)
	{
	case EAnimationState::Run:
		index = 0;
		break;
	case EAnimationState::Sprint:
		index = 1;
		break;
	case EAnimationState::Power:
		if (myCurrentPower == EPowerUp::Glide) index = 2;
		break;
	case EAnimationState::W_Down: case EAnimationState::W_Up:
		index = 3;
		break;
	}

	if (!(index < 0) && mySounds[index] != "Audio/Player/" && !AudioManager::GetInstance().IsEffectCurrentlyPlaying(mySounds[index].c_str()))
	{
		for (int i = 0; i < 4; i++)
		{
			AudioManager::GetInstance().StopEffectSound(mySounds[i].c_str());
		}
		AudioManager::GetInstance().PlayEffect(mySounds[index].c_str(), true);
	}
	else if (index < 0)
	{
		for (int i = 0; i < 4; i++)
		{
			AudioManager::GetInstance().StopEffectSound(mySounds[i].c_str());
		}
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

void Player::SetShouldUpdatePhysics(bool aState)
{
	myShouldUpdatePhysics = aState;
}

std::shared_ptr<Collider> Player::GetCollider()
{
	return myCollider;
}

void Player::ChangeInput()
{
	EInputType inputType;

	if (INPUT.GetKey(DIK_UP) || INPUT.GetKey(DIK_LEFT) || INPUT.GetKey(DIK_DOWN) || INPUT.GetKey(DIK_RIGHT) || INPUT.GetKey(DIK_Z) || INPUT.GetKey(DIK_X))
		inputType = EInputType::ArrowKeys;
	else if (INPUT.GetKey(DIK_W) || INPUT.GetKey(DIK_A) || INPUT.GetKey(DIK_S) || INPUT.GetKey(DIK_D) || INPUT.GetKey(DIK_SPACE) || INPUT.GetKey(DIK_LSHIFT))
		inputType = EInputType::WASD;
	else if (INPUT.GetKey(XINPUT_GAMEPAD_DPAD_UP) || INPUT.GetKey(XINPUT_GAMEPAD_DPAD_LEFT) || INPUT.GetKey(XINPUT_GAMEPAD_DPAD_DOWN) || INPUT.GetKey(XINPUT_GAMEPAD_DPAD_RIGHT) || INPUT.GetKey(XINPUT_GAMEPAD_A) || INPUT.GetKey(XINPUT_GAMEPAD_B) || INPUT.GetKey(XINPUT_GAMEPAD_X))
		inputType = EInputType::Controller;

	switch (inputType)
	{
	case EInputType::ArrowKeys:
		myUp = DIK_UP;
		myLeft = DIK_LEFT;
		myDown = DIK_DOWN;
		myRight = DIK_RIGHT;
		myJump = DIK_X;
		myBoost = DIK_Z;
		break;
	case EInputType::WASD:
		myUp = DIK_W;
		myLeft = DIK_A;
		myDown = DIK_S;
		myRight = DIK_D;
		myJump = DIK_SPACE;
		myBoost = DIK_LSHIFT;
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

void Player::UpdateJumping()
{
	if (myIsGrounded) myCanDoubleJump = true;
	if (!Input(myJump)) // kanske buggar h�r
	{
		myCanJumpAgain = true;
		myIsGliding = false;
		myCanGlide = true;
	}
}

void Player::UpdatePhysics()
{
	if (!myShouldUpdatePhysics) return;

	CacheCurrentValues();
	myPosition += myCurrentVelocity * DELTA_TIME;

	CollisionManager::GetInstance().Update();

	CommonUtilities::Vector2f normal;
	CommonUtilities::Vector2f positionCorrection;
	CommonUtilities::Vector2f posCorrNormal;

	Collider* verticalCollider = nullptr;
	Collider* horizontalCollider = nullptr;

	/*myHugsLeftWall = false;
	myHugsRightWall = false;*/

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
			if ((verticalCollider->GetPosition() - myCollider->GetPosition()).Length() > (myCollider->GetCollidedWith()[i]->GetPosition() - myCollider->GetPosition()).Length())
				verticalCollider = myCollider->GetCollidedWith()[i];
		}
		else if (verticalCollider == nullptr && normal.y != 0)
		{
			verticalCollider = myCollider->GetCollidedWith()[i];
		}
		if (horizontalCollider != nullptr && normal.x != 0)
		{
			if ((horizontalCollider->GetPosition() - myCollider->GetPosition()).Length() > (myCollider->GetCollidedWith()[i]->GetPosition() - myCollider->GetPosition()).Length())
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

		float resolutionscale = (Tga2D::CEngine::GetInstance()->GetRenderSize().x / 1280.0f);

		positionCorrection *= resolutionscale;
		positionCorrection *= posCorrNormal;
		positionCorrection.x += 0.1f / Tga2D::CEngine::GetInstance()->GetRenderSize().x * -posCorrNormal.x;

		if (posCorrNormal.y > 0)
		{
			myPosition.y += positionCorrection.y;
			if (myWasRoofied && myCurrentVelocity.y < 0) myCurrentVelocity.y = 0;
			myIsRoofied = true;
		}
		else if (posCorrNormal.y < 0)
		{
			myPosition.y += positionCorrection.y + 0.1f / Tga2D::CEngine::GetInstance()->GetRenderSize().y;
			if (myWasGrounded && myCurrentVelocity.y > 0) myCurrentVelocity.y = 0;
			myIsGrounded = true;
		}
		else
		{
			myIsGrounded = false;
			myIsRoofied = false;
		}
		if (posCorrNormal.x > 0 &&
			myCollider->GetPosition().y <= horizontalCollider->GetPosition().y + horizontalCollider->GetSize().y &&
			myCollider->GetPosition().y >= horizontalCollider->GetPosition().y - horizontalCollider->GetSize().y)
		{
			myPosition.x += positionCorrection.x;
			if (myHuggedLeftWall && myCurrentVelocity.x < 0) myCurrentVelocity.x = 0;
			/*if (myCurrentVelocity.x < 0) */myHugsLeftWall = true;
		}
		else if (posCorrNormal.x < 0 &&
			myCollider->GetPosition().y <= horizontalCollider->GetPosition().y + horizontalCollider->GetSize().y &&
			myCollider->GetPosition().y >= horizontalCollider->GetPosition().y - horizontalCollider->GetSize().y)
		{
			myPosition.x += positionCorrection.x;
			if (myHuggedRightWall && myCurrentVelocity.x > 0) myCurrentVelocity.x = 0;
			/*if (myCurrentVelocity.x > 0) */myHugsRightWall = true;
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
	if (!myWasGrounded && myIsGrounded)
	{
		if (myDirection < 0) PlaySpecificAnimation(EPlayerAnimationClips::eLandL);
		else PlaySpecificAnimation(EPlayerAnimationClips::eLandR);
	}

	if (myCurrentVelocity.x > 0) myCurrentVelocity.x -= myWalkDecceleration * DELTA_TIME;
	if (myCurrentVelocity.x < 0) myCurrentVelocity.x += myWalkDecceleration * DELTA_TIME;
	if (myCurrentVelocity.x <= myWalkDecceleration * DELTA_TIME && myCurrentVelocity.x >= -myWalkDecceleration * DELTA_TIME) myCurrentVelocity.x = 0;

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
		Action(EAnimationState::Jump);
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
		Idle();
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
		Action(EAnimationState::Jump);
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
	else if (myIsGliding || !myCanDoubleJump) myCurrentAnimation = EAnimationState::Power;
	else if (!myIsGrounded && !myHugsLeftWall && !myHugsRightWall) myCurrentAnimation = EAnimationState::Jump;

	if (myCurrentVelocity.y >= myMaxVerticalVelocity) myCurrentVelocity.y = myMaxVerticalVelocity;
	else if (myIsGliding) myCurrentVelocity.y = myGlideSpeed;
	else myCurrentVelocity.y += myGravity * DELTA_TIME;

	if (Input(myLeft) == Input(myRight))
	{
		if (myIsGrounded)
		{
			myMoveState = EPlayerState::Idle;
			return;
		}
		if (myCurrentVelocity.x > 0) myCurrentVelocity.x -= myAirDecceleration * DELTA_TIME;
		if (myCurrentVelocity.x < 0) myCurrentVelocity.x += myAirDecceleration * DELTA_TIME;
	}
	else if (Input(myRight))
	{
		myDirection = 1;

		//if (myIsGrounded && !myHugsLeftWall && !myHugsRightWall) myMoveState = EPlayerState::Walk;
		if (myIsGrounded) myMoveState = EPlayerState::Walk;
		if (myHugsRightWall && !myIsGrounded && !myWasGrounded)
		{
			myMoveState = EPlayerState::Ledge;
			return;
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
			return;
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

	Action(EAnimationState::Power);

	if (!Input(myJump) && myCurrentVelocity.y < 0.0f)
	{
		myCurrentVelocity.y += myJumpDecceleration * DELTA_TIME;
	}
}

void Player::Ledge()
{
	if (myIsGrounded)
	{
		myMoveState = EPlayerState::Walk;  // ta bort om han ska chilla p� v�ggen n�r han har glidit ned
		return;
	}

	if (INPUT.GetKey(myLeft) != INPUT.GetKey(myRight))
	{
		if (myCurrentVelocity.y == 0) myCurrentAnimation = EAnimationState::W_Idle;
		else if (myCurrentVelocity.y > 0) myCurrentAnimation = EAnimationState::W_Down;
		else if (myCurrentVelocity.y < 0) myCurrentAnimation = EAnimationState::W_Up;
	}
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
	}
	else if (Input(myLeft))
	{
		myDirection = -1;
	}

	if (myHugsRightWall || myHugsLeftWall)
	{
		myCurrentVelocity.x = 0.0f;
	}
	else
	{
		myMoveState = EPlayerState::Falling;
		return;
	}
	if (Input(myJump) && myCanJumpAgain && !myIsGliding)
	{
		Action(EAnimationState::W_Jump);
		return;
	}

}

void Player::Die()
{
	myCurrentVelocity.y += myGravity * DELTA_TIME;
	if (myIsGrounded)
	{
		if (myCurrentVelocity.x > 0) myCurrentVelocity.x -= myWalkDecceleration * DELTA_TIME;
		else if (myCurrentVelocity.x < 0) myCurrentVelocity.x += myWalkDecceleration * DELTA_TIME;
		if (myCurrentVelocity.x <= myWalkDecceleration * DELTA_TIME && myCurrentVelocity.x >= -myWalkDecceleration * DELTA_TIME) myCurrentVelocity.x = 0;
	}
	else
	{
		if (myCurrentVelocity.x > 0) myCurrentVelocity.x -= myAirDecceleration * DELTA_TIME;
		else if (myCurrentVelocity.x < 0) myCurrentVelocity.x += myAirDecceleration * DELTA_TIME;
		if (myCurrentVelocity.x <= myAirDecceleration * DELTA_TIME && myCurrentVelocity.x >= -myAirDecceleration * DELTA_TIME) myCurrentVelocity.x = 0;
	}
	Action(EAnimationState::Death);
}

void Player::PlaySpecificAnimation(EPlayerAnimationClips anAnimEnum)
{
	if (anAnimEnum == EPlayerAnimationClips::ePowerL ||
		anAnimEnum == EPlayerAnimationClips::ePowerR ||
		anAnimEnum == EPlayerAnimationClips::eWallJumpL ||
		anAnimEnum == EPlayerAnimationClips::eWallJumpR)
		myAnimations[(int)anAnimEnum]->PlayAnimOnce(0.1666666666666667f);
	else if (anAnimEnum == EPlayerAnimationClips::eDeathL ||
		anAnimEnum == EPlayerAnimationClips::eDeathR)
		myAnimations[(int)anAnimEnum]->PlayAnimOnce(0.125f);
	else myAnimations[(int)anAnimEnum]->PlayAnimOnce();
}

void Player::PlaySpecificAudio(EAnimationState anAnimState)
{
	switch (anAnimState)
	{
	case EAnimationState::Jump:
		if (mySounds[4] != "Audio/Player/")
			AudioManager::GetInstance().PlayEffect(mySounds[4].c_str());
		break;
	case EAnimationState::Power:
		if (myCurrentPower == EPowerUp::DoubleJump)
			if (mySounds[5] != "Audio/Player/")
				AudioManager::GetInstance().PlayEffect(mySounds[5].c_str());
		break;
	case EAnimationState::W_Jump:
		if (mySounds[6] != "Audio/Player/")
			AudioManager::GetInstance().PlayEffect(mySounds[6].c_str());
		break;
	case EAnimationState::Land:
		if (mySounds[7] != "Audio/Player/")
			AudioManager::GetInstance().PlayEffect(mySounds[7].c_str());
		break;
	case EAnimationState::Death:
		if (mySounds[8] != "Audio/Player/")
			AudioManager::GetInstance().PlayEffect(mySounds[8].c_str());
		break;
	}
}
