#include "stdafx.h"
#include "Ambient.h"
#include "Timer.h"
#include "Camera.h"
#include <tga2d/sprite/sprite.h>
#include <random>
#include <cmath>


#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

Ambient::Ambient(EWorldLevel aWorld)
{
	myWorld = aWorld;
}

Ambient::~Ambient()
{
	delete mySprite;
	mySprite = nullptr;
}

void Ambient::Init()
{
	switch (myWorld)
	{
	case EWorldLevel::eWorld1:
		InitLeavesG();
		break;
	case EWorldLevel::eWorld2:
		InitLeavesR();
		break;
	case EWorldLevel::eWorld3:
		InitDroplets();
		break;
	case EWorldLevel::eWorld4:
		InitBubbles();
		break;
	}

	mySprite->SetSamplerState(ESamplerFilter::ESamplerFilter_Point, ESamplerAddressMode::ESamplerAddressMode_Clamp);
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetBlendState(myBlendState);

	Reset();
}


void Ambient::Reset()
{
	std::random_device rd;
	std::mt19937 randomInt(rd());

	// Setting values
	/// Color
	mySprite->SetColor({ myStartColor });

	/// Scale
	std::uniform_real_distribution<> scaleDist(myMinStartScale, myMaxStartScale);
	myStartScale = scaleDist(randomInt);

	/// Angle
	std::uniform_real_distribution<> rotationDist(myMinRotation, myMaxRotation);
	myRotation = rotationDist(randomInt);

	/// Sprite
	mySprite->SetSizeRelativeToImage({ myStartScale, myStartScale });

	/// Speed
	std::uniform_real_distribution<> speedDist(myMinStartSpeed, myMaxStartSpeed);
	mySpeed = speedDist(randomInt);
	std::uniform_real_distribution<> periodDist(0.5f, 3.0f);
	myPeriod = periodDist(randomInt);

	/// Velocity
	std::uniform_real_distribution<> velocityDist(-100, 100);
	myVelocity.x = velocityDist(randomInt) / 100.0f;
	myVelocity.y = velocityDist(randomInt) / 200.0f;
	if (!myVelocity.x) myVelocity.x += 0.001f;
	if (!myVelocity.y) myVelocity.y += 0.001f;
	myVelocity.x *= 9.0f / 16.0f;
	myVelocity *= mySpeed;

	/// Lifetime
	std::uniform_real_distribution<> LTDist(myMinLifeTime, myMaxLifeTime);
	myLifeTime = LTDist(randomInt);

	/// Acceleration
	std::uniform_real_distribution<> accelerationDist(myMinAcceleration.x, myMaxAcceleration.x);
	myAcceleration.x = accelerationDist(randomInt);
	std::uniform_real_distribution<> acceleration(myMinAcceleration.y, myMaxAcceleration.y);
	myAcceleration.y = acceleration(randomInt);

	/// Time
	myTime = 0;
}

void Ambient::Update(const CommonUtilities::Vector2f& aCamera, const float& aPercentage)
{
	if (myPosition.y > 2.0f)
	{ 
		myIsActive = false; 
		return; 
	}
	
	// Gör vad fan du vill här, det är ingenting som är "permanent".
	myTime += DELTA_TIME;

	myVelocity.x = powf(myAcceleration.x, DELTA_TIME) * myVelocity.x + sinf(myPeriod * myTime) * 0.05f * DELTA_TIME;
	myVelocity.y = powf(myAcceleration.y, DELTA_TIME) * myVelocity.y + myGravity * DELTA_TIME;

	myAngle += myRotation * DELTA_TIME;

	myPosition.x += myVelocity.x * DELTA_TIME;
	myPosition.y += myVelocity.y * DELTA_TIME;

	mySprite->SetPosition({ myPosition.x - aCamera.x, myPosition.y - aCamera.y }); /////
	mySprite->SetRotation(myAngle);

	float size = myStartScale + (myTime / myLifeTime) * (myEndScale - myStartScale);
	mySprite->SetSizeRelativeToImage({ size, size });
	float alpha = myStartColor.myA + (myTime / myLifeTime) * (myEndColor.myA - myStartColor.myA);
	mySprite->SetColor({ myStartColor.myR, myStartColor.myG, myStartColor.myB, alpha });
}

void Ambient::SetPosition(CommonUtilities::Vector2f aPosition)
{
	myPosition = { aPosition.x + float(rand() % 200 - 100) / 100.0f * myEmissionWidth.x * 0.5f, aPosition.y + float(rand() % 200 - 100) / 100.0f * myEmissionWidth.y * 0.5f };
}

Tga2D::CSprite* Ambient::GetSprite()
{
	return mySprite;
}

