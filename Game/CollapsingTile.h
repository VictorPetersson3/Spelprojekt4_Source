#pragma once
#include <iostream>
#include <vector>
#include <CommonUtilities/Vector2.hpp>
#include <memory>
#include "Collider.h"
#include "Entity.h"
#include "Timer.h"

class RenderCommand;
class Collider;

class CollapsingTile : public Entity
{
public:
	
	CollapsingTile(CommonUtilities::Vector2f aPosition);
	~CollapsingTile();

	void Update(float aDeltaTime) override;
	void Render(const std::shared_ptr<Camera> aCamera) override;

private:
	std::shared_ptr<RenderCommand> myRenderCommand;

	float myTimer = 0.f;
	float myCooldownTime = 2.5f;

	bool myHasBeenHitByPlayer = false;
	bool myShouldBeRendered = true;

};

