#pragma once
#include "Entity.h"

class CollapsingTile : Entity
{
public:
	CollapsingTile(CommonUtilities::Vector2f aPosition);
	~CollapsingTile();

	void Update(float aDeltaTime) override;
};

