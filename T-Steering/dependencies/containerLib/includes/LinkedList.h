#pragma once

template<typename T>
struct LinkedListNode
{
	LinkedListNode<T>* m_pNext;
	LinkedListNode<T>* m_pPrev;

	T m_data;
};

template<typename T>
class LinkedList
{
public:
	//--------------------------------------------------
	//	Constructor
	//--------------------------------------------------
	LinkedList()
	{
		m_pStart = new LinkedListNode<T>();
		m_pStart->m_pNext = m_pEnd;
		m_pStart->m_pPrev = nullptr;

		m_pEnd = new LinkedListNode<T>();
		m_pEnd->m_pNext = nullptr;
		m_pEnd->m_pPrev = m_pStart;

		m_nListSize = 0;
	}

	//--------------------------------------------------
	//	Destructor
	//--------------------------------------------------
	~LinkedList() 
	{
		Clear();

		delete m_pStart;
		delete m_pEnd;

		m_pStart = nullptr;
		m_pEnd = nullptr;
	}

	//--------------------------------------------------
	//	Clear
	//		Deletes all in List
	//--------------------------------------------------
	void Clear()
	{
		while (m_pStart->m_pNext != m_pEnd)
		{
			PopPoint(m_pStart->m_pNext);
		}
	}

	//--------------------------------------------------
	//	PushFront
	//		Adds to the front of the list
	//
	//			value (T):
	//				data to be stored
	//--------------------------------------------------
	void PushFront(T value)
	{
		PushPoint(value, m_pStart, m_pStart->m_pNext);
	}

	//--------------------------------------------------
	//	PushBack
	//		Adds to the back of the list
	//
	//			value (T):
	//				data to be stored
	//--------------------------------------------------
	void PushBack(T value)
	{
		PushPoint(value, m_pEnd->m_pPrev, m_pEnd); //HERE
	}

	//--------------------------------------------------
	//	GetStart
	//		Gets start sentinel of list
	//
	//			return (LinkedListNode<T>*):
	//				returns start sentinel of list
	//--------------------------------------------------
	LinkedListNode<T>* GetStart()
	{
		return m_pStart;
	}

	//--------------------------------------------------
	//	GetEnd
	//		Gets end sentinel of list
	//
	//			return (LinkedListNode<T>*):
	//				returns end sentinel of list
	//--------------------------------------------------
	LinkedListNode<T>* GetEnd()
	{
		return m_pEnd;
	}

	//--------------------------------------------------
	//	GetData
	//		gets Data from point in list
	//
	//			index (int):
	//				point to get data
	//
	//			return (T):
	//				data from index
	//--------------------------------------------------
	T& GetData(int index)
	{
		int count = 0;
		LinkedListNode<T>* pCurrent;

		if (index < m_nListSize / 2)
		{
			pCurrent = m_pStart->m_pNext;

			while (pCurrent != m_pEnd)
			{
				if (index == count)
				{
					return pCurrent->m_data;
				}
				pCurrent = pCurrent->m_pNext;
				++count;
			}
		}
		else
		{
			pCurrent = m_pEnd->m_pPrev;
			count = m_nListSize - 1;
			while (pCurrent != m_pStart)
			{
				if (index == count)
				{
					return pCurrent->m_data;
				}
				pCurrent = pCurrent->m_pPrev;
				--count;
			}
		}
		return pCurrent->m_data;
	}

	//--------------------------------------------------
	// [] Operator Overload
	//
	//		index (int):
	//			position in array
	//--------------------------------------------------
	T& operator[] (int index)
	{
		return GetData(index);
	}

	//--------------------------------------------------
	//	PushPoint
	//		Inserts new entry into list, 
	//		extending list
	//
	//		value (T):
	//			data to be stored
	//		pNodePrev (LinkedListNode<T>*):
	//			pointer to previous entry in list
	//		pNodeNext (LinkedListNode<T>*):
	//			pointer to next entry in list
	//--------------------------------------------------
	void PushPoint(T value, LinkedListNode<T>* pNodePrev, LinkedListNode<T>* pNodeNext)
	{
		LinkedListNode<T>* pNewNode = new LinkedListNode<T>();
		pNewNode->m_data = value;

		pNewNode->m_pPrev = pNodePrev;
		pNewNode->m_pNext = pNodeNext;

		pNodePrev->m_pNext = pNewNode;
		pNodeNext->m_pPrev = pNewNode;

		++m_nListSize;
	}

	//--------------------------------------------------
	//	PopPoint
	//		deletes entry in list at a point
	//
	//			pNode (LinkedListNode<T>*):
	//				 pointer to entry to be deleted
	//--------------------------------------------------
	void PopPoint(LinkedListNode<T>* pNode)
	{
		pNode->m_pNext->m_pPrev = pNode->m_pPrev;
		pNode->m_pPrev->m_pNext = pNode->m_pNext;

		delete pNode;

		--m_nListSize;
	}

	//--------------------------------------------------
	// PopBack
	//
	//--------------------------------------------------
	void PopBack()
	{
		PopPoint(m_pEnd->m_pPrev);
	}

	//--------------------------------------------------
	// PopFront
	//
	//--------------------------------------------------
	void PopFront()
	{
		PopPoint(m_pStart->m_pNext);
	}

	//--------------------------------------------------
	// Size
	//
	//		index (int):
	//			position in array
	//--------------------------------------------------
	int Size()
	{
		return m_nListSize;
	}

private:

	LinkedListNode<T>* m_pStart;
	LinkedListNode<T>* m_pEnd;

	int m_nListSize;
};