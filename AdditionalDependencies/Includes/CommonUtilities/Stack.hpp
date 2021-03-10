#pragma once
#include <assert.h>
namespace CommonUtilities
{
	template <class T, const unsigned int T_Size = 100>
	class Stack
	{
	public:
		//Create a Empty Stack
		Stack();
		//Returns Size of Stack
		int GetSize() const;
		//Returns with Top Element, asserts if Empty
		const T& GetTop() const;
		//Returns with Top Element, asserts if Empty
		T& GetTop();
		//Adds a new element on Top of stack
		void Push(const T& aValue);
		//Removes and returns the Top element, asserts if Empty
		T Pop();
		//Removes Top not returning element
		void RemoveTop();
		//This is an exception to be able to traverse down the Stack without removing above element, 
		//should only be used in special cases
		T& GetElement(const int aIndex);
	private:
		T myContainer[T_Size];
		unsigned int myIterator;
	};

	template<class T, const unsigned int T_Size>
	inline Stack<T, T_Size>::Stack()
	{
		myIterator = 0;
	}

	

	template<class T, const unsigned int T_Size>
	inline int Stack<T, T_Size>::GetSize() const
	{
		return myIterator;
	}

	template<class T, const unsigned int T_Size>
	inline const T& Stack<T, T_Size>::GetTop() const
	{
		assert(myIterator != 0 && "Stack is Empty");
		return myContainer[myIterator - 1];
	}

	template<class T, const unsigned int T_Size>
	inline T& Stack<T, T_Size>::GetTop()
	{
		assert(myIterator != 0 && "Stack is Empty");
		return myContainer[myIterator - 1];
	}

	template<class T, const unsigned int T_Size>
	inline void Stack<T, T_Size>::Push(const T& aValue)
	{
		assert(myIterator <= T_Size && "Stack Filled, increase size of Container");
		myContainer[myIterator] = aValue;

		myIterator++;
	}

	template<class T, const unsigned int T_Size>
	inline T Stack<T, T_Size>::Pop()
	{
		assert(myIterator != 0 && "Stack Empty, cannot remove from empty container");
		T returnValue = myContainer[myIterator - 1];
		delete myContainer[myIterator - 1];
		myIterator--;
		return returnValue;
	}
	template<class T, const unsigned int T_Size>
	inline void Stack<T, T_Size>::RemoveTop()
	{
		assert(myIterator != 0 && "Stack Empty, cannot remove from empty container");
		delete myContainer[myIterator - 1];
		myIterator--;
	}
	template<class T, const unsigned int T_Size>
	inline T& Stack<T, T_Size>::GetElement(const int aIndex)
	{
		assert(myIterator != 0 && "Stack Empty, cannot get element from empty container");
		return myContainer[aIndex];
	}
}