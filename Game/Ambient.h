#pragma once
#include "Particle.h"

class Camera;

class Ambient : public Particle
{
public:
	Ambient(EWorldLevel aWorld);
	~Ambient();

	void Init() override;
	void Reset() override;
	void Update(const CommonUtilities::Vector2f& aCamera) override;

	void SetPosition(CommonUtilities::Vector2f aPosition) override;
	Tga2D::CSprite* GetSprite() override;

private:
	Tga2D::CSprite* mySprite = nullptr;
	float myGravity = 0.5f;
	float myPeriod = 1.0f;
	float myEmissionWidth = 1.0f;
	EWorldLevel myWorld;
};

