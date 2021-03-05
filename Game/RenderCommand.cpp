#include "stdafx.h"
#include "RenderCommand.h"
#include "tga2d/sprite/sprite.h"
RenderCommand::RenderCommand(const char* aImagePath, int aLayer)
{
	mySprite = std::make_unique<Tga2D::CSprite>(aImagePath);
	myLayer = aLayer;
}

void RenderCommand::Update(const CommonUtilities::Vector2f& aPos)
{
	mySprite->SetPosition({ aPos.x, aPos.y });
}

void RenderCommand::Render()
{
	mySprite->Render();
}

const RenderCommand& RenderCommand::GetRenderCommand() const
{
	return *this;
}

const int RenderCommand::GetLayer() const
{
	return myLayer;
}

void RenderCommand::SetSizeRelativeToImage(const CommonUtilities::Vector2f& aSize)
{
	mySprite->SetSizeRelativeToImage({aSize.x, aSize.y});
}
