#include "stdafx.h"
#include "Emitter.h"
#include "Ambient.h"
#include "Snow.h"
#include "Timer.h"
#include <tga2d/sprite/sprite_batch.h>
#include <WinUser.h>
#include <iostream>
#include <random>

#define DELTA_TIME Timer::GetInstance().GetDeltaTime()

Emitter::Emitter(EWorldLevel aWorld)
{
	mySpriteBatch = new Tga2D::CSpriteBatch("");
	mySpriteBatch->Init();
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
	delete mySpriteBatch;
	mySpriteBatch = nullptr;
}

//Separate Update function, use UpdateAndEmit() for non-specific uses.
void Emitter::Update()
{
	myEmissionTimer += DELTA_TIME;

	/* // Detta är bara om man vill att den ska följa musen, använd annars SetPosition separat.
	auto resolution = Tga2D::CEngine::GetInstance()->GetRenderSize();
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GetActiveWindow(), &pos);
	SetPosition({ (float)pos.x / resolution.x, (float)pos.y / resolution.y });
	*/
	Emit(); // add timer stuff here

	for (auto& particle : myParticles)
	{
		//logic
		if (particle->IsActive())
		{
			particle->Update(DELTA_TIME);

			mySpriteBatch->AddObject(particle->GetSprite());
			if (particle->LifeTime())
			{
				particle->IsActive() = false;
				std::swap(particle, myParticles.front());
			}
		}
	}
}

void Emitter::SetParticleType(const ParticleType& aParticleType)
{
	switch (aParticleType)
	{
	case ParticleType::Ambient:
		mySpriteBatch->Init("Sprites/leaf_particle_red.dds");
		mySpriteBatch->SetBlendState(EBlendState::EBlendState_Alphablend);
		myParticleType = ParticleType::Ambient;
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
		}
		break;
	}
}

void Emitter::SetPosition(const VECTOR2F& aPosition)
{
	myPosition = aPosition;
}

//Separate Emit function, use UpdateAndEmit() for non-specific uses.
void Emitter::Emit()
{
	if (myEmissionTimer >= myEmissionRate)
	{
		myEmissionTimer = 0;

		for (auto& particle : myParticles)
		{
			if (!particle->IsActive())
			{
				particle->IsActive() = true;
				particle->Reset();
				particle->SetPosition(myPosition);
				std::random_device rd;
				std::mt19937 randomInt(rd());
				std::uniform_real_distribution<> eRateDistr(myParticles[0]->GetContents().myMinTimeBetweenParticleSpawns, myParticles[0]->GetContents().myMaxTimeBetweenParticleSpawns);
				myEmissionRate = eRateDistr(randomInt);
				break;
			}
		}
	}
}

void Emitter::CallRender()
{
	mySpriteBatch->Render();
	mySpriteBatch->ClearAll();
}
