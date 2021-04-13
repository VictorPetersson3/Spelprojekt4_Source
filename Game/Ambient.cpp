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
	myEndScale = 0.2f;

	/// Start Speed
	myMinStartSpeed = 0.1f;
	myMaxStartSpeed = 0.3f;

	/// Angle
	myMinRotation = -2.0f;
	myMaxRotation = 2.0f;

	/// Lifetime
	myMinLifeTime = 30.0f;
	myMaxLifeTime = 60.0f;
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
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetBlendState(myBlendState);

	std::random_device rd;
	std::mt19937 randomInt(rd());
	std::uniform_real_distribution<> BWBalance(0.5f, 1.0f);
	float color = BWBalance(randomInt);
	myStartColor.myR *= color;
	myStartColor.myG *= color;
	myStartColor.myB *= color;
	myEndColor.myR *= color;
	myEndColor.myG *= color;
	myEndColor.myB *= color;

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
	//if (myVelocity.y > 0) myVelocity.y *= -1;
	//myVelocity.Normalize();
	myVelocity.x *= 9.0f / 16.0f;
	//myVelocity.y = 0;
	myVelocity *= mySpeed;

	/// Lifetime
	std::uniform_real_distribution<> LTDist(myMinLifeTime, myMaxLifeTime);
	myLifeTime = LTDist(randomInt);

	/// Acceleration
	std::uniform_real_distribution<> accelerationDist(myMinAcceleration.x, myMinAcceleration.x);
	myAcceleration.x = accelerationDist(randomInt);
	std::uniform_real_distribution<>(myMinAcceleration.y, myMinAcceleration.y);
	myAcceleration.y = accelerationDist(randomInt);

	/// Time
	myTime = 0;
}

void Ambient::Update(const CommonUtilities::Vector2f& aCamera)
{
	// Gör vad fan du vill här, det är ingenting som är "permanent".

	myTime += DELTA_TIME;

	myVelocity.x = powf(myAcceleration.y, DELTA_TIME) * myVelocity.x + sinf(myPeriod * myTime) * 0.05f * DELTA_TIME;
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
	myPosition = { aPosition.x + float(rand() % 200 - 100) / 100.0f * myEmissionWidth * 0.5f, aPosition.y };
}

Tga2D::CSprite* Ambient::GetSprite()
{
	return mySprite;
}