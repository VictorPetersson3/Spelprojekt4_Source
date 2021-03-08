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
	void Render();
	
	const bool GetIsActive() const;
	void Activate();
	void Deactivate();
protected:
	CommonUtilities::Vector2f myPosition;
	std::unique_ptr<RenderCommand> myRenderCommand;
private:
	bool myIsActive;
};