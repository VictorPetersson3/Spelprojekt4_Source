#include "stdafx.h"
#include "MenuObject.h"
#include "UIButton.h"
#include "InputManager.h"


void MenuObject::UpdateInput()
{
	UpdateInputHorizontal();
	UpdateInputVertical();
}

void MenuObject::AddButton(const std::shared_ptr<UIButton> aElement)
{
    myUiButtonElements.Add(aElement);
}

int MenuObject::GetInputHorizontal()
{
	if (myHorizontalUnchanged)
	{
		return 0;
	}
	printf("Horizontal Input : %i\n", myHorizontalInput);
	return myHorizontalInput;
}

int MenuObject::GetInputVertical()
{
	if (myVerticalUnchanged)
	{
		return 0;
	}
	printf("Vertical Input : %i\n", myVerticalInput);
	return myVerticalInput;
}

bool MenuObject::GetInputExit()
{
	bool input = InputManagerS::GetInstance().GetKeyUp(DIK_ESCAPE);
	if (!input)
	{
		if (myController->IsConnected() && myController->IsButtonDown(XINPUT_GAMEPAD_B))
		{
			input = true;
		}
	}
	return input;
}

bool MenuObject::GetInputContinue()
{
	bool input = InputManagerS::GetInstance().GetKeyUp(DIK_RETURN);
	if (!input)
	{
		if (myController->IsConnected() && myController->IsButtonDown(XINPUT_GAMEPAD_A))
		{
			input = true;
		}
	}
	return input;
}

MenuObject::MenuObject(XController* aControllerPointer) : myController(aControllerPointer)
{
    myUiButtonElements.Init(10);
}

void MenuObject::Render()
{
    for (int i = 0; i < myUiButtonElements.Size(); i++)
    {
        if (myUiButtonElements[i]->GetIsActive())
        {
            myUiButtonElements[i]->Render();
        }
    }
}

void MenuObject::Update()
{
    for (int i = 0; i < myUiButtonElements.Size(); i++)
    {
        if (myUiButtonElements[i]->GetIsActive())
        {
            myUiButtonElements[i]->Update();
        }
    }
}

void MenuObject::Init(const EStateType& aState)
{
    printf("MenuObject Init()\n");
}

const int MenuObject::GetUIButtonElementsSize() const
{
    return myUiButtonElements.Size();
}

void MenuObject::UpdateInputHorizontal()
{
	myPreviousHorizontalInput = myHorizontalInput;
	int rInput = 0;
	int lInput = 0;
	bool controllerConnected = myController->IsConnected();
	if (controllerConnected && myController->GetDPadInput().x > 0 || myController->GetLeftTumbStick().x > 0.45f)
	{
		rInput += 1;
	}
	if (InputManagerS::GetInstance().GetKeyUp(DIK_D) || InputManagerS::GetInstance().GetKeyUp(DIK_RIGHT))
	{
		if (rInput == 0)
		{
			rInput += 1;
		}
	}
	if (InputManagerS::GetInstance().GetKeyUp(DIK_A) || InputManagerS::GetInstance().GetKeyUp(DIK_LEFT))
	{
		lInput -= 1;
	}
	if (controllerConnected && myController->GetDPadInput().x < 0 || myController->GetLeftTumbStick().x < -0.45f)
	{
		if (lInput == 0)
		{
			lInput -= 1;
		}
	}
	myHorizontalInput = rInput + lInput;
	if (myPreviousHorizontalInput == myHorizontalInput)
	{
		myHorizontalUnchanged = true;
	}
	else
	{
		myHorizontalUnchanged = false;
	}
}

void MenuObject::UpdateInputVertical()
{
	myPreviousVerticalInput = myVerticalInput;
	int uInput = 0;
	int dInput = 0;
	bool controllerConnected = myController->IsConnected();
	if (controllerConnected && myController->GetDPadInput().y > 0 || myController->GetLeftTumbStick().y > 0.45f)
	{
		uInput += 1;
	}
	if (InputManagerS::GetInstance().GetKeyUp(DIK_W) || InputManagerS::GetInstance().GetKeyUp(DIK_UP))
	{
		if (uInput == 0)
		{
			uInput += 1;
		}
	}
	if (InputManagerS::GetInstance().GetKeyUp(DIK_S) || InputManagerS::GetInstance().GetKeyUp(DIK_DOWN))
	{
		dInput -= 1;
	}
	if (controllerConnected && myController->GetDPadInput().y < 0 || myController->GetLeftTumbStick().y < -0.45f)
	{
		if (dInput == 0)
		{
			dInput -= 1;
		}
	}
	myVerticalInput = uInput + dInput;
	if (myPreviousVerticalInput == myVerticalInput)
	{
		myVerticalUnchanged = true;
	}
	else
	{
		myVerticalUnchanged = false;
	}
}


std::shared_ptr<UIButton> MenuObject::GetButtonElement(const int aIndex)
{
    return myUiButtonElements[aIndex];
}

const std::shared_ptr<UIButton> MenuObject::GetButtonElement(const int aIndex) const
{
    return myUiButtonElements[aIndex];
}
