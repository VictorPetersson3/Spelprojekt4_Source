#pragma once
#include "CommonUtilities/Vector2.hpp"
#include "Enums.h"
#include "RenderCommand.h"

namespace Tga2D
{
	class CSprite;
	class CColor;
}

enum class ParticleType
{
	none,
	P_Sprint,
	P_Land,
	Ambient
};

struct Emission
{
	float myMinTimeBetweenParticleSpawns;
	float myMaxTimeBetweenParticleSpawns;

	float myEmitTime;
};

class Camera;

class Particle
{
public:
	virtual void Init() {}
	virtual void Init(EWorldLevel aWorld){}
	virtual void Reset() {};
	virtual void Update(const CommonUtilities::Vector2f& aCamera){};

	virtual Tga2D::CSprite* GetSprite() = 0;
	virtual void SetPosition(CommonUtilities::Vector2f aPosition) { myPosition = aPosition; }
	virtual bool LifeTime() { return myTime >= myLifeTime; }
	virtual bool& IsActive() { return myIsActive; }
	virtual const Emission& GetContents() { return myContents; }

protected:
	Emission myContents;

	float myLifeTime = 1.0f;
	float myTime = 0.0f;
	float mySpeed = 0.0f;
	float myAngle = 0.0f;
	float myRotation = 0.0f;
	//float myFlow = 0.0f;
	Tga2D::Vector2f myAcceleration;

	bool myIsActive = false;

	// <Ranges>
	float myStartScale = 0.0f;
	float myEndScale = 0.0f;

	float myMinStartScale = 1.0f;
	float myMaxStartScale = 1.0f;

	float myMinStartSpeed = 0.0f;
	float myMaxStartSpeed = 0.0f;

	float myMinRotation = 0.0f;
	float myMaxRotation = 0.0f;

	float myMinLifeTime = 0.0f;
	float myMaxLifeTime = 0.0f;

	float myMinRadius = 0.0f;
	float myMaxRadius = 0.0f;

	Tga2D::CColor myStartColor;
	Tga2D::CColor myEndColor;

	CommonUtilities::Vector2f myMinAcceleration;
	CommonUtilities::Vector2f myMaxAcceleration;

	// Lägg eventuellt till värden här, exempelvis hur brett den ska emittas.
	//CommonUtilities::Vector2f myEmissionSize;

	// <\Ranges>

	EBlendState myBlendState = EBlendState::EBlendState_Disabled;


	CommonUtilities::Vector2f myVelocity;
	CommonUtilities::Vector2f myPosition;
};

