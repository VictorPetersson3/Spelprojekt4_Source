#include "stdafx.h"
#include "Snow.h"

#include <tga2d/sprite/sprite.h>
#include <random>
#include <cmath>

Snow::Snow()
{
}

Snow::~Snow()
{
	delete mySprite;
	mySprite = nullptr;
}

void Snow::Init()
{
	// Emission Values
	/// Spawn time
	myContents.myMinTimeBetweenParticleSpawns = 0.001f;
	myContents.myMaxTimeBetweenParticleSpawns = 0.01f;
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
	myMinLifeTime = 10.0f;
	myMaxLifeTime = 40.0f;
	/// Color
	myStartColor = { 1, 1, 1, 1.0f };
	myEndColor = { 1, 1, 1, 0.0f };
	/// Acceleration
	myMinAcceleration = { 0.95f, 0.99f };
	myMaxAcceleration = { 0.99f, 0.9999f };
	myGravity = 0.01f;

	// Setting values
	/// Blend State
	myBlendState = EBlendState::EBlendState_Alphablend;

	/// Sprite
	mySprite = new Tga2D::CSprite("Sprites/snowflake6.dds");
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


void Snow::Reset()
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

void Snow::Update(float aDeltaTime)
{
	// Gör vad fan du vill här, det är ingenting som är "permanent".

	myTime += aDeltaTime;

	myVelocity.x = powf(myAcceleration.y, aDeltaTime) * myVelocity.x + sinf(myPeriod * myTime) * 0.05f * aDeltaTime;
	myVelocity.y = powf(myAcceleration.y, aDeltaTime) * myVelocity.y + myGravity * aDeltaTime;

	myAngle += myRotation * aDeltaTime;

	myPosition.x += myVelocity.x * aDeltaTime;
	myPosition.y += myVelocity.y * aDeltaTime;
	
	mySprite->SetPosition(myPosition);
	mySprite->SetRotation(myAngle);

	float size = myStartScale + (myTime / myLifeTime) * (myEndScale - myStartScale);
	mySprite->SetSizeRelativeToImage({ size, size });
	float alpha = myStartColor.myA + (myTime / myLifeTime) * (myEndColor.myA - myStartColor.myA);
	mySprite->SetColor({ myStartColor.myR, myStartColor.myG, myStartColor.myB, alpha });
}

void Snow::Render()
{
}

Tga2D::CSprite* Snow::GetSprite()
{
	return mySprite;
}