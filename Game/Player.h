#pragma once
#include <CommonUtilities/Vector2.hpp>
#include <memory>

#include "Enums.h"

namespace Tga2D
{
	class CSprite;
}

class Camera;
class Collider;
class AnimationClip;

enum class EPlayerState
{
	Idle,
	Walk,
	Falling,
	Ledge,
	Death
};

enum class EInputType
{
	Controller,
	WASD,
	ArrowKeys
};

enum class EAnimationState
{
	Idle,
	Run,
	Sprint,
	Jump,
	Land,
	W_Idle,
	W_Down,
	W_Up,
	W_Jump,
	Death,
	D_Jump,
	Glide
};

class Player
{
public:
	Player(EPowerUp aPowerup = EPowerUp::Default);
	~Player();

	virtual void Init(CommonUtilities::Vector2f aPosition, EPowerUp aPower = EPowerUp::Default);
	virtual void Update(Camera& aCamera);

	void ChangeInput(const EInputType anInputType);

	void SetPosition(const CommonUtilities::Vector2f& aPosition);
	CommonUtilities::Vector2f GetPosition() const;
	CommonUtilities::Vector2f& GetCurrentVelocity();
	std::shared_ptr<Collider> GetCollider();
	const bool IsDead() const;

protected:
	void InitJSON();
	void InitAnimations();
	void InitCollider();

	void ManageStates();
	void UpdatePhysics();
	void UpdateJumping();
	void HandleAnimations(Camera& aCamera);

	void CacheCurrentValues();
	void ChangePower();

	void Idle();
	void Walk();
	void Falling();
	void Ledge();
	void Die();

	void PlaySpecificAnimation(EPlayerAnimationClips anAnimEnum);

protected:
	CommonUtilities::Vector2f mySize = {};

	CommonUtilities::Vector2f myOldPosition = {};
	CommonUtilities::Vector2f myPosition = {};

	CommonUtilities::Vector2f myOldVelocity = {};
	CommonUtilities::Vector2f myCurrentVelocity = {};

	bool myHuggedRightWall = false;
	bool myHugsRightWall = false;

	bool myHuggedLeftWall = false;
	bool myHugsLeftWall = false;

	bool myWasGrounded = false;
	bool myIsGrounded = false;

	bool myWasRoofied = false;
	bool myIsRoofied = false;

	bool myWasDead = false;
	bool myIsDead = false;

	/*Technically should be const values, but can't because JSON*/
	//======================================//
	float myWalkDecceleration = 2.0f;       //
	float myWalkSpeed = 2.0f;               //
	                                        //
	float myJumpDecceleration = 10.0f;      //
	float myJumpSpeed = 1.5f;               //
	                                        //
	float myWallJumpSpeed = 0.7f;	          //
	float myWallJumpFactorX = 2.0f;         //
	float myWallDrag = 1.0f;                //
	float myMaxWallSlideSpeed = 0.2f;       //
	                                        //
	float myAirAcceleration = 2.0f;			 //
	float myAirDecceleration = 1.0f;        //
	float myMaxAirSpeed = 0.25f;            //
	                                        //
	float myMaxHorizontalVelocity = 0.25f;  //
	float myMaxVerticalVelocity = 1.5f;     //
	float myGravity = 4.0f;                 //
	float myBoostFactor = 2.0f;             //
	float myGlideSpeed = 0.2f;              //
	//======================================//

	int myUp = 0x11;
	int myLeft = 0x1E;
	int myDown = 0x1F;
	int myRight = 0x20;
	int myJump = 0x39;
	int myBoost = 0x2A;
	
	bool myCanJumpAgain = true;
	bool myCanDoubleJump = true;
	bool myIsGliding = false;
	bool myCanGlide = true;

	int myDirection = 1;

	EPlayerState myMoveState = EPlayerState::Idle;
	EAnimationState myCurrentAnimation = EAnimationState::Idle;
	EPowerUp myCurrentPower = EPowerUp::Default;

	std::shared_ptr<Collider> myCollider;
	std::vector<std::shared_ptr<AnimationClip>> myAnimations;
};