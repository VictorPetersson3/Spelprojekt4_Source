#pragma once
#include "CommonUtilities/Vector2.hpp"
#include "Entity.h"
#include <array>
#include "Bullet.h"

using Vector2 = CommonUtilities::Vector2f;
class RenderCommand;

class Shooter : public Entity
{
public:
static enum class EFireDirection
{
	Up,
	Down,
	Right,
	Left
};

	Shooter() = default;
	~Shooter() = default;

	void Init(Vector2 aPosition, Shooter::EFireDirection aFireDirection);
	std::shared_ptr<RenderCommand> GetRenderCommand();
	void Update(float aDeltaTime) override;
	void Render(std::shared_ptr<Camera> aCamera)override;
	void Shoot();
		
private:
	
	std::shared_ptr<RenderCommand> myRenderCommand;
	Vector2 myPosition;
	Vector2 myFireDirection;
	float myFireRate = 5;
	float myFireTimer;
	std::array<Bullet, 10> myBullets;

};

