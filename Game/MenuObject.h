#pragma once
#include <vector>
#include "CommonUtilities/GrowingArray.hpp"
#include <memory>
#include "State.h"

class UIButton;
class MenuObject : public State
{
public:
    
	MenuObject();
	~MenuObject() = default;

	void Render() override;
	virtual void Update() override;
	virtual void Init(const EStateType& aState) override;
protected:
	void AddButton(const std::shared_ptr<UIButton> aElement);
	std::shared_ptr<UIButton> GetButtonElement(const int aIndex);
	const std::shared_ptr<UIButton> GetButtonElement(const int aIndex) const;
	const int GetUIButtonElementsSize() const;
private:
	CommonUtilities::GrowingArray<std::shared_ptr<UIButton>> myUiButtonElements;
};

