#pragma once
#include<cmath>

namespace CommonUtilities
{
	template <class T>
	class Vector2 {
	public:
		//Konstruktor
		Vector2<T>() = default;
		~Vector2<T>() = default;
		Vector2<T>(const T aX, const T aY) : X(aX), Y(aY)
		{
		}
		Vector2<T>(const Vector2<T>& vectorToCopy) : X(vectorToCopy.X), Y(vectorToCopy.Y)
		{
		}
		//Detta behåller samma värde under dessa variabelnamnen
		union
		{
			T myX = 0;
			T X;
			T u;
			T x;
		};
		union
		{
			T myY = 0;
			T Y;
			T v;
			T y;
		};

		static float SignedAngle(Vector2<T> aFrom, Vector2<T> aTo)
		{
			return (atan2f(aTo.y, aTo.x) - atan2f(aFrom.y, aFrom.x));
		}
		
		static T Distance(const Vector2<T>& aFrom, const Vector2<T>& aTo) 
		{
			Vector2<T> a = aTo - aFrom;
			return a.Length();
		}
		Vector2<T> Clamp(const Vector2<T>& aMin, const Vector2<T>& aMax)
		{
			if (myX > aMax.myX)
				myX = aMax.myX;

			if (myY > aMax.myY)
				myY = aMax.myY;

			if (myX < aMin.myX)
				myX = aMin.myX;

			if (myY < aMin.myY)
				myY = aMin.myY;
			return *this;	
		}
		Vector2<T> Clamp(const float aMin, const float aMax)
		{
			if (myX > aMax)
				myX = aMax;

			if (myY > aMax)
				myY = aMax;

			if (myX < aMin)
				myX = aMin;

			if (myY < aMin)
				myY = aMin;

			return *this;
		}

		//Längd funktioner
		T Length() const
		{
			return sqrt((myX * myX) + (myY * myY));
		}

		T LengthSqr() const
		{
			return (myX * myX) + (myY * myY);

		}


		//Normalized funktioner
		void Normalize()
		{
			if (Length() == 0)
			{
				return;
			}
			const T lSqr = Length();
			myX /= lSqr;
			myY /= lSqr;
		}
		Vector2<T> GetNormalized() const
		{
			if (Length() == 0)
			{
				return Vector2<T>::Zero();
			}

			const T lSqr = Length();
			return Vector2<T>(myX / lSqr, myY / lSqr);
		}

		//Lerp / Dot
		Vector2<T> Lerp(const Vector2<T>& aB, float aAlpha) const
		{
			const Vector2<T> a = Vector2<T>(*this);
			return a + ((aB - a) * aAlpha);
		}

		T Dot(const Vector2<T>& aVector) const
		{
			return (myX * aVector.myX) + (myY * aVector.myY);
		}

		static Vector2<T> One() 
		{
			return Vector2<T>(1, 1);
		}
		static Vector2<T> Zero() 
		{
			return Vector2<T>(0, 0);
		}
		static Vector2<T> Up() 
		{
			return Vector2<T>(0, 1);
		}
		static Vector2<T> Right() 
		{
			return Vector2<T>(1, 0);
		}
		//Vector +*-/ Vector
		Vector2<T> operator+(const Vector2<T>& aRightVector) const
		{
			return Vector2<T>(myX + aRightVector.myX, myY + aRightVector.myY);
		}
		Vector2<T> operator-(const Vector2<T>& aRightVector) const
		{
			return Vector2<T>(myX - aRightVector.myX, myY - aRightVector.myY);
		}
		Vector2<T> operator/(const Vector2<T>& aRightVector) const
		{
			return Vector2<T>(myX / aRightVector.myX, myY / aRightVector.myY);
		}
		Vector2<T> operator*(const Vector2<T>& aRightVector) const
		{
			return Vector2<T>(myX * aRightVector.myX, myY * aRightVector.myY);
		}

		// Vector +*-/ float
		Vector2<T> operator*(const T aScaler) const
		{
			return Vector2<T>(myX * aScaler, myY * aScaler);
		}
		Vector2<T> operator/(const T aScaler) const
		{
			return Vector2<T>(myX / aScaler, myY / aScaler);
		}
		Vector2<T> operator-(const T aScaler) const
		{
			return Vector2<T>(myX - aScaler, myY - aScaler);
		}
		Vector2<T> operator+(const float aScaler) const
		{
			return Vector2<T>(myX + aScaler, myY + aScaler);
		}

		//Vector += Vector
		Vector2<T>& operator+=(const Vector2<T>& aRightVector)
		{
			myX += aRightVector.myX;
			myY += aRightVector.myY;
			return *this;
		}
		Vector2<T>& operator-=(const Vector2<T>& aRightVector)
		{
			myX -= aRightVector.myX;
			myY -= aRightVector.myY;
			return *this;
		}
		Vector2<T>& operator*=(const Vector2<T>& aRightVector)
		{
			myX *= aRightVector.myX;
			myY *= aRightVector.myY;
			return *this;
		}
		Vector2<T>& operator/=(const Vector2<T>& aRightVector)
		{
			myX /= aRightVector.myX;
			myY /= aRightVector.myY;
			return *this;
		}

		//Vector += float
		Vector2<T>& operator+=(const T aScaler)
		{
			myX += aScaler;
			myY += aScaler;
			return *this;
		}
		Vector2<T>& operator-=(const T aScaler)
		{
			myX -= aScaler;
			myY -= aScaler;
			return *this;
		}
		Vector2<T>& operator *= (const T aScaler)
		{
			myX *= aScaler;
			myY *= aScaler;
			return *this;
		}
		Vector2<T>& operator/=(const T aScaler)
		{
			myX /= aScaler;
			myY /= aScaler;
			return *this;
		}

	}; 

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2ui;
	template <class T>
	Vector2<T> operator*(const T& aScaler, const Vector2<T>& aVector)
	{
		return Vector2<T>(aVector.myX * aScaler, aVector.myY * aScaler);
	}
	template <class T>
	Vector2<T> operator/(const T& aScaler, const Vector2<T>& aVector)
	{
		return Vector2<T>(aScaler / aVector.myX, aScaler / aVector.myY);
	}
	template <class T>
	Vector2<T> operator-(const T& aScaler, const Vector2<T>& aVector)
	{
		return Vector2<T>(aScaler - aVector.myX, aScaler - aVector.myY);
	}
	template <class T>
	Vector2<T> operator+(const T& aScaler, const Vector2<T>& aVector)
	{
		return Vector2<T>(aVector.myX + aScaler, aVector.myY + aScaler);
	}
	template <class T>
	bool operator==(const Vector2<T>& aLeftVector, const Vector2<T>& aRightVector) 
	{
		return aLeftVector.x == aRightVector.x && aLeftVector.y == aRightVector.y;
	}
	template <class T>
	bool operator!=(const Vector2<T>& aLeftVector, const Vector2<T>& aRightVector)
	{
		return aLeftVector.x != aRightVector.x || aLeftVector.y != aRightVector.y;
	}
}

