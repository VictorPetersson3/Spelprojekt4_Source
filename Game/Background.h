#pragma once
#include <array>
#include "CommonUtilities/Vector2.hpp"
#include "RenderCommand.h"
#include "Enums.h"

class AnimationClip;
class Camera;
class CameraBehavoir;
class Player;

struct Layer
{
public:
	Layer() = default;
	Layer(const RenderCommand aRenderCommand);
	void Update();
	void Render(Camera& aCamera);
	RenderCommand mySprite;
	CommonUtilities::Vector2f myPosition;
};

class Background
{
public:
	Background() {}
	~Background() {}

	void Init(Camera& aCamera, EWorldLevel aWorld, const int aLevelIndex);
	void Update(Camera& aCamera);
	void Render(Camera& aCamera);

private:
	bool myShouldPanX = true;
	bool myShouldPanY = false;

	std::array<std::array<Layer, 3>, 6> mySets;

	std::array<float, 3> mySpeedFactor = { 0.0f, 1.0f / 32.0f, 1.0f / 16.0f };

	CommonUtilities::Vector2f mySpeed;
	CommonUtilities::Vector2f myOldCameraPos;
};

