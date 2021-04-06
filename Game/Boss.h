#pragma once
#include <CommonUtilities/Vector2.hpp>
#include <memory>
#include <vector>
class Camera;
class Player;
class Boss
{
public:
	Boss() = default;
	~Boss() = default;
	void Init(const std::shared_ptr<Player> aPlayer);
	void Update(const float aDt);
	void Render(std::shared_ptr<Camera> aCamera);
	inline void AddDashPosition(CommonUtilities::Vector2f aPosition);

private:
	void Move();
	CommonUtilities::Vector2f PickPositionToMoveTowards();

private:
	std::shared_ptr<Player> myPlayerToAttack = {};

	CommonUtilities::Vector2f myPosition = {};
	CommonUtilities::Vector2f myDirection = {};
	std::vector<CommonUtilities::Vector2f> myPostionsToMoveTo = {};	
};

