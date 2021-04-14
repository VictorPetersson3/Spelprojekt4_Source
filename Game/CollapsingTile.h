#pragma once
#include <iostream>
#include <vector>
#include <CommonUtilities/Vector2.hpp>
#include <memory>
#include "Entity.h"

class RenderCommand;
class Collider;
class AnimationClip;

class CollapsingTile : public Entity
{
public:
	
	CollapsingTile(CommonUtilities::Vector2f aPosition);
	~CollapsingTile();

	void Update(float aDeltaTime) override;
	void Render(const std::shared_ptr<Camera> aCamera) override;
	void InitAnimation();
	std::vector<std::shared_ptr<Collider>> GetAllColliders();

private:
	std::shared_ptr<AnimationClip> myAnimationClip;

	float myTimer = 0.f;
	float myCooldownTime = 0.8f;
	float myAnimtionTime = 0.7f;



	bool myHasBeenHitByPlayer = false;
	bool myShouldBeRendered = true;
	bool myIsAnimating = false;

};

