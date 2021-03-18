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
	Death
};

class Player
{
public:
	Player();
	~Player();
	virtual void Init(CommonUtilities::Vector2f aPosition);
	virtual void Update(Camera& aCamera);
	//virtual void Render(std::shared_ptr<Camera> aCamera);
	
	void ChangeInput(const EInputType anInputType);

	std::shared_ptr<Collider> GetCollider();
	CommonUtilities::Vector2f GetPosition() const;
	const bool IsDead() const;
	
	void SetPosition(const CommonUtilities::Vector2f& aPosition);

protected:
	virtual void UpdatePhysics();
	virtual void CacheCurrentValues();
	virtual void ManageStates();

	void Idle();
	void Walk();
	void Falling();
	void Ledge();
	void Die();

	void PlaySpecificAnimation(EPlayerAnimationClips anAnimEnum);

protected:
	EPlayerState myMoveState = EPlayerState::Idle;

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

	const float myWalkDecceleration = 2.0f;
	
	const float myWalkSpeed = 2.0f;
	const float myJumpSpeed = 1.5f;
	const float myWallJumpSpeed = 0.7f;

	const float myAirAcceleration = 2.0f;
	const float myAirDecceleration = 1.0f;
	const float myMaxAirSpeed = 0.25f;
	const float myJumpDecceleration = 10.0f;

	const float myMaxHorizontalVelocity = 0.25f;
	const float myMaxVerticalVelocity = 1.5f;
	const float myGravity = 4.0f;

	const float myBoostFactor = 2.0f;
	const float myMaxWallSlideSpeed = 0.2f;
	const float myWallDrag = 1.0f;

	bool myPlayingOnce;

	int myUp = 'W';
	int myLeft = 'A';
	int myDown = 'S';
	int myRight = 'D';
	int myJump = VK_SPACE;
	int myBoost = VK_SHIFT;
	
	bool myCanJumpAgain = true;

	int myDirection = 1;
	EAnimationState myCurrentAnimation = EAnimationState::Idle;
	std::shared_ptr<Collider> myCollider;
	std::shared_ptr<Tga2D::CSprite> mySprite;
	std::vector<std::shared_ptr<AnimationClip>> myAnimations;
};