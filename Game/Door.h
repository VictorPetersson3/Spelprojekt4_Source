#pragma once
#include <memory>
#include <CommonUtilities/Vector2.hpp>
class Key;
class Collider;
class Camera;

class Door
{
public:
	Door() = default;
	~Door() = default;

	void Init(std::shared_ptr<Key>);
	void Update();
	void Render(std::shared_ptr<Camera> aCamera);

	void Unlock();

private:
	CommonUtilities::Vector2f myPosition = {};
	std::shared_ptr<Key> myKey = {};
	std::shared_ptr<Collider> myCollider = {};
	std::shared_ptr<RenderCommand> myRenderCommand = {};

};

