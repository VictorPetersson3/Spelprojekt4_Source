#include "stdafx.h"
#include "Level.h"
#include "LevelLoader.h"
#include "Player.h"
#include "Camera.h"
#include "Camera.h"
#include "Timer.h"
#include "InputManager.h"
#include "RenderCommand.h"
#include "Collider.h"
#include "tga2d/sprite/sprite_batch.h"

#include "LevelData.h"
#include "Saw.h"
#include "TerrainTile.h"

Level::Level()
{
	myPlayer = std::make_unique<Player>();
	mySpriteBatches.Init(10);
}

Level::~Level()
{

}

void Level::Render()
{
	for (int i = 0; i < mySpriteBatches.Size(); i++)
	{
		mySpriteBatches[i]->Render();
	}
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

	for (auto saw : mySaws)
	{
		saw.get()->Update(deltaTime);
		myCamera->BatchRenderSprite(*saw.get()->GetRenderCommand());
	}

	if (InputManager::GetInstance().IsKeyPressed(VK_F5))
	{
		Restart();
	}

	if (InputManager::GetInstance().IsKeyPressed(VK_F4))
	{
		Load(1);
	}
	//Collider drawing needs reworking
	//for (auto t : myTerrain)
	//{
	//	t.get()->myCollider.get()->Draw();
	//}
	
	if (myPlayer.get() != nullptr)
	{
		myPlayer.get()->Update();
		myPlayer.get()->GetCollider().get()->Draw();
		//myCamera.get()->RenderSprite(*myPlayer.get()->GetSprite().get());
	}
	

	
}

void Level::Load(std::shared_ptr<LevelData> aData)
{
	if (myPlayer.get()->GetCollider().get() != nullptr)
	{
		myPlayer.get()->GetCollider().get()->RemoveFromManager();
	}

	for (auto t : myTerrain)
	{
		t.get()->myCollider.get()->RemoveFromManager();
	}

	

	myTerrain.clear();

	myTerrain = aData.get()->GetTiles();

	for (int i = 0; i < aData->GetSpriteBatches().Size(); i++)
	{
		mySpriteBatches.Add(aData->GetSpriteBatches()[i]);

	}

	//mySaws = aData.get()->GetSaws();

	for (auto t : myTerrain)
	{
		t.get()->myCollider.get()->AddToManager();
	}

	myPlayer.get()->Init({ aData.get()->GetPlayerStart().x, aData.get()->GetPlayerStart().y });

	if (myPlayer.get()->GetCollider().get() != nullptr)
	{
		myPlayer.get()->GetCollider().get()->AddToManager();
	}
}

void Level::Load(int aIndex)
{
	LevelLoader levelLoader;

	Load(levelLoader.LoadLevel(aIndex));
	currentLevelIndex = aIndex;
}

void Level::Restart()
{
	//myPlayer.reset();
	LevelLoader levelLoader;
	Load(levelLoader.LoadLevel(currentLevelIndex));

	//Load(myCurrentLevelData);
}

void Level::Init(const EStateType& aState)
{
	std::cout << "level inited\n";
	//Creating a camera and then a renderer for the camera
	myCamera = std::make_unique<Camera>();

	currentLevelIndex = 0;

}
