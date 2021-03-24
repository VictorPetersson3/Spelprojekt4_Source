#pragma once
#include <array>

class AnimationClip;
class Camera;
class RenderCommand;
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
	virtual void Update() = 0;
	CommonUtilities::Vector2f myPosition;
};
struct StaticLayer : public Layer
{
	void Update() override
	{
		mySprite->Update(myPosition);
	}
	std::shared_ptr<RenderCommand> mySprite;
};
struct AnimatedLayer : public Layer
{
	void Update() override
	{
		myAnimation->UpdateAnimation(myPosition);
	}
	std::shared_ptr<AnimationClip> myAnimation;
};

class Background
{
public:
	Background();
	~Background();

	void Init(std::shared_ptr<Player> aPlayer, EWorld_but_like_just_a_placeholder_for_the_real_tag aWorld);
	void Update();
	void MoveLayers();

private:
	void InitWorld1();
	void InitWorld2();
	void InitWorld3();
	void InitWorld4();

private:
	std::array<std::shared_ptr<Layer>, 4> myLayers;

	std::array<float, 4> mySpeedFactor = { 1 / 16.0f, 1 / 8.0f, 1 / 2.0f, 1 / 1.0f };
	CommonUtilities::Vector2f* mySpeed;
};

