#pragma once
#include <memory>

class Key;
class Collider;

class Door
{
public:
	Door() = default;
	~Door() = default;

	void Init();
	void Update();
	void Render();

	void Unlock();

private:
	std::shared_ptr<Key> myKey = {};


};

