#pragma once
#include <memory>
#include <CommonUtilities/Vector2.hpp>

class Camera;
class Player;
class CameraBehavoir
{
public:
	CameraBehavoir() = default;
	~CameraBehavoir() = default;
	void Init(std::shared_ptr<Camera> aCamera, std::shared_ptr<Player> aPlayer);
	void Update(const float aDt);
	void ResetCamera();



private:
	void AddForce(const CommonUtilities::Vector2f aForceToAdd);
	void CenterCamera();

private:
	bool myMoveY = true,
	 	 myMoveX = true;

	float myAcceleration = 5.f,
		myRangeToMove = 0.1f,
		myMinBoarderX = 0.0f,
		myMaxBoarderX = 1.0f,
		myMinBoarderY = 0.0f,
		myMaxBoarderY = 1.0f,
		myMaxVelocity = .5f;

	CommonUtilities::Vector2f myPosition = {};
	CommonUtilities::Vector2f myFrameVelocity = {}; 

	std::shared_ptr<Player> myPlayerToFollow = {};
	std::shared_ptr<Camera> myCameraToMove = {};
};

