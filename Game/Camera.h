#pragma once
#include "CommonUtilities/Vector2.hpp"
class RenderCommand;
class Camera
{
public:
	Camera();
	~Camera() = default;
	void Init(const CommonUtilities::Vector2f& aPos);
	void Update(const CommonUtilities::Vector2f aPositionToFollow);
	void RenderSprite(Tga2D::CSprite aSprite);
	void BatchRenderSprite(RenderCommand& aRenderCommand);
	void RenderSprite(RenderCommand& aRenderCommand);

	inline CommonUtilities::Vector2f GetPosition() const { return myPosition; }
	inline void SetPosition(CommonUtilities::Vector2f aPosition) {	myPosition = aPosition;  }

private:
	CommonUtilities::Vector2f myPosition;
	float myMovementSpeed;
};
