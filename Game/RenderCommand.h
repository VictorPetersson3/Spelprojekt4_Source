#pragma once
#include <memory>
#include "tga2d/math/vector2.h"
#include "tga2d/render/render_common.h"
#include "CommonUtilities/Vector2.hpp"
#include <tga2d/shaders/customshader.h>

namespace Tga2D
{
	class CSprite;
}
class RenderCommand
{
public:
	RenderCommand();
	RenderCommand(const RenderCommand& aRenderCommand);

	RenderCommand(const char* aImagePath);
	RenderCommand(const char* aImagePath, int aLayer, bool aShouldBeCulled = true);
	RenderCommand(const char* aImagePath, int aLayer, const CommonUtilities::Vector2f& aPos, bool aShouldBeCulled = true);
	
	~RenderCommand() = default;
	void Update(const CommonUtilities::Vector2f& aPos);
	void Render();



	//Getters
	const RenderCommand& GetRenderCommand() const;
	const int GetLayer() const;
	const float GetRotation() const;
	const Tga2D::Vector2ui& GetImageSize() const;
	const CommonUtilities::Vector2f& GetSize() const;
	const CommonUtilities::Vector2f& GetPosition() const;
	//Setters

	void SetRotation(const float aAngleInRadian);
	void SetSpritePosition(const CommonUtilities::Vector2f& aPos);
	void SetTextureRect(float aStartX, float aStartY, float aEndX, float aEndY);
	void SetSizeRelativeToImage(const CommonUtilities::Vector2f& aSize);
	void SetSamplerState(ESamplerFilter aFilter, ESamplerAddressMode aAddressMode);
	void SetPivot(const CommonUtilities::Vector2f& aPivot);
	void SetShader(Tga2D::CCustomShader& aShader);
	void SetColor(Tga2D::CColor& aColor);

private:
	void ReplaceSpritePointerContent(const Tga2D::CSprite& aSprite);


	friend class Camera;
	friend class LevelLoader;
	CommonUtilities::Vector2f myPosition;
	std::shared_ptr<Tga2D::CSprite> mySprite;
	int myLayer;
	bool myShouldBeCulled;
};

