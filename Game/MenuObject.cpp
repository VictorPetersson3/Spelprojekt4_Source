#include "stdafx.h"
#include "MenuObject.h"
#include "UIButton.h"



void MenuObject::AddButton(const std::shared_ptr<UIButton> aElement)
{
    myUiButtonElements.Add(aElement);
}

MenuObject::MenuObject()
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

std::shared_ptr<UIButton> MenuObject::GetButtonElement(const int aIndex)
{
    return myUiButtonElements[aIndex];
}

const std::shared_ptr<UIButton> MenuObject::GetButtonElement(const int aIndex) const
{
    return myUiButtonElements[aIndex];
}
