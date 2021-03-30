#pragma once
#include "Entity.h"
#include <memory>
#include <CommonUtilities/Vector2.hpp>
class Key;
class Collider;
class Camera;

class Door : public Entity
{
public:
	Door() = default;
	~Door() = default;

	void Init(std::shared_ptr<Key>);
	void Update(float) override;
	void Render(std::shared_ptr<Camera> aCamera) override;

	void Unlock();

	void SetPosition(CommonUtilities::Vector2f aPosition)
	{
		myPosition = aPosition;
	}

	inline CommonUtilities::Vector2f GetPosition() const
	{
		return myPosition;
	}
	inline std::shared_ptr<RenderCommand> GetRenderCommand() const
	{
		return myRenderCommand;
	}
	inline int GetIndex() const
	{
		return myIndex;
	}
	inline void SetIndex(const int aIndex) 
	{
		myIndex = aIndex;
	}
private:

	int myIndex = 0;

	CommonUtilities::Vector2f myPosition = {};
	std::shared_ptr<Key> myKey = {};
	std::shared_ptr<Collider> myCollider = {};
	std::shared_ptr<RenderCommand> myRenderCommand = {};
	bool myIsDestoryed = false;
};

