#pragma once
#include "CommonUtilities/Vector2.hpp"
#include "Entity.h"

using Vector2 = CommonUtilities::Vector2f;

class ShooterBulletManager;
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
	void SetManager(std::shared_ptr<ShooterBulletManager> aBulletManager);
	std::shared_ptr<RenderCommand> GetRenderCommand();
	void Update(float aDeltaTime) override;
	void Render(std::shared_ptr<Camera> aCamera)override;
	const void Shoot() const;
		
private:
	
	std::shared_ptr<ShooterBulletManager> myBulletManager;
	std::shared_ptr<RenderCommand> myRenderCommand;
	Vector2 myPosition;
	Vector2 myFireDirection;
	float myFireRate;
	float myFireTimer;

};

