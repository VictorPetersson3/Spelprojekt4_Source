#include "stdafx.h"
#include "Sprite_Renderer.h"
#include "tga2d/sprite/sprite.h"
#include "tga2d/sprite/sprite_batch.h"

void Sprite_Renderer::AddRenderCommandToRenderer(const RenderCommand& aRenderCommand)
{
	//myRenderCommands.push_back(aRenderCommand);
	// Create layer if it does not already exist
	myLayeredSpriteBatches[aRenderCommand.GetLayer()];

	// Check if a batch with the same file path already exists on that layer
	if (myLayeredSpriteBatches.at(aRenderCommand.GetLayer()).count(aRenderCommand.mySprite->GetImagePath()) == 0)
	{
		auto batch = new Tga2D::CSpriteBatch(false);

		batch->Init(aRenderCommand.mySprite->GetImagePath());

		// Include the batch at correct layer
		myLayeredSpriteBatches.at(aRenderCommand.GetLayer())[aRenderCommand.mySprite->GetImagePath()] = batch;

		// Inform that a new spritebatch has been created
		//printf_s("Renderer: Created new SpriteBatch at layer %i with Sprite \"%s\"\n", aRenderCommand.GetLayer(), aRenderCommand.mySprite->GetImagePath());
	}
	if (myLayeredSpriteBatches.at(aRenderCommand.GetLayer()).count(aRenderCommand.mySprite->GetImagePath()) > 0)
	{
		myLayeredSpriteBatches.at(aRenderCommand.GetLayer())[aRenderCommand.mySprite->GetImagePath()]->AddObject(aRenderCommand.mySprite.get());
		// Used in sorting
		myFilledLayeredBatches[aRenderCommand.GetLayer()].insert(myLayeredSpriteBatches.at(aRenderCommand.GetLayer()).at(aRenderCommand.mySprite->GetImagePath()));
	}
}

void Sprite_Renderer::Render()
{
	//SortAllSprites();
	//// Sorting by Layers
	//std::map<signed int, std::set<Tga2D::CSpriteBatch*>> filledLayeredBatches;
	//
	//for (auto& renderCommand : myRenderCommands)
	//{
	//	if (myLayeredSpriteBatches.at(renderCommand.GetLayer()).count(renderCommand.mySprite->GetImagePath()) > 0)
	//	{
	//		auto sprite = renderCommand.mySprite;
	//		//Ändra storleken och sådant på spriten här
	//
	//		myLayeredSpriteBatches.at(renderCommand.GetLayer())[renderCommand.mySprite->GetImagePath()]->AddObject(sprite.get());
	//		// Used in sorting
	//		filledLayeredBatches[renderCommand.GetLayer()].insert(myLayeredSpriteBatches.at(renderCommand.GetLayer()).at(renderCommand.mySprite->GetImagePath()));
	//	}
	//}
	// Render batches
	for (auto& layers : myFilledLayeredBatches)
	{
		for (auto& batch : layers.second)
		{
			batch->Render();
			batch->ClearAll();
		}
	}
	//myRenderCommands.clear();
}

void Sprite_Renderer::SortAllSprites()
{
	for (auto& renderCommand : myRenderCommands)
	{
		// Create layer if it does not already exist
		myLayeredSpriteBatches[renderCommand.GetLayer()];

		// Check if a batch with the same file path already exists on that layer
		if (myLayeredSpriteBatches.at(renderCommand.GetLayer()).count(renderCommand.mySprite->GetImagePath()) == 0)
		{
			auto batch = new Tga2D::CSpriteBatch(false);

			batch->Init(renderCommand.mySprite->GetImagePath());

			// Include the batch at correct layer
			myLayeredSpriteBatches.at(renderCommand.GetLayer())[renderCommand.mySprite->GetImagePath()] = batch;

			// Inform that a new spritebatch has been created
			printf_s("Renderer: Created new SpriteBatch at layer %i with Sprite \"%s\"\n", renderCommand.GetLayer(), renderCommand.mySprite->GetImagePath());
		}
	}
}


