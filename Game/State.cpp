#include "stdafx.h"
#include "State.h"


void State::OnPushed()
{
	printf("I got pushed");
}

void State::SetRenderThrough(const bool aRenderThroughState)
{
	myRenderThrough = aRenderThroughState;
}

const bool State::GetRenderThrough() const
{
	return myRenderThrough;
}

const EStateType& State::GetStateType() const
{
	return myStateType;
}

void State::SetStateType(const EStateType& aStateType)
{
	myStateType = aStateType;
}
