#include "stdafx.h"
#include "RenderCommand.h"
#include "tga2D/sprite/sprite.h"
RenderCommand::RenderCommand(const char* aImagePath, int aLayer)
{
	mySprite = std::make_shared<Tga2D::CSprite>(aImagePath);
	mySprite->SetPivot({ 0.5f, 0.5f });
	myLayer = aLayer;
}

RenderCommand::RenderCommand(const char* aImagePath, int aLayer, const CommonUtilities::Vector2f& aPos)
{
	mySprite = std::make_shared<Tga2D::CSprite>(aImagePath);
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetPosition({ aPos.x, aPos.y });
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
