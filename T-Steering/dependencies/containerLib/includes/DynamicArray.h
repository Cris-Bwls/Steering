#pragma once

#include <memory.h>
#include "EnumPrimitiveTypes.h"

template<typename T>
class DynamicArray
{
public:
	//--------------------------------------------------
	// Constructor
	//
	//			initSize (int):
	//				determines inital size of array
	//--------------------------------------------------
	DynamicArray(int initSize = 1)
	{
		m_pData = new T[initSize];
		m_nCapacity = initSize;
		m_nUsed = 0;
	}

	//--------------------------------------------------
	// Destructor
	//--------------------------------------------------
	~DynamicArray()
	{
		delete m_pData;
	}

	//--------------------------------------------------
	// PushBack
	//		Adds data to end of array
	//		
	//			data (T):
	//				data to be added
	//--------------------------------------------------
	void PushBack(T data)
	{
		if (m_nUsed >= m_nCapacity - 1)
		{
			Resize();
		}
		m_pData[m_nUsed] = data;
		++m_nUsed;
	}

	//--------------------------------------------------
	// PushFront
	//		Adds data to end of array
	//		
	//			data (T):
	//				data to be added
	//--------------------------------------------------
	void PushFront(T data)
	{
		PushPoint(data, 0);
	}

	//--------------------------------------------------
	// PushPoint
	//		Adds data at point in array
	//			data (T):
	//				data to be added
	//			point (int):
	//				point to add data
	//--------------------------------------------------
	void PushPoint(T data, int point)
	{
		if (m_nUsed >= m_nCapacity - 1)
		{
			Resize();
		}
		memcpy(&m_pData[point + 1], &m_pData[point], sizeof(T) * (m_nUsed - point));
		m_pData[point] = data;
		++m_nUsed;
	}

	//--------------------------------------------------
	// PopBack
	//		Deletes data at end of array
	//--------------------------------------------------
	T PopBack()
	{
		T data = m_pData[m_nUsed];
		m_nUsed--;
		return data;
	}

	//--------------------------------------------------
	// PopPoint
	//		Deletes data at point in array
	//
	//			point (int):
	//				point in array
	//			isOrdered (bool):
	//				Determines if array should keep its order
	//--------------------------------------------------
	T PopPoint(int point, bool isOrdered = false)
	{
		T data = m_pData[point];
		if (!isOrdered)
		{
			m_pData[point] = m_pData[m_nUsed - 1];
			m_nUsed--;
		}
		else
		{
			memcpy(&m_pData[point], &m_pData[point + 1], sizeof(T) * (m_nUsed - (point + 1)));
			m_nUsed--;
		}
		return data;
	}

	//--------------------------------------------------
	// Size
	//
	//		return (int):
	//			Size of Array	
	//--------------------------------------------------
	int Size()
	{
		return m_nUsed;
	}

	//--------------------------------------------------
	// [] Operator Overload
	//
	//		index (int):
	//			position in array
	//--------------------------------------------------
	T& operator[] (int index)
	{
		return m_pData[index];
	}

	//--------------------------------------------------
	// Sort
	//		Sorts Dynamic Array
	//
	//			ePrimitiveType (EPrimitiveTypes)
	//				Primitive type to sort by
	//--------------------------------------------------
	void Sort(EPrimitiveTypes ePrimitiveType)
	{
		switch (ePrimitiveType)
		{
		case EPRIMITIVETYPES_BOOL:
			// WIP
			break;
		case EPRIMITIVETYPES_CHAR:
			// WIP
			break;
		case EPRIMITIVETYPES_INT:
			SortInt();
			break;
		case EPRIMITIVETYPES_FLOAT:
			// WIP
			break;
		default:
			break;
		}
	}

	//-------------------------------------------------------------------
	// Binary Search
	//		Perform a Binary search on Dynamic array looking for value
	//
	//			return (int): position of value in array
	//-------------------------------------------------------------------
	int BinarySearch(int value)
	{
		// Binary Search for position of value in Dynamic Array
		int nMax = m_nUsed - 1;
		int nMin = 0;
		int nMid;

		while (nMax >= nMin)
		{
			nMid = (nMin + nMax) / 2;

			if (m_pData[nMid] == value)
			{	// position of value is nMid
				return nMid;
			}
			else if (m_pData[nMid] > value)
			{
				nMax = nMid - 1;
			}
			else if (m_pData[nMid] < value)
			{
				nMin = nMid + 1;
			}
		}

		return nMid;
	}

private:
	//--------------------------------------------------
	// Resize
	//		Private Resize function
	//		Grows array
	//--------------------------------------------------
	void Resize()
	{
		m_nCapacity = (m_nCapacity * 1.5) + 1;
		T* pTemp = new T[m_nCapacity];
		memcpy(pTemp, m_pData, sizeof(T)*m_nUsed);
		delete[] m_pData;
		m_pData = pTemp;
	}

	//--------------------------------------------------
	// SortInt
	//		Sorts Dynamic Array by Integer
	//--------------------------------------------------
	void SortInt()
	{
		int max = getMax();

		for (int exp = 1; max / exp > 0; exp *= 10)
		{
			countSort(exp);
		}
	}

	//--------------------------------------------------
	// CountSort
	//		CountSorts
	//--------------------------------------------------
	void countSort(int exp)
	{
		// Count[i] array will be counting the number of array values having that 'i' digit at their (exp)th place.  
		int* output = new int[m_nUsed], i, count[10] = { 0 };

		// Count the number of times each digit occurred at (exp)th place in every input.
		for (i = 0; i < m_nUsed; i++)
		{
			count[(m_pData[i] / exp) % 10]++;
		}

		// Calculating their cumulative count.
		for (i = 1; i < 10; i++)
		{
			count[i] += count[i - 1];
		}

		// Inserting values according to the digit '(arr[i] / exp) % 10' fetched into count[(arr[i] / exp) % 10].
		for (i = m_nUsed - 1; i >= 0; i--)
		{
			output[count[(m_pData[i] / exp) % 10] - 1] = m_pData[i];
			count[(m_pData[i] / exp) % 10]--;
		}

		// Assigning the result to the arr pointer of main().
		for (i = 0; i < m_nUsed; i++)
		{
			m_pData[i] = output[i];
		}

		delete[] output;
	}

	//--------------------------------------------------
	// GetMax
	//		Gets Max value in array
	//--------------------------------------------------
	int getMax()
	{
		int max = m_pData[0];
		for (int i = 1; i < m_nUsed; i++)
		{
			if (m_pData[i] > max)
			{
				max = m_pData[i];
			}
		}
		return max;
	}

	//--------------------------------------------------
	// Variables
	//--------------------------------------------------
	T* m_pData;
	int m_nCapacity;
	int m_nUsed;
};