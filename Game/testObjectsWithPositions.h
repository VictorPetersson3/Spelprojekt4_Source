#pragma once
#include <memory>
#include "CommonUtilities/Vector2.hpp"

namespace Tga2D
{
	class CSprite;
}
class testObjectsWithPositions
{
public:
	testObjectsWithPositions();
	~testObjectsWithPositions() = default;
	void Init(const CommonUtilities::Vector2f& aPos);
	const std::unique_ptr<Tga2D::CSprite>& GetSprite() const;

private:
	std::unique_ptr<Tga2D::CSprite> mySprite;
};

