#pragma once

namespace Tga2D
{
	class CSprite;
	class CColor;
}

namespace CommonUtilities
{
	class Vector2;
}

enum class ParticleType
{
	none,
	Smoke,
	FireRing,
	Explosion,
	Magic,
	Snow
};

struct Emission
{
	float myMinTimeBetweenParticleSpawns;
	float myMaxTimeBetweenParticleSpawns;

	float myEmitTime;
};

class Particle
{
public:
	virtual void Init() {}
	virtual void Reset() {}
	virtual void Update(float aDeltaTime) {}
	virtual void Render() {}
	virtual Tga2D::CSprite* GetSprite() { return nullptr; }
	virtual void SetPosition(VECTOR2F aPosition) { myPosition = aPosition; }
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

	Tga2D::Vector2f myMinAcceleration;
	Tga2D::Vector2f myMaxAcceleration;

	// L�gg eventuellt till v�rden h�r, exempelvis hur brett den ska emittas.

	// <\Ranges>

	EBlendState myBlendState = EBlendState::EBlendState_Disabled;

	Tga2D::Vector2f myVelocity;
	Tga2D::Vector2f myPosition;
};

