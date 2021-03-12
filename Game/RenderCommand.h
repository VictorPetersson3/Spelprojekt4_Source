#pragma once
#include <memory>
#include "CommonUtilities/Vector2.hpp"
namespace Tga2D
{
	class CSprite;
}
class RenderCommand
{
public:
	RenderCommand(const char* aImagePath, int aLayer);
	RenderCommand(const char* aImagePath, int aLayer, const CommonUtilities::Vector2f& aPos);
	~RenderCommand() = default;
	void Update(const CommonUtilities::Vector2f& aPos);
	void Render();
	const RenderCommand& GetRenderCommand() const;
	const int GetLayer() const;

	void SetSizeRelativeToImage(const CommonUtilities::Vector2f& aSize);
private:
	friend class Sprite_Renderer;
	std::shared_ptr<Tga2D::CSprite> mySprite;
	int myLayer;
};

