#pragma once

namespace CommonUtilities
{
	template <typename T>
	T Max(const T aFirstValue, const T aSecondValue)
	{
		if (aFirstValue < aSecondValue)
		{
			return aSecondValue;
		}
		return aFirstValue;
	}
	template <typename T>
	T Min(const T aFirstValue, const T aSecondValue)
	{
		if (aFirstValue < aSecondValue)
		{
			return aFirstValue;
		}
		return aSecondValue;
	}
	template <typename T>
	T Abs(const T aValue)
	{
		if (aValue < 0)
		{
			return aValue * (-1);
		}
		return aValue;
	}
	template <typename T>
	T Clamp(const T aMin, const T aMax, const T aValue)
	{
		if (aMin > aMax)
		{
			return false;
		}
		if (aValue > aMin && aValue < aMax)
		{
			return aValue;
		}
		if (aValue <= aMin)
		{
			return aMin;
		}
		return aMax;
	}
	template <typename T>
	T Lerp(const T anXVal, const T anYVal, const float aTVal)
	{
		return anXVal + aTVal * (anYVal - anXVal);
	}
	template <typename T>
	void Swap(T& aAValue, T& aBValue)
	{
		T temp = aAValue;
		aAValue = aBValue;
		aBValue = aAValue;
	}
}




#pragma once
