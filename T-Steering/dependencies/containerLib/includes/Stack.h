#pragma once

#include"DynamicArray.h"

template<typename T>
class Stack
{
public:
	int Size()
	{
		return m_DynArray.Size();
	}

	bool Empty()
	{
		return (m_DynArray.Size() == 0);
	}

	void Push(T value)
	{
		m_DynArray.PushBack(value);
	}

	T Pop()
	{
		int last = m_DynArray.Size() - 1;
		return m_DynArray[last];
		m_DynArray.PopBack();
	}

	T Top()
	{
		int last = m_DynArray.Size() - 1;
		return m_DynArray[last];
	}

private:
	DynamicArray<T> m_DynArray;
};