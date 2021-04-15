#pragma once
#include "Particle.h"

namespace Tga2D
{
	class CColor;
	class CSprite;
	class CSpriteBatch;
}

class Camera;
class RenderCommand;

class Emitter
{
public:
	Emitter(EWorldLevel aWorld = EWorldLevel::eWorld1);
	~Emitter();

	void Init(const CommonUtilities::Vector2f& aPosition, const ParticleType& aParticleType, const EWorldLevel& aWorld);

	void SetParticleType(const ParticleType& aParticleType);
	void SetPosition(const CommonUtilities::Vector2f& aPosition);

	void Update(const CommonUtilities::Vector2f& aPosition, Camera& aCamera, const float& aPercentage = 1.0f);
	void Emit();
	void UpdateTimer();
	void SneakyUpdate(Camera& aCamera, const float& aPercentage);
	
	std::shared_ptr<Tga2D::CSpriteBatch> GetBatch();

private:
	bool myShouldEmit = false;

	std::vector<Particle*> myParticles;
	std::vector<RenderCommand*> myRenderCommands;
	
	ParticleType myParticleType = ParticleType::none;

	CommonUtilities::Vector2f myPosition;

	std::shared_ptr<Tga2D::CSpriteBatch> mySpriteBatch;
	double myEmissionRate;
	float myEmissionTimer = 0;

	EWorldLevel myWorld;
};

