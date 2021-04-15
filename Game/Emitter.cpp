#include "stdafx.h"
#include "Emitter.h"
#include "Ambient.h"
#include "PlayerSprint.h"
#include "Camera.h"
#include "Timer.h"
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/sprite/sprite.h>
#include <WinUser.h>
#include <iostream>
#include <random>

#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

Emitter::Emitter(EWorldLevel aWorld)
{
	mySpriteBatch = nullptr;
	myWorld = aWorld;
}

Emitter::~Emitter()
{
	for (auto& particle : myParticles)
	{
		delete particle;
		particle = nullptr;
	}
	myParticles.clear();
	mySpriteBatch->ClearAll();
	mySpriteBatch = nullptr;
}

void Emitter::Update(const CommonUtilities::Vector2f& aPosition, Camera& aCamera)
{
	UpdateTimer();

	SetPosition(aPosition);

	Emit();

	SneakyUpdate(aPosition, aCamera);
}

std::shared_ptr<Tga2D::CSpriteBatch> Emitter::GetBatch()
{
	return mySpriteBatch;
}

void Emitter::Init(const CommonUtilities::Vector2f& aPosition, const ParticleType& aParticleType, const EWorldLevel& aWorld)
{
	myWorld = aWorld;

	SetPosition(aPosition);
	SetParticleType(aParticleType);

	if (aParticleType == ParticleType::Ambient && (myWorld == EWorldLevel::eWorld1 || myWorld == EWorldLevel::eWorld2))
	{
		std::random_device rd;
		std::mt19937 randomInt(rd());
		std::uniform_real_distribution<> eRateDistr(myParticles[0]->GetContents().myMinTimeBetweenParticleSpawns, myParticles[0]->GetContents().myMaxTimeBetweenParticleSpawns);
		myEmissionRate = eRateDistr(randomInt);

		for (int i = 0; i < 20.0f / DELTA_TIME; i++)
		{
			myEmissionTimer += DELTA_TIME;
			Emit();
			for (auto& particle : myParticles)
			{
				if (particle->IsActive())
				{
					particle->Update({ 0, 0 });
				}
			}
		}
	}
}

void Emitter::SetParticleType(const ParticleType& aParticleType)
{
	myParticleType = aParticleType;

	switch (aParticleType)
	{
	case ParticleType::Ambient:
		switch (myWorld)
		{
		case EWorldLevel::eWorld1:
			mySpriteBatch = std::make_shared<Tga2D::CSpriteBatch>("Sprites/Particles/leaf_particle_green.dds");
			mySpriteBatch->Init("Sprites/Particles/leaf_particle_green.dds");
			mySpriteBatch->SetBlendState(EBlendState::EBlendState_Alphablend);
			break;
		case EWorldLevel::eWorld2:
			mySpriteBatch = std::make_shared<Tga2D::CSpriteBatch>("Sprites/Particles/leaf_particle_red.dds");
			mySpriteBatch->Init("Sprites/Particles/leaf_particle_red.dds");
			mySpriteBatch->SetBlendState(EBlendState::EBlendState_Alphablend);
			break;
		case EWorldLevel::eWorld3:
			mySpriteBatch = std::make_shared<Tga2D::CSpriteBatch>("Sprites/Particles/drop_particle.dds");
			mySpriteBatch->Init("Sprites/Particles/drop_particle.dds");
			mySpriteBatch->SetBlendState(EBlendState::EBlendState_Alphablend);
			break;
		case EWorldLevel::eWorld4:
			mySpriteBatch = std::make_shared<Tga2D::CSpriteBatch>("Sprites/Particles/mega_bubble_particle.dds");
			mySpriteBatch->Init("Sprites/Particles/mega_bubble_particle.dds");
			mySpriteBatch->SetBlendState(EBlendState::EBlendState_Additiveblend);
			break;
		}

		for (auto& particle : myParticles)
		{
			delete particle;
			particle = nullptr;
		}
		myParticles.clear();
		for (int i = 0; i < 1000; i++)
		{
			myParticles.push_back(new Ambient(myWorld));
			myParticles[i]->Init();
			myParticles[i]->IsActive() = false;
			mySpriteBatch->AddObject(myParticles[i]->GetSprite());
		}
		break;
	case ParticleType::P_Sprint:
		mySpriteBatch = std::make_shared<Tga2D::CSpriteBatch>("Sprites/Particles/big_player_run_particle_w.dds");
		mySpriteBatch->Init("Sprites/Particles/big_player_run_particle_w.dds");

		mySpriteBatch->SetBlendState(EBlendState::EBlendState_Alphablend);

		for (auto& particle : myParticles)
		{
			delete particle;
			particle = nullptr;
		}
		myParticles.clear();
		for (int i = 0; i < 100; i++)
		{
			myParticles.push_back(new PlayerSprint());
			myParticles[i]->Init(myWorld);
			myParticles[i]->IsActive() = false;
			mySpriteBatch->AddObject(myParticles[i]->GetSprite());
		}
		break;
	}
}

void Emitter::SetPosition(const CommonUtilities::Vector2f& aPosition)
{
	auto pos = aPosition;

	if (myWorld == EWorldLevel::eWorld3 || myWorld == EWorldLevel::eWorld4) pos.y += 1.0f;

	myPosition = pos;
}

//Separate Emit function, use Update() for non-specific uses.
void Emitter::Emit()
{
	if (myEmissionTimer >= myEmissionRate)
	{
		//printf("%f\n", myEmissionTimer);
		myEmissionTimer = 0;

		for (auto& particle : myParticles)
		{
			if (!particle->IsActive())
			{
				particle->IsActive() = true;
				particle->Reset();
				particle->SetPosition(myPosition);
				particle->GetSprite()->SetShouldRender(true);

				std::random_device rd;
				std::mt19937 randomInt(rd());
				std::uniform_real_distribution<> eRateDistr(myParticles[0]->GetContents().myMinTimeBetweenParticleSpawns, myParticles[0]->GetContents().myMaxTimeBetweenParticleSpawns);
				myEmissionRate = eRateDistr(randomInt);
				return;
			}
		}
	}
}

void Emitter::UpdateTimer()
{
	myEmissionTimer += DELTA_TIME;
}

void Emitter::SneakyUpdate(const CommonUtilities::Vector2f& aPosition, Camera& aCamera)
{
	for (auto& particle : myParticles)
	{
		if (particle->IsActive())
		{
			particle->Update(aCamera.GetPosition());

			if (particle->LifeTime())
			{
				particle->IsActive() = false;
				particle->GetSprite()->SetShouldRender(false);
				std::swap(particle, myParticles.front());
			}
		}
	}
}
