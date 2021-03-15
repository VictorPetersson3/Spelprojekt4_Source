#pragma once
#include <memory>
#include "tga2d/math/vector2.h"
#include "tga2d/render/render_common.h"
#include "CommonUtilities/Vector2.hpp"

namespace Tga2D
{
	class CSprite;
}
class RenderCommand
{
public:
	RenderCommand();
	RenderCommand(const RenderCommand& aRenderCommand);

	RenderCommand(const char* aImagePath, int aLayer);
	RenderCommand(const char* aImagePath, int aLayer, const CommonUtilities::Vector2f& aPos);
	
	~RenderCommand() = default;
	void Update(const CommonUtilities::Vector2f& aPos);
	void Render();



	//Getters
	const RenderCommand& GetRenderCommand() const;
	const int GetLayer() const;
	const Tga2D::Vector2ui& GetImageSize() const;
	const CommonUtilities::Vector2f& GetSize() const;
	const CommonUtilities::Vector2f& GetPosition() const;
	//Setters
	void SetTextureRect(float aStartX, float aStartY, float aEndX, float aEndY);
	void SetSizeRelativeToImage(const CommonUtilities::Vector2f& aSize);
	void SetSamplerState(ESamplerFilter aFilter, ESamplerAddressMode aAddressMode);
	void SetPivot(const CommonUtilities::Vector2f& aPivot);
private:
	void ReplaceSpritePointerContent(const Tga2D::CSprite& aSprite);


	friend class Sprite_Renderer;
	friend class Camera;
	std::shared_ptr<Tga2D::CSprite> mySprite;
	int myLayer;
};

