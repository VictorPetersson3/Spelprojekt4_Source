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

	inline void SetAcceleration(const float aAcceleration) { const_cast<float&>(myAcceleration) = aAcceleration; }

	inline void SetMinBoarderX(const float aMinBoarderX) { const_cast<float&>(myMinBoarderX) = aMinBoarderX; }
	inline void SetMaxBoarderX(const float aMaxBoarderX) { const_cast<float&>(myMaxBoarderX) = aMaxBoarderX; }
	inline void SetMinBoarderY(const float aMinBoarderY) { const_cast<float&>(myMinBoarderY) = aMinBoarderY; }
	inline void SetMaxBoarderY(const float aMaxBoarderY) { const_cast<float&>(myMaxBoarderY) = aMaxBoarderY; }
	
	inline void SetPosition(const CommonUtilities::Vector2f aPosition) { myPosition = aPosition; }

	inline void SetMoveX(const bool aBool) { myMoveX = aBool; }
	inline void SetMoveY(const bool aBool) { myMoveY = aBool; }

private:
	void AddForce(const CommonUtilities::Vector2f aForceToAdd);
	void CenterCamera();

private:
	bool myMoveY = true,
	 	 myMoveX = true;

	const float myAcceleration = 5.f,
		myMinBoarderX = 0.0f,
		myMaxBoarderX = 1.0f,
		myMinBoarderY = 0.0f,
		myMaxBoarderY = 1.0f;

	CommonUtilities::Vector2f myPosition = {};
	CommonUtilities::Vector2f myFrameVelocity = {}; 

	std::shared_ptr<Player> myPlayerToFollow = {};
	std::shared_ptr<Camera> myCameraToMove = {};
};

