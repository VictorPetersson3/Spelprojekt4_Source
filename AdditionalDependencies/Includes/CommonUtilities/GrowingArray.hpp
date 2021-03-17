#pragma once
#include <assert.h>
#include <functional>

namespace CommonUtilities
{
	template <typename T, typename CountType = unsigned short>
	class GrowingArray
	{
	public:
		GrowingArray();

		GrowingArray(CountType aAmountOfItems, bool aUseSafeModeFlag = true);
		GrowingArray(const GrowingArray& aGrowingArray);

		~GrowingArray();

		GrowingArray& operator=(const GrowingArray& aGrowingArray);

		void Init(CountType aAmountOfItems, bool aUseSafeModeFlag = true);
		void ReInit(CountType aAmountOfItems, bool aUseSafeModeFlag = true);
		const CountType Size() const;

		inline T& operator[](const CountType& aIndex);
		inline const T& operator[](const CountType& aIndex) const;

		inline void Add(const T& aObject);
		inline void Insert(const CountType& aIndex, const T& aObject);
		inline void DeleteCyclic(const T& aObject);
		inline void DeleteCyclicAtIndex(CountType aItemIndex);
		inline void RemoveCyclic(const T& aObject);
		inline void RemoveCyclicAtIndex(CountType aItemIndex);
		inline void RemoveAtIndex(CountType aItemIndex);
		inline CountType Find(const T& aObject);
		inline T& GetLast();
		inline const T& GetLast() const;
		inline void RemoveAll();
		inline void DeleteAll();

		inline void CallFunctionOnAllMembers(std::function<void(T&)> aFunction);
		inline void CallFunctionOnAllMembers(std::function<void(const T&)> aFunction) const;
		inline const bool IsInitialized() const;

	private:
		void DumpAll();
		void GrowArray();
		void GrowArray(const CountType aGrowthAmount);

		T* myArrayPointer;
		CountType myElementCount;
		CountType myArrayCapacity;
		bool myUseSafeMode;
		bool myIsInitialized;
	};

	template <typename T, typename CountType>
	inline GrowingArray<T, CountType>::GrowingArray()
	{
		myArrayPointer = nullptr;
		myElementCount = 0;
		myArrayCapacity = 0;
		myUseSafeMode = true;
		myIsInitialized = false;
	}

	template <typename T, typename CountType>
	inline GrowingArray<T, CountType>::GrowingArray(CountType aAmountOfItems, bool aUseSafeModeFlag)
	{
		myArrayPointer = nullptr;
		myArrayCapacity = 0;
		myElementCount = 0;
		myUseSafeMode = true;
		myIsInitialized = false;
		Init(aNrOfRecommendedItems, aUseSafeModeFlag);
	}

	template <typename T, typename CountType>
	inline GrowingArray<T, CountType>::GrowingArray(const GrowingArray& aGrowingArray)
	{
		*this = aGrowingArray;
	}

