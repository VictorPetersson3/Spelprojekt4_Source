#pragma once
#include "Enums.h"
class State
{
public:
	State()
	{
		myRenderThrough = false;
		myStateType = EStateType::eNull;
	};
	~State() = default;
	virtual void Init(const EStateType& aState) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void OnPushed();
	//By default RenderThrough is false
	void SetRenderThrough(const bool aRenderThroughState);
	const bool GetRenderThrough() const;
	const EStateType& GetStateType() const;
protected:
	void SetStateType(const EStateType& aStateType);
private:
	EStateType myStateType;
	bool myRenderThrough;
};

