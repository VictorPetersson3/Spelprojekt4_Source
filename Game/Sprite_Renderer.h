#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include "RenderCommand.h"
namespace Tga2D
{
	class CSpriteBatch;
}
class Sprite_Renderer
{
	void AddToRenderBatch(const RenderCommand& aRenderCommand);
	void Render();

private:
	void SortAllSprites();
	std::vector<RenderCommand> myRenderCommands;
	std::map < signed int, std::unordered_map 
		<std::string, Tga2D::CSpriteBatch* >> myLayeredSpriteBatches;
};

