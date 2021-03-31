#pragma once
#include <memory>
#include <CommonUtilities/Vector2.hpp>

class Camera;
class Player;
class CameraBehavoir
{
public:
	typedef void (CameraBehavoir::* MovementFunctions)(const float);

	CameraBehavoir() = default;
	~CameraBehavoir() = default;
	void Init(std::shared_ptr<Camera> aCamera, std::shared_ptr<Player> aPlayer);
	void Update(const float aDt);
	

	void MoveY(const float aDt);
	void MoveX(const float aDt);
	void Static(const float aDt);

private:
	void AddForce(CommonUtilities::Vector2f aForceToAdd);
	void CenterCamera();
	float GetPlayerDistance() const;
	
	CommonUtilities::Vector2f GetPlayerNextFramePos() const;

private:
	bool myMoveY = true,
		 myMoveX = true,
		 myStatic = false;

	float myAcceleration = 0.1f,
		  myMaxSpeed = 1.f, 
		  myRangeToMove = 0.1f;



	CommonUtilities::Vector2f myPosition = {};
	CommonUtilities::Vector2f myFrameVelocity = {}; 

	CommonUtilities::Vector2f myBoundaries = {};
	CommonUtilities::Vector2f myCenterOfMap = {};

	// myBoundaries + myCenterOfMap = myWorldBoundaries
	CommonUtilities::Vector2f myWorldBoundaries = {};

	
	std::shared_ptr<Player> myPlayerToFollow = {};
	std::shared_ptr<Camera> myCameraToMove = {};
	MovementFunctions myMovementFunctions[3] = {};
	

};

