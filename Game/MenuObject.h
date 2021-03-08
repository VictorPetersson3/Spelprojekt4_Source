#pragma once
#include <vector>
#include <memory>
class UIButton;
class MenuObject
{
public:
    
	MenuObject() { myIsActive = false; }
	~MenuObject() = default;

	void AddButton(const std::shared_ptr<UIButton> aElement);
	void Render();
	virtual void Update();
	virtual void Init() = 0;
	const bool GetIsActive() const;
	void Activate();
	void DeActivate();
protected:
	std::shared_ptr<UIButton> GetElement(const int aIndex);
	const std::shared_ptr<UIButton> GetElement(const int aIndex) const;
	const int GetUIElementsSize() const;
private:
	std::vector<std::shared_ptr<UIButton>> myUiButtonElements;
	bool myIsActive;
};

