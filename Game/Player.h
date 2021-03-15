#pragma once
#include <CommonUtilities/Vector2.hpp>
#include <memory>
class Camera;
class Collider;

enum class PlayerStates {
	eFalling,
	eJumping,
	eRunning,

};
namespace Tga2D 
{
	class CSprite;
}

class Player
{
public:
	Player();
	~Player();
	virtual void Init();
	virtual void Update();
	virtual void Render(std::shared_ptr<Camera> aCamera);
	CommonUtilities::Vector2f GetPosition() const;


protected:
	virtual void LoadJsonData();
	virtual void Movement();	
	virtual void InputHandling();
	virtual void PhysicsSimulation();
	
	void JumpPhysics();
	void ApplyDrag(const float aThisFrameVel);
	void CollisionSolver(CommonUtilities::Vector2f aFrameDirection);
protected:

	bool myIsGrounded = false;
	bool myCanJump = false;
	float myMaxVelocity = 0.75f;
	float myAcceleration = 4.25f; 
	
	float myJumpTimer = 0;
	float myJumpTime = 0.2f;
	
	float myDrag = 3.0f;


	int myBoostInput = 0;
	float myBoostDrag = 10.0f;
	float myMaxBoostVelocity = 2.f;
	float myBoostAcceleration = 7.0f;

	float myAirControll = 0.125f;
	float myJumpSpeed = 10.0f;
	float myGravity = 1.5f;


	float timer = 3.f;

	PlayerStates myPlayerState;
	std::shared_ptr<Collider> myCollider = {};

	CommonUtilities::Vector2f myPosition = {};
	CommonUtilities::Vector2f myCurrentVelocity = {};	
	CommonUtilities::Vector2f myInputVector = {};
	std::shared_ptr<Tga2D::CSprite> mySprite;
	
};