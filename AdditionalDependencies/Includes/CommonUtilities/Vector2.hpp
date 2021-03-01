#pragma once
#include "math.h"
#include <assert.h>
namespace CommonUtilities
{
	template<class T>
	class Vector2
	{

	public:
		union
		{
			T myX;
			T x;
			T u;
			T myU;
		};

		union
		{
			T myY;
			T y;
			T V;
			T myV;
		};

		Vector2<T>()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
		}
		Vector2<T>(const T& aX, const T& aY)
		{
			x = aX;
			y = aY;
		}
		Vector2<T>(const Vector2<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
		}
		T& operator()(const int aIndex)
		{
			assert(aIndex >= 0 && aIndex < 2);
			switch (aIndex)
			{
			case 0:
				return x;
			case 1:
				return y;
			default:
				break;
			}
		}
		Vector2<T>& operator=(const Vector2<T>& aVector)
		{
			x = aVector.x;
			y = aVector.y;
			return *this;
		}
		~Vector2<T>() = default;

		inline T LengthSqr() const
		{
			return ((x * x) + (y * y));
		}
		inline T Length() const
		{
			return sqrt(LengthSqr());
		}
		inline Vector2<T> GetNormalized() const
		{
			if (Length() == 0)
			{
				return Vector2<T>::Zero;
			}
			return *this / Length();
		}
		inline void Normalize()
		{
			*this = GetNormalized();
		}
		inline T Dot(const Vector2<T>& aVector) const
		{
			return ((this->x * aVector.x) + (this->y * aVector.y));
		}

		static const Vector2
			Zero,
			UnitX,
			UnitY,
			One;

	};
	template<class T>Vector2<T> operator+(const Vector2<T>& aVector, const Vector2<T>& aVector1)
	{
		Vector2<T> temp = aVector;
		temp.x = aVector.x + aVector1.x;
		temp.y = aVector.y + aVector1.y;
		return temp;
	}
	template<class T> Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		Vector2<T> temp = aVector0;
		temp.x = aVector0.x - aVector1.x;
		temp.y = aVector0.y - aVector1.y;
		return temp;
	}
	template<class T> Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		Vector2<T> temp;
		temp.x = aVector.x * aScalar;
		temp.y = aVector.y * aScalar;
		return temp;
	}
	template<class T> Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return aVector * aScalar;
	}
	template<class T> Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		Vector2<T> tempVector = aVector;
		tempVector.x /= aScalar;
		tempVector.y /= aScalar;
		return tempVector;
	}
	template<class T> void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x += aVector1.x;
		aVector0.y += aVector1.y;
	}
	template<class T> void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0.x -= aVector1.x;
		aVector0.y -= aVector1.y;
	}
	template<class T> void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x *= aScalar;
		aVector.y *= aScalar;
	}
	template<class T> void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector.x /= aScalar;
		aVector.y /= aScalar;
	}
	template<class T> bool operator==(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		if (aVector0.x == aVector1.x && aVector0.y == aVector1.y)
		{
			return true;
		}
		return false;
	}
	using Vector2c = Vector2<char>;
	using Vector2i = Vector2<int>;
	using Vector2ui = Vector2<unsigned int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;

	template<typename T> const Vector2<T> Vector2<T>::Zero(static_cast<T>(0), static_cast<T>(0));
	template<typename T> const Vector2<T> Vector2<T>::UnitX(static_cast<T>(1), static_cast<T>(0));
	template<typename T> const Vector2<T> Vector2<T>::UnitY(static_cast<T>(0), static_cast<T>(1));
	template<typename T> const Vector2<T> Vector2<T>::One(static_cast<T>(1), static_cast<T>(1));
}
