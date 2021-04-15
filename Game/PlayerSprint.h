#pragma once
#include "Particle.h"


class PlayerSprint : public Particle
{
public:
	PlayerSprint();
	~PlayerSprint();

	void Init(EWorldLevel aWorld) override;
	void Reset() override;
	void Update(const CommonUtilities::Vector2f& aCamera, const float& aPercentage) override;

	void SetPosition(CommonUtilities::Vector2f aPosition) override;
	Tga2D::CSprite* GetSprite() override;

private:
	Tga2D::CSprite* mySprite = nullptr;
	float myGravity = 0.5f;
	float myPeriod = 1.0f;

	EWorldLevel myWorld;
};
