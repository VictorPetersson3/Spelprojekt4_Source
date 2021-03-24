#pragma once
#include <memory>
#include <CommonUtilities/Vector2.hpp>
class Player;
class Key
{
public:
	Key() = default;
	~Key() = default;

	void Init(std::shared_ptr<Player> aPlayer);
	void Update();
	void Render();
	bool CheckState();
	inline bool GetKeyState() const 
	{
		return myIsPickedUp;
	}


private:

	const int myId = 0;                        // Detta är ett id som level design ska kunna använda för att ha flera olika nycklar i samma level
	bool myIsPickedUp = false;
	const float myRange = 0.025f;

	CommonUtilities::Vector2f myPosition;
	std::shared_ptr<Player> myPlayer;

};

