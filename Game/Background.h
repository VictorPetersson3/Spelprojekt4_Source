#pragma once
#include <array>
#include "CommonUtilities/Vector2.hpp"
#include "RenderCommand.h"
#include "Enums.h"

class AnimationClip;
class Camera;
class Player;

enum class EWorld_but_like_just_a_placeholder_for_the_real_tag
{
	Forest,
	Level2,
	Factory_Kanske,
	MinnsInteVadDennaSkulleVaraHeller
};

struct Layer
{
public:
	void Update();
	void Render(Camera& aCamera);
	RenderCommand mySprite;
	CommonUtilities::Vector2f myPosition;
};

class Background
{
public:
	Background(EWorld_but_like_just_a_placeholder_for_the_real_tag aWorld = EWorld_but_like_just_a_placeholder_for_the_real_tag::Forest);
	~Background() {}

	void Init(Player& aPlayer, EWorldLevel aWorld);
	void Update();
	void Render(Camera& aCamera);

private:
	std::array<std::array<Layer, 3>, 5> mySets;

	std::array<float, 3> mySpeedFactor = { 1.0f / 16.0f, 1.0f / 8.0f, 1.0f / 4.0f };

	CommonUtilities::Vector2<float*> mySpeed;

	EWorld_but_like_just_a_placeholder_for_the_real_tag myWorld;
};

