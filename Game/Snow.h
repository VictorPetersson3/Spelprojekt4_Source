#pragma once
#include "Particle.h"
class Snow :  public Particle
{
public:
	Snow();
	~Snow();

	void Init() override;
	void Reset() override;
	void Update(float aDeltaTime) override;

	Tga2D::CSprite* GetSprite() override;

private:
	Tga2D::CSprite* mySprite = nullptr;
	float myGravity = 0.5f;
	float myPeriod = 1.0f;
};

