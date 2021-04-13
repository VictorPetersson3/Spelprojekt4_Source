#pragma once
#include "CommonUtilities/Vector2.hpp"
class RenderCommand;
class Camera
{
public:
	Camera();
	~Camera() = default;
	void Init(const CommonUtilities::Vector2f& aPos);
	void Update();
	void RenderSprite(Tga2D::CSprite& aSprite);
	void BatchRenderSprite(RenderCommand& aRenderCommand);
	void RenderSprite(RenderCommand& aRenderCommand);

	inline CommonUtilities::Vector2f GetPosition() const { return myPosition; }
	inline void SetPosition(CommonUtilities::Vector2f aPosition) {	myPosition = aPosition;  }

	/// <summary>
	/// Shake Amount goes from 0 - 1, but you can add more if you feel frisky. 
	/// Amount of Time, is in seconds for how long it will shake
	/// </summary>
	/// <param name="aShakeAmount"></param>
	/// <param name="aAmountOfTime"></param>
	void ShakeCamera(const float aShakeAmount, const float aAmountOfTime);

private:
	static CommonUtilities::Vector2f InsideUnitCircle();
	void CameraShakingFunctionality();
	CommonUtilities::Vector2f myPosition;	
	float myMovementSpeed;
	float myZoomFactor;

	CommonUtilities::Vector2f myCameraShakePosition;
	float myCameraShakeTimer;
	float myCameraShakeMultiplier;
};
