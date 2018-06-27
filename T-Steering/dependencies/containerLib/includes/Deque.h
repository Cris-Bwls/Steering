#pragma once

#include "LinkedList.h"

template<typename T>
class DeQue
{
public:
	void PushBack(T value)
	{
		data.PushBack(value);
	}

	void PushFront(T value)
	{
		data.PushFront(value);
	}

	T PopBack()
	{
		int last = data.Size() - 1;
		T value = data.GetData(last);
		data.PopBack();
		return value;
	}

	T PopFront()
	{
		T value = data.GetData(0);
		data.PopFront();
		return value;
	}

	int Size()
	{
		return data.Size();
	}

	bool Empty()
	{
		return (data.m_nListSize == 0);
	}

	T ReadBack()
	{
		int last = data.Size() - 1;
		return data.GetData(last);
	}

	T ReadFront()
	{
		return data.GetData(0);
	}

private:
	LinkedList<T> data;
};