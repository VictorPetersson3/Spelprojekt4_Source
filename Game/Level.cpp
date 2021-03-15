#include "stdafx.h"
#include "Level.h"
#include "LevelLoader.h"
#include "Player.h"
#include "Camera.h"
#include "Sprite_Renderer.h"
#include "Camera.h"
#include "Timer.h"
#include "LevelLoader.h"
#include "Player.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::Render()
{
	mySpriteRenderer->Render();
}

void Level::Update()
{
	//Player
	myCamera->Update({ 0,0 });
	for (auto t : myTerrain)
	{
		myCamera->BatchRenderSprite(t.get()->myRenderCommand);
	}
	float deltaTime = Timer::GetInstance().GetDeltaTime();

	for (auto t : mySaws)
	{
		t.get()->Update(deltaTime);
		//Push in render command to camera 
	}
}

void Level::Load(std::shared_ptr<LevelData> aData)
{
	myTerrain = aData.get()->GetTiles();
	mySaws = aData.get()->GetSaws();
}

void Level::Init(const EStateType& aState)
{
	std::cout << "level inited\n";
	//Creating a camera and then a renderer for the camera
	myCamera = std::make_unique<Camera>();
	mySpriteRenderer = std::make_shared<Sprite_Renderer>();
	myCamera->Init({0.0f, 0.0f}, mySpriteRenderer.get());

	//Load Level Routine
	LevelLoader levelLoader;
	Load(levelLoader.LoadLevel("Json/Levels/CollisionTest.json"));

}
