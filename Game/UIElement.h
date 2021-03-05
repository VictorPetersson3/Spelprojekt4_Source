#pragma once
#include <memory>
#include "CommonUtilities/Vector2.hpp"
#include "RenderCommand.h"
class UIElement
{
public:
	UIElement() = default;
	~UIElement() = default;
	virtual void Update();
	virtual void Init(const CommonUtilities::Vector2f& aPos, const char* aImagePath, const int aLayer);
	const bool GetIsActive() const;
	void Activate();
	void Deactivate();
protected:
	std::unique_ptr<RenderCommand> myRenderCommand;
	CommonUtilities::Vector2f myPosition;
private:
	bool myIsActive;
};