#pragma once
#include "DynamicArray.h"
#include <functional>

template<typename T>
struct HeapNode
{
	HeapNode<T>* m_pParent = nullptr;
	HeapNode<T>* m_pChild1 = nullptr;
	HeapNode<T>* m_pChild2 = nullptr;

	T m_data;
};

template<typename T>
class Heap
{
public:
	// Constructor
	Heap(bool bMax = true)
	{
		m_bMax = bMax;

		if (bMax)
		{
			CompareFunc = [](T a, T b)
			{
				if (a > b)
					return true;
				return false;
			};
		}
		else
		{
			CompareFunc = [](T a, T b)
			{
				if (a < b)
					return true;
				return false;
			};
		}
	}

	// Destructor
	~Heap()
	{
		Clear();
	}

	// Insert
	void Insert(T data)
	{
		HeapNode<T>* pHeapNode = new HeapNode<T>();
		pHeapNode->m_data = data;

		int size = m_Array.Size();

		if (size == 0)
		{
			m_Array.PushBack(pHeapNode);
		}
		else
		{
			pHeapNode->m_pParent = FindParent(size);

			if (size % 2)
			{
				pHeapNode->m_pParent->m_pChild2 = pHeapNode;
			}
			else
			{
				pHeapNode->m_pParent->m_pChild1 = pHeapNode;
			}

			m_Array.PushBack(pHeapNode);
			UpHeap(size);
		}
	}
	
	// Remove
	T Remove(int index)
	{
		HeapNode<T>* indexNode = m_Array.m_pData[index];
		HeapNode<T>* lastNode = m_Array.m_pData[m_Array.Size() - 1];

		T result = indexNode->m_data;
		indexNode->m_data = lastNode->m_data;
		delete m_Array.PopBack();

		DownHeap(index);

		return result;
	}

	// Pop
	T Pop()
	{
		return Remove(0);
	}

	// Peek
	T Peek()
	{
		return m_Array.m_pData[0].m_data;
	}
	
	//--------------------------------------------------
	// Size
	//
	//		return (int):
	//			Size of Array	
	//--------------------------------------------------
	int Size()
	{
		return m_Array.m_nUsed;
	}

	//--------------------------------------------------
	// [] Operator Overload
	//
	//		index (int):
	//			position in array
	//--------------------------------------------------
	T& operator[] (int index)
	{
		//WRONG
		return m_Array.m_pData[index];
	}

	// Step


	// Clear
	void Clear()
	{
		while (m_Array.Size > 0)
		{
			delete m_Array.PopBack();
		}
	}

	// SetCompareFunc
	void SetCompareFunc(std::function<bool(T, T)> Func)
	{
		CompareFunc = Func;
	}


private:
	HeapNode<T>* FindParent(int index)
	{
		int parentIndex = (index - 1) / 2;
		if (parentIndex < m_Array.Size())
		{
			return m_Array[parentIndex];
		}
		return nullptr;
	}

	HeapNode<T>* FindChild(int index, bool bFirstChild)
	{
		int childIndex;
		if (bFirstChild)
			childIndex = 2 * index + 1;
		else
			childIndex = 2 * index + 2;

		if (childIndex < m_Array.Size())
		{
			return m_Array[childIndex];
		}
		return nullptr;
	}

	void DownHeap(int index)
	{
		HeapNode<T>* dataNode = m_Array.m_pData[index];
		HeapNode<T>* ChildNode1 = dataNode->m_pChild1;
		HeapNode<T>* ChildNode2 = dataNode->m_pChild2;

		bool bCanSwap = true;
		while (bCanSwap)
		{
			if (CompareFunc(ChildNode1, ChildNode2))
			{
				if (CompareFunc(ChildNode1, dataNode))
				{
					T temp = dataNode->m_data;
					ChildNode1->m_data = dataNode->m_data;

					dataNode = ChildNode1;
				}
				else if (CompareFunc(ChildNode2, dataNode))
				{
					T temp = dataNode->m_data;
					ChildNode2->m_data = dataNode->m_data;

					dataNode = ChildNode2;
				}
				else
				{
					bCanSwap = false;
				}
			}
			else
			{
				if (CompareFunc(ChildNode2, dataNode))
				{
					T temp = dataNode->m_data;
					ChildNode2->m_data = dataNode->m_data;

					dataNode = ChildNode2;
				}
				else if (CompareFunc(ChildNode1, dataNode))
				{
					T temp = dataNode->m_data;
					ChildNode1->m_data = dataNode->m_data;

					dataNode = ChildNode1;
				}
				else
				{
					bCanSwap = false;
				}
			}

			ChildNode1 = dataNode->m_pChild1;
			ChildNode2 = dataNode->m_pChild2;
		}
	}

	void UpHeap(int index)
	{
		HeapNode<T>* dataNode = m_Array.m_pData[index];
		HeapNode<T>* parentNode = dataNode->m_pParent;

		while (CompareFunc(dataNode, parentNode))
		{
			T temp = dataNode->m_data;
			parentNode->m_data = dataNode->m_data;

			dataNode = parentNode;
			parentNode = dataNode->m_pParent;

			if (!parentNode)
				continue;
		}
	}

	//VARIABLES
	std::function<bool(T, T)> CompareFunc;
	DynamicArray<HeapNode<T>*> m_Array;

	bool m_bMax;
};