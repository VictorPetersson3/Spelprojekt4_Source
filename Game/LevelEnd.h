#pragma once
#include "Collider.h"
#include "Entity.h"

class Camera;
class RenderCommand;
class AnimationClip;

using Vector2 = CommonUtilities::Vector2f;

class LevelEnd : public Entity
{

public:
	LevelEnd() = default;
	~LevelEnd() = default;

	void Init(const Vector2 aPosition, const Vector2 aSize, std::string aImagePath);
	void Update(float aDeltaTime) override;
	void Render(std::shared_ptr<Camera> aCamera) override;
	std::vector<std::shared_ptr<Collider>> GetAllColliders();

private:
	std::shared_ptr<AnimationClip> myRenderCommand;
	Vector2 myPosition;
};

