#pragma once
#include "CommonUtilities/Vector2.hpp"
#include <memory>
class RenderCommand
{
public:
	RenderCommand(const char* aImagePath, int aLayer);
	~RenderCommand() = default;
	void Update(const CommonUtilities::Vector2f& aPos);
	void Render();
	const RenderCommand& GetRenderCommand() const;
	const int GetLayer() const;

	void SetSizeRelativeToImage(const CommonUtilities::Vector2f& aSize);
private:
	std::unique_ptr<Tga2D::CSprite> mySprite;
	int myLayer;
};

