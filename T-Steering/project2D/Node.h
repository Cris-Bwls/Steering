#pragma once
#include "Vector2.h"

#define NEIGHBOUR_COUNT 8

struct Node
{
	Vector2 m_v2Pos;
	Node* m_pNeighbours[NEIGHBOUR_COUNT];
	int m_Costs[NEIGHBOUR_COUNT];

	Node* m_pPrev = nullptr;

	int m_nIndexX = 0;
	int m_nIndexY = 0;

	int m_nFScore = 0;
	int m_nGScore = 0;
	int m_nHScore = 0;

	bool m_bBlocked = false;
};