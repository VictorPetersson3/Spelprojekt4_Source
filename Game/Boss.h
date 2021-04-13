#pragma once
#include <CommonUtilities/Vector2.hpp>
#include <memory>
#include <vector>
class Camera;
class Player;
class Collider;
class RenderCommand;
class AnimationClip;

enum class AnimationState 
{
	eIdleL,
	eIdleR,
	eDashL,
	eDashR,
	eTellL,
	eTellR
};

class Boss
{
public:
	Boss() = default;
	~Boss() = default;
	
	void Init(const std::shared_ptr<Player> aPlayer);
	void Update(const float aDt);
	void Render(Camera& aCamera);
	
	inline void AddDashPosition(const CommonUtilities::Vector2f aPosition);
	inline void AddDashPositions(std::vector<CommonUtilities::Vector2f>& somePositions);
	inline void SetDeadState(const bool aBool);

private:
	
	int PickPosition();
	void LoadAnimations();
	void LoadJson();
	void Move(const float aDt);
	void AddForce(const CommonUtilities::Vector2f aForce);
	void PickNewPosition(const float aDt);
	void CheckCollisionWithPlayer();
	void ChangeAnimState(const AnimationState aAnimationState);
	void PickAnimationSide();


private:

	int myPositionIndex = 0;

	float myMoveTimer = 0.f,
		myMoveTime = 2.f,
		myMoveTimerMax = 4.f,
		myMoveTimerMin = 2.f;

	float mySpeed = 1.5f;

	bool myIsDead = false;

	AnimationState myAnimationState = AnimationState::eIdleL;
	std::vector<std::shared_ptr<AnimationClip>> myAnimations;
	CommonUtilities::Vector2f myPosition = {};
	CommonUtilities::Vector2f myDirection = {};

	std::shared_ptr<Collider> myCollider = {};
	std::shared_ptr<Player> myPlayerToAttack = {};
	std::shared_ptr<RenderCommand> myRenderCommand = {};
	std::vector<CommonUtilities::Vector2f> myPostionsToMoveTo = {};
};
inline void Boss::AddDashPosition(const CommonUtilities::Vector2f aPosition)
{
	myPostionsToMoveTo.emplace_back(aPosition);
}
inline void Boss::AddDashPositions(std::vector<CommonUtilities::Vector2f>& somePositions)
{
	myPostionsToMoveTo = somePositions;
}
inline void Boss::SetDeadState(const bool aBool) 
{
	myIsDead = aBool;
}