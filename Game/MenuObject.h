#pragma once
#include <vector>
#include "CommonUtilities/GrowingArray.hpp"
#include <memory>
#include "State.h"
#include "XController.h"

class UIButton;
class MenuObject : public State
{
public:
    
	MenuObject(XController* aControllerPointer);
	~MenuObject() = default;

	void Render() override;
	virtual void Update() override;
	virtual void Init(const EStateType& aState) override;
protected:
	void UpdateInput();
	void AddButton(const std::shared_ptr<UIButton> aElement);
	bool GetInputExit();
	bool GetInputContinue();
	int GetInputHorizontal();
	int GetInputVertical();

	std::shared_ptr<UIButton> GetButtonElement(const int aIndex);
	const std::shared_ptr<UIButton> GetButtonElement(const int aIndex) const;
	const int GetUIButtonElementsSize() const;
	XController* myController;


private:
	void UpdateInputHorizontal();
	void UpdateInputVertical();
	void UpdateInputContinue();
	void UpdateInputExit();
	int myPreviousHorizontalInput = 0;
	int myPreviousVerticalInput = 0;
	int myHorizontalInput = 0;
	int myVerticalInput = 0;
	bool myContinueInput = false;
	bool myExitInput = false;

	bool myHorizontalUnchanged = false;
	bool myVerticalUnchanged = false;

	CommonUtilities::GrowingArray<std::shared_ptr<UIButton>> myUiButtonElements;
};

