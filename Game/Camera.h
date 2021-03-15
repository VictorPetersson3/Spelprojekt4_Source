#pragma once
#include "CommonUtilities/Vector2.hpp"
class Sprite_Renderer;
class RenderCommand;
class Camera
{
public:
	Camera();
	~Camera() = default;
	void Init(const CommonUtilities::Vector2f& aPos);
	void Init(const CommonUtilities::Vector2f& aPos, Sprite_Renderer* aSpriteRenderer);
	void Update(const CommonUtilities::Vector2f aPositionToFollow);
	void RenderSprite(const Tga2D::CSprite aSprite);
	void BatchRenderSprite(const RenderCommand& aRenderCommand);

private:
	CommonUtilities::Vector2f myPosition;
	Sprite_Renderer* mySpriteRenderRef;
	float myMovementSpeed;
};