	template <typename T, typename CountType>
	inline GrowingArray<T, CountType>::~GrowingArray()
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		DumpAll();
	}

	template <typename T, typename CountType>
	inline GrowingArray<typename T, typename CountType>&
		GrowingArray<T, CountType>::operator=(const GrowingArray& aGrowingArray)
	{
		if (myIsInitialized)
		{
			DumpAll();
		}
		Init(aGrowingArray.myArrayCapacity, aGrowingArray.myUseSafeMode);

		myElementCount = aGrowingArray.myElementCount;
		myIsInitialized = aGrowingArray.myIsInitialized;
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::Init(CountType aAmountOfItems, bool aUseSafeModeFlag)
	{
		assert(myIsInitialized == false && "Growing Array should not initiated twice");
		myArrayCapacity = aAmountOfItems;
		myUseSafeMode = aUseSafeModeFlag;
		myIsInitialized = true;
		myArrayPointer = new T[myArrayCapacity];
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::ReInit(CountType aAmountOfItems, bool aUseSafeModeFlag)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		DumpAll();
		Init(aAmountOfItems, aUseSafeModeFlag);
	}

	template <typename T, typename CountType>
	inline const CountType GrowingArray<T, CountType>::Size() const
	{
		return myElementCount;
	}

	template <typename T, typename CountType>
	inline T& GrowingArray<T, CountType>::operator[](const CountType& aIndex)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		assert(aIndex < myElementCount && "Index is out of Range");
		assert(aIndex >= 0 && "Index can not be negative");
		return myArrayPointer[aIndex];
	}

	template <typename T, typename CountType>
	inline const T& GrowingArray<T, CountType>::operator[](const CountType& aIndex) const
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		assert(aIndex < myElementCount && "Index is out of Range");
		assert(aIndex >= 0 && "Index can not be negative");
		return myArrayPointer[aIndex];
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::Add(const T& aObject)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		if (myElementCount + 1 > (myArrayCapacity))
		{
			GrowArray();
		}
		myArrayPointer[myElementCount] = aObject;
		myElementCount++;
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::Insert(const CountType& aIndex, const T& aObject)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		assert(aIndex >= 0 && "Index can not be negative");
		assert(aIndex <= myElementCount && "Index is out of range");
		T tempObject = myArrayPointer[myElementCount - 1];
		if (aIndex != myElementCount)
		{
			for (CountType index = myElementCount - 1; index > aIndex; --index)
			{
				myArrayPointer[index] = myArrayPointer[index - 1];
			}
		}
		myArrayPointer[aIndex] = aObject;
		Add(tempObject);
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::DeleteCyclic(const T& aObject)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		const CountType objectIndex = Find(aObject);
		if (objectIndex != -1)
		{
			DeleteCyclicAtIndex(objectIndex);
		}
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::DeleteCyclicAtIndex(CountType aItemNumber)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		assert(aIndex <= myElementCount && "Index is out of range");
		assert(aIndex >= 0 && "Index can not be negative");
		if (myElementCount != 1)
		{
			if (aItemNumber == myElementCount - 1)
			{
				delete myArrayPointer[aItemNumber];
				myArrayPointer[aItemNumber] = nullptr;
			}
			else
			{
				delete myArrayPointer[aItemNumber];
				myArrayPointer[aItemNumber] = myArrayPointer[myElementCount - 1];
			}
			--myElementCount;
		}
		else
		{
			delete myArrayPointer[0];
			myArrayPointer[0] = nullptr;
			RemoveAll();
		}
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::RemoveCyclic(const T& aObject)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");

		const CountType objectIndex = Find(aObject);
		if (objectIndex != -1)
		{
			DeleteCyclicAtIndex(objectIndex);
		}
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::RemoveCyclicAtIndex(CountType aItemIndex)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		assert(aItemIndex < myElementCount && "Index is out of range");
		assert(aItemIndex >= 0 && "Index can not be negative");
		if (myElementCount != 1)
		{
			myArrayPointer[aItemIndex] = myArrayPointer[myElementCount - 1];
			--myElementCount;
		}
		else
		{
			RemoveAll();
		}
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::RemoveAtIndex(CountType aItemIndex)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		assert(aItemIndex < myElementCount && "Index is out of range");
		assert(aItemIndex >= 0 && "Index can not be negative");
		--myElementCount;
		for (int i = aItemIndex; i < myElementCount; ++i)
		{
			myArrayPointer[i] = myArrayPointer[i + 1];
		}
	}

	template <typename T, typename CountType>
	inline CountType GrowingArray<T, CountType>::Find(const T& aObject)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		for (CountType index = 0; index < myElementCount; ++index)
		{
			if (myArrayPointer[index] == aObject)
			{
				return index;
			}
		}
		return -1;
	}

	template <typename T, typename CountType>
	inline T& GrowingArray<T, CountType>::GetLast()
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		assert(myElementCount > 0 && "Vector is empty");
		return myArrayPointer[myElementCount - 1];
	}

	template <typename T, typename CountType>
	inline const T& GrowingArray<T, CountType>::GetLast() const
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		assert(myElementCount > 0 && "Vector is empty");
		return myArrayPointer[myElementCount - 1];
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::RemoveAll()
	{
		myElementCount = 0;
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::DeleteAll()
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		for (CountType i = 0; i < myElementCount; i++)
		{
			delete myArrayPointer[i];
			myArrayPointer[i] = nullptr;
		}
		RemoveAll();
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::CallFunctionOnAllMembers(std::function<void(T&)> aFunction)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		for (CountType i = 0; i < myElementCount; i++)
		{
			aFunction(*this myArrayPointer[i]);
		}
	}

	template <typename T, typename CountType>
	inline void
		GrowingArray<T, CountType>::CallFunctionOnAllMembers(std::function<void(const T&)> aFunction) const
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		for (CountType i = 0; i < myElementCount; i++)
		{
			aFunction(*this myArrayPointer[i]);
		}
	}

	template <typename T, typename CountType>
	inline const bool GrowingArray<T, CountType>::IsInitialized() const
	{
		return myIsInitialized;
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::DumpAll()
	{
		if (myIsInitialized)
		{
			delete[] myArrayPointer;
			myArrayPointer = nullptr;
			myArrayCapacity = 0;
		}
		myIsInitialized = false;
		RemoveAll();
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::GrowArray()
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		GrowArray(myArrayCapacity * 2);
	}

	template <typename T, typename CountType>
	inline void GrowingArray<T, CountType>::GrowArray(const CountType aGrowthAmount)
	{
		assert(myIsInitialized == true && "Growing Array is not initialized");
		T* tempArrayPointer = myArrayPointer;
		const CountType tempCount = myElementCount;
		myIsInitialized = false;
		Init(aGrowthAmount);
		if (myUseSafeMode)
		{
			for (CountType i = 0; i < tempCount; ++i)
			{
				myArrayPointer[i] = tempArrayPointer[i];
			}
		}
		else
		{
			memcpy(myArrayPointer, tempArrayPointer, (sizeof(T) * tempCount));
		}
		delete[] tempArrayPointer;
		tempArrayPointer = nullptr;
	}

}