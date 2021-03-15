#include "stdafx.h"
#include "Level.h"
#include "LevelLoader.h"
#include "Player.h"
#include "Camera.h"
#include "Sprite_Renderer.h"
#include "Camera.h"

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
	myCamera->Update({ 0,0 });
	for (auto t : myTerrain)
	{
		myCamera->BatchRenderSprite(t.get()->myRenderCommand);
		//t.get()->myRenderCommand.Render();
	}
}

void Level::Load(std::shared_ptr<LevelData> aData)
{
	myTerrain = aData.get()->GetTiles();
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
	RenderCommand tempRenderCommand = RenderCommand("Sprites/Tilesets/Tiles.dds", 1);
	tempRenderCommand.Update({ 0.5f,0.5f });
	myTerrain.push_back(std::make_shared<TerrainTile>(tempRenderCommand));
}
