#pragma once
#include "Particle.h"

namespace Tga2D
{
	class CColor;
	class CSprite;
	class CSpriteBatch;
}

class Emitter
{
public:
	Emitter();
	~Emitter();

	void Update(float aDeltaTime);
	void SetParticleType(const ParticleType& aParticleType);
	void SetPosition(const VECTOR2F& aPosition);
	void Emit();

	void CallRender();

private:
	bool myShouldEmit = false;

	std::vector<Particle*> myParticles;
	ParticleType myParticleType = ParticleType::none;

	VECTOR2F myPosition;

	Tga2D::CSpriteBatch* mySpriteBatch;
	double myEmissionRate = 0.0045;
	float myEmissionTimer = 0;
};

