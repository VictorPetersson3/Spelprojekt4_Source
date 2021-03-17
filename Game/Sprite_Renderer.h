#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include "RenderCommand.h"
#include "LinkString.h"
#include <set>

namespace Tga2D
{
	class CSpriteBatch;
}
class Sprite_Renderer
{
public:
	Sprite_Renderer() = default;
	~Sprite_Renderer() = default;
	void AddRenderCommandToRenderer(const RenderCommand& aRenderCommand);
	void Render();

private:
	void SortAllSprites();
	std::vector<RenderCommand> myRenderCommands;
	std::map < signed int, std::unordered_map 
		<std::string, Tga2D::CSpriteBatch*>> myLayeredSpriteBatches;
	std::map<signed int, std::set<Tga2D::CSpriteBatch*>> myFilledLayeredBatches;
};

