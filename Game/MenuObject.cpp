#include "stdafx.h"
#include "MenuObject.h"
#include "UIElement.h"



void MenuObject::AddObject(const std::unique_ptr<UIElement> aElement)
{
    myUiElements.push_back(aElement);
}

void MenuObject::Update()
{
    for (int i = 0; i < myUiElements.size(); i++)
    {
        if (myUiElements[i]->GetIsActive())
        {
            myUiElements[i]->Update();
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
}

void MenuObject::DeActivate()
{
    myIsActive = false;
}
