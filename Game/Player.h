#pragma once
#include <CommonUtilities/Vector2.hpp>
#include <memory>

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
	virtual void Render();

protected:
	virtual void LoadJsonData();
	virtual void Movement();	
	virtual void InputHandling();
	virtual void PhysicsSimulation();
	void JumpPhysics();
	void ApplyDrag();


	float myMaxVelocity = 0.75f;
	float myAcceleration = 4.25f;
	float myBoostAcceleration = {};
	
	float myJumpTimer = 0;
	float myJumpTime = 0.2f;
	
	float myDrag = 3.0f;
	

	const float myJumpSpeed = 10.f;
	const float myGravity = 1.75f;

	bool myIsGrounded = false;
	CommonUtilities::Vector2f myPosition = {};
	CommonUtilities::Vector2f myCurrentVelocity = {};	
	CommonUtilities::Vector2f myInputVector = {};
	std::shared_ptr<Tga2D::CSprite> mySprite;

};