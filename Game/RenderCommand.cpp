#include "stdafx.h"
#include "RenderCommand.h"
#include "tga2D/sprite/sprite.h"


RenderCommand::RenderCommand()
{
	myLayer = 0;
	mySprite = nullptr;
}
RenderCommand::RenderCommand(const RenderCommand& aRenderCommand)
{
	myLayer = aRenderCommand.myLayer;
	mySprite = aRenderCommand.mySprite;
	myShouldBeCulled = aRenderCommand.myShouldBeCulled;
}
RenderCommand::RenderCommand(const char* aImagePath)
{
	mySprite = std::make_shared<Tga2D::CSprite>(aImagePath);
	mySprite->SetPivot({ 0.5f, 0.5f });
	myLayer = 0;
	mySprite->SetSizeRelativeToImage({ 1.0f, 1.0f });
}
RenderCommand::RenderCommand(const char* aImagePath, int aLayer, bool aShouldBeCulled)
{
	mySprite = std::make_shared<Tga2D::CSprite>(aImagePath);
	mySprite->SetPivot({ 0.5f, 0.5f });
	myLayer = aLayer;
	mySprite->SetSizeRelativeToImage({ 1.0f, 1.0f });
	myShouldBeCulled = aShouldBeCulled;
}

RenderCommand::RenderCommand(const char* aImagePath, int aLayer, const CommonUtilities::Vector2f& aPos, bool aShouldBeCulled)
{
	mySprite = std::make_shared<Tga2D::CSprite>(aImagePath);
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetPosition({ aPos.x, aPos.y });
	mySprite->SetSizeRelativeToImage({ 1.0f, 1.0f });
	myLayer = aLayer;
	myShouldBeCulled = aShouldBeCulled;
}
//Sets position of sprite and if animated will animate
void RenderCommand::Update(const CommonUtilities::Vector2f& aPos)
{
	myPosition = aPos;
	SetSpritePosition(aPos);
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

const float RenderCommand::GetRotation() const
{
	return mySprite->GetRotation();
}

void RenderCommand::SetRotation(const float aAngleInRadian)
{
	mySprite->SetRotation(aAngleInRadian);
}

void RenderCommand::SetSpritePosition(const CommonUtilities::Vector2f& aPos)
{
	mySprite->SetPosition({ aPos.x, aPos.y });
}

void RenderCommand::SetTextureRect(float aStartX, float aStartY, float aEndX, float aEndY)
{
	mySprite->SetTextureRect(aStartX, aStartY, aEndX, aEndY);
}

void RenderCommand::SetSizeRelativeToImage(const CommonUtilities::Vector2f& aSize)
{
	mySprite->SetSizeRelativeToImage({aSize.x, aSize.y});
}

void RenderCommand::SetSamplerState(ESamplerFilter aFilter, ESamplerAddressMode aAddressMode)
{
	mySprite->SetSamplerState(aFilter, aAddressMode);
}

void RenderCommand::SetPivot(const CommonUtilities::Vector2f& aPivot)
{
	mySprite->SetPivot({ aPivot.x, aPivot.y });
}

void RenderCommand::SetShader(Tga2D::CCustomShader& aShader)
{
	mySprite->SetCustomShader(&aShader);
}

void RenderCommand::SetColor(Tga2D::CColor& aColor)
{
	mySprite->SetColor(aColor);
}

void RenderCommand::ReplaceSpritePointerContent(const Tga2D::CSprite& aSprite)
{
	std::shared_ptr<Tga2D::CSprite> tempPointer = std::make_shared<Tga2D::CSprite>(aSprite);
	mySprite = tempPointer;
}

const Tga2D::Vector2ui& RenderCommand::GetImageSize() const
{
	return mySprite->GetImageSize();
}

const CommonUtilities::Vector2f& RenderCommand::GetSize() const
{
	return CommonUtilities::Vector2f(mySprite->GetSize().x, mySprite->GetSize().y);
}

const CommonUtilities::Vector2f& RenderCommand::GetPosition() const
{
	return myPosition;
}
