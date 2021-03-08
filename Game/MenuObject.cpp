#include "stdafx.h"
#include "MenuObject.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UIImage.h"



void MenuObject::AddButton(const std::shared_ptr<UIButton> aElement)
{
    myUiButtonElements.push_back(aElement);
}

void MenuObject::Render()
{
    if (GetIsActive())
    {
        for (int i = 0; i < myUiButtonElements.size(); i++)
        {
            if (myUiButtonElements[i]->GetIsActive())
            {
                myUiButtonElements[i]->Render();
            }
        }
    }
}

void MenuObject::Update()
{
    if (GetIsActive())
    {
        for (int i = 0; i < myUiButtonElements.size(); i++)
        {
            if (myUiButtonElements[i]->GetIsActive())
            {
                myUiButtonElements[i]->Update();
            }
        }
    }
}

const bool MenuObject::GetIsActive() const
{
    return myIsActive;
}

void MenuObject::Activate()
{
    myIsActive = true;
    for (int i = 0; i < myUiButtonElements.size(); i++)
    {
        myUiButtonElements[i]->Activate();
    }
}

void MenuObject::DeActivate()
{
    myIsActive = false;
    for (int i = 0; i < myUiButtonElements.size(); i++)
    {
        myUiButtonElements[i]->Deactivate();
    }
}

const int MenuObject::GetUIElementsSize() const
{
    return myUiButtonElements.size();
}

std::shared_ptr<UIButton> MenuObject::GetElement(const int aIndex)
{
    return myUiButtonElements[aIndex];
}

const std::shared_ptr<UIButton> MenuObject::GetElement(const int aIndex) const
{
    return myUiButtonElements[aIndex];
}
