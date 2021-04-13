#pragma once
#include "Particle.h"

namespace Tga2D
{
	class CColor;
	class CSprite;
	class CSpriteBatch;
}

class Camera;

class Emitter
{
public:
	Emitter(EWorldLevel aWorld);
	~Emitter();

	void Init(const CommonUtilities::Vector2f& aPosition, const ParticleType& aParticleType);

	void SetParticleType(const ParticleType& aParticleType);
	void SetPosition(const CommonUtilities::Vector2f& aPosition);

	void Update(const CommonUtilities::Vector2f& aPosition, Camera& aCamera);

	std::shared_ptr<Tga2D::CSpriteBatch> GetBatch();

private:
	void Emit();
	bool myShouldEmit = false;

	std::vector<Particle*> myParticles;
	ParticleType myParticleType = ParticleType::none;

	CommonUtilities::Vector2f myPosition;

	std::shared_ptr<Tga2D::CSpriteBatch> mySpriteBatch;
	double myEmissionRate;
	float myEmissionTimer = 0;

	EWorldLevel myWorld;
};

