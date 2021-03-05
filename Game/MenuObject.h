#pragma once
#include <vector>
#include <memory>
class UIElement;
class MenuObject
{
public:
    
	MenuObject() { myIsActive = false; }
	~MenuObject() = default;
	void AddObject(const std::unique_ptr<UIElement> aElement);
	virtual void Update();

	const bool GetIsActive() const;
	void Activate();
	void DeActivate();

private:
	std::vector<std::unique_ptr<UIElement>> myUiElements;
	bool myIsActive;
};