void Ambient::InitLeavesG()
{
	// Emission Values
	/// Spawn time
	myContents.myMinTimeBetweenParticleSpawns = 0.001f;
	myContents.myMaxTimeBetweenParticleSpawns = 0.2f;
	/// Emission time
	/*myEmitTime = 0.0f;*/

	// Local Ranges 
	/// Scale
	myMinStartScale = 1.0f;
	myMaxStartScale = 1.5f;

	//myStartScale = 1.0f;
	myEndScale = 0.4f;

	/// Start Speed
	myMinStartSpeed = 0.1f;
	myMaxStartSpeed = 0.3f;

	/// Angle
	myMinRotation = -2.0f;
	myMaxRotation = 2.0f;

	/// Lifetime
	myMinLifeTime = 20.0f;
	myMaxLifeTime = 30.0f;
	/// Color
	myStartColor = { 1, 1, 1, 1.0f };
	myEndColor = { 1, 1, 1, 0.5f };
	/// Acceleration
	myMinAcceleration = { 0.95f, 0.99f };
	myMaxAcceleration = { 0.99f, 0.9999f };
	myGravity = 0.01f;

	// Setting values
	/// Blend State
	myBlendState = EBlendState::EBlendState_Alphablend;

	/// Sprite
	mySprite = new Tga2D::CSprite("Sprites/Particles/leaf_particle_green.dds");
}

void Ambient::InitLeavesR()
{
	// Emission Values
	/// Spawn time
	myContents.myMinTimeBetweenParticleSpawns = 0.001f;
	myContents.myMaxTimeBetweenParticleSpawns = 0.2f;

	// Local Ranges 
	/// Scale
	myMinStartScale = 1.0f;
	myMaxStartScale = 1.5f;

	//myStartScale = 1.0f;
	myEndScale = 0.4f;

	/// Start Speed
	myMinStartSpeed = 0.1f;
	myMaxStartSpeed = 0.3f;

	/// Angle
	myMinRotation = -2.0f;
	myMaxRotation = 2.0f;

	/// Lifetime
	myMinLifeTime = 20.0f;
	myMaxLifeTime = 30.0f;
	/// Color
	myStartColor = { 1, 1, 1, 1.0f };
	myEndColor = { 1, 1, 1, 0.5f };
	/// Acceleration
	myMinAcceleration = { 0.95f, 0.99f };
	myMaxAcceleration = { 0.99f, 0.9999f };
	myGravity = 0.01f;

	// Setting values
	/// Blend State
	myBlendState = EBlendState::EBlendState_Alphablend;

	/// Sprite
	mySprite = new Tga2D::CSprite("Sprites/Particles/leaf_particle_red.dds");
}

void Ambient::InitDroplets()
{
	// Emission Values
	/// Spawn time
	myContents.myMinTimeBetweenParticleSpawns = 0.01f;
	myContents.myMaxTimeBetweenParticleSpawns = 0.6f;
	/// Emission range
	myEmissionWidth = { 1.0f, 1.0f };

	// Local Ranges 
	/// Scale
	myMinStartScale = 1.0f;
	myMaxStartScale = 1.5f;

	//myStartScale = 1.0f;
	myEndScale = 1.0f;

	/// Start Speed
	myMinStartSpeed = 0.1f;
	myMaxStartSpeed = 0.3f;

	/// Angle
	myMinRotation = 0;
	myMaxRotation = 0;

	/// Lifetime
	myMinLifeTime = 6.0f;
	myMaxLifeTime = 6.0f;
	/// Color
	myStartColor = { 1, 1, 1, 0.7f };
	myEndColor = { 1, 1, 1, 1.0f };
	/// Acceleration
	myMinAcceleration = { 0, 0.99f };
	myMaxAcceleration = { 0, 0.9999f };
	myGravity = 0.3f;

	// Setting values
	/// Blend State
	myBlendState = EBlendState::EBlendState_Alphablend;

	/// Sprite
	mySprite = new Tga2D::CSprite("Sprites/Particles/drop_particle.dds");
}

void Ambient::InitBubbles()
{
	// Emission Values
	/// Spawn time
	myContents.myMinTimeBetweenParticleSpawns = 0.001f;
	myContents.myMaxTimeBetweenParticleSpawns = 0.2f;
	/// Emission range
	myEmissionWidth = { 1.0f, 1.0f };

	// Local Ranges 
	/// Scale
	myMinStartScale = 1.0f;
	myMaxStartScale = 1.0f;

	//myStartScale = 1.0f;
	myEndScale = 1.0f;

	/// Start Speed
	myMinStartSpeed = 0.1f;
	myMaxStartSpeed = 0.3f;

	/// Angle
	myMinRotation = -2.0f;
	myMaxRotation = 2.0f;

	/// Lifetime
	myMinLifeTime = 5.0f;
	myMaxLifeTime = 15.0f;
	/// Color
	myStartColor = { 1, 1, 1, 0.4f };
	myEndColor = { 1, 1, 1, 0.7f };
	/// Acceleration
	myMinAcceleration = { 0.95f, 0.99f };
	myMaxAcceleration = { 0.99f, 0.9999f };
	myGravity = -0.01f;

	// Setting values
	/// Blend State
	myBlendState = EBlendState::EBlendState_Alphablend;

	/// Sprite
	switch (rand() % 4)
	{
	case 0:
		mySprite = new Tga2D::CSprite("Sprites/Particles/small_bubble_particle.dds");
		break;
	case 1:
		mySprite = new Tga2D::CSprite("Sprites/Particles/bubble_particle.dds");
		break;
	case 2:
		mySprite = new Tga2D::CSprite("Sprites/Particles/big_bubble_particle.dds");
		break;
	case 3:
		mySprite = new Tga2D::CSprite("Sprites/Particles/mega_bubble_particle.dds");
		break;
	}
}