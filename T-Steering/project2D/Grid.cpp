#include "Grid.h"

#include "Node.h"
#include <random>

#define GRID_SPACING 2.0f

#define OFFSET_X 350.0f
#define OFFSET_Y 75.0f

#define BLOCKED_NODES 80

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
Grid::Grid()
{
	// Creation
	for (int x = 0; x < GRID_SIZE; ++x)
	{
		for (int y = 0; y < GRID_SIZE; ++y)
		{
			m_pNodes[x][y] = new Node();
			m_pNodes[x][y]->m_v2Pos.x = OFFSET_X + NODE_SIZE * x;
			m_pNodes[x][y]->m_v2Pos.y = OFFSET_Y + NODE_SIZE * y;
			m_pNodes[x][y]->m_nIndexX = x;
			m_pNodes[x][y]->m_nIndexY = y;
			m_pNodes[x][y]->m_nFScore = 0xFFFFFFFF;
		}
	}

	// Connection
	for (int x = 0; x < GRID_SIZE; ++x)
	{
		for (int y = 0; y < GRID_SIZE; ++y)
		{
			m_pNodes[x][y]->m_pNeighbours[0] = nullptr;
			m_pNodes[x][y]->m_pNeighbours[1] = nullptr;
			m_pNodes[x][y]->m_pNeighbours[2] = nullptr;
			m_pNodes[x][y]->m_pNeighbours[3] = nullptr;
			m_pNodes[x][y]->m_pNeighbours[4] = nullptr;
			m_pNodes[x][y]->m_pNeighbours[5] = nullptr;
			m_pNodes[x][y]->m_pNeighbours[6] = nullptr;
			m_pNodes[x][y]->m_pNeighbours[7] = nullptr;

			//Costs
			m_pNodes[x][y]->m_Costs[0] = 10;
			m_pNodes[x][y]->m_Costs[1] = 10;
			m_pNodes[x][y]->m_Costs[2] = 10;
			m_pNodes[x][y]->m_Costs[3] = 10;
			m_pNodes[x][y]->m_Costs[4] = 14;
			m_pNodes[x][y]->m_Costs[5] = 14;
			m_pNodes[x][y]->m_Costs[6] = 14;
			m_pNodes[x][y]->m_Costs[7] = 14;

			// Cardinal

			// Up
			if (y < GRID_SIZE - 1)
				m_pNodes[x][y]->m_pNeighbours[0] = m_pNodes[x][y + 1];

			// Right
			if (x < GRID_SIZE - 1)
				m_pNodes[x][y]->m_pNeighbours[1] = m_pNodes[x + 1][y];

			// Down
			if (y > 0)
				m_pNodes[x][y]->m_pNeighbours[2] = m_pNodes[x][y - 1];

			// Left
			if (x > 0)
				m_pNodes[x][y]->m_pNeighbours[3] = m_pNodes[x - 1][y];

			// Diagonals

			// Top Right
			if (y < GRID_SIZE - 1 && x < GRID_SIZE - 1)
				m_pNodes[x][y]->m_pNeighbours[4] = m_pNodes[x + 1][y + 1];

			// Bottom Right
			if (y > 0 && x < GRID_SIZE - 1)
				m_pNodes[x][y]->m_pNeighbours[5] = m_pNodes[x + 1][y - 1];

			// Bottom Left
			if (y > 0 && x > 0)
				m_pNodes[x][y]->m_pNeighbours[6] = m_pNodes[x - 1][y - 1];

			// Top Left
			if (y < GRID_SIZE - 1 && x > 0)
				m_pNodes[x][y]->m_pNeighbours[7] = m_pNodes[x - 1][y + 1];

			
		}
	}

	// Blocked Node Creation

	for (int i = 0; i < BLOCKED_NODES; ++i)
	{
		int x = rand() % GRID_SIZE;
		int y = rand() % GRID_SIZE;
		m_pNodes[x][y]->m_bBlocked = true;
	}
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
Grid::~Grid()
{
	for (int x = 0; x < GRID_SIZE; ++x)
	{
		for (int y = 0; y < GRID_SIZE; ++y)
		{
			delete m_pNodes[x][y];
		}
	}
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
std::vector<Vector2> Grid::GetPath(Vector2 v2Start, Vector2 v2End, bool AStar)
{
	std::vector<Vector2> path;
	Node* pStart = GetNodeByPos(v2End);
	Node* pEnd = GetNodeByPos(v2Start);

	// Safety Checks
	if (!pStart || !pEnd)
		return path;

	if (pStart->m_bBlocked || pEnd->m_bBlocked)
		return path;

	//Pathfinding
	m_OpenList.clear();
	memset(m_ClosedList, 0, sizeof(bool) * GRID_SIZE * GRID_SIZE);

	pStart->m_nGScore = 0;
	pStart->m_pPrev = nullptr;
	m_OpenList.push_back(pStart);

	while (m_OpenList.size() > 0)
	{
		SortOpenList();

		// Remove lowest node from open list and add to closed list
		Node* pCurrent = m_OpenList[0];
		m_OpenList.erase(m_OpenList.begin());
		m_ClosedList[pCurrent->m_nIndexX][pCurrent->m_nIndexY] = true;

		//Complete path here
		if (pCurrent == pEnd)
		{
			//Path is complete
			path.push_back(pCurrent->m_v2Pos);

			//While current's prev is not null
			while (pCurrent->m_pPrev)
			{
				//Make current currents prev
				pCurrent = pCurrent->m_pPrev;
				path.push_back(pCurrent->m_v2Pos);
			}
			// Return Path
			return path;
		}

		//Loop through all neighbours and add them to open list
		for (int i = 0; i < NEIGHBOUR_COUNT; ++i)
		{
			Node* pNeighbour = pCurrent->m_pNeighbours[i];

			//Skip null neighbours
			if (!pNeighbour)
				continue;

			//Skip blocked neighbours
			if (pNeighbour->m_bBlocked)
				continue;

			//Skip closed list neighbours
			if (m_ClosedList[pNeighbour->m_nIndexX][pNeighbour->m_nIndexY])
				continue;

			//If neighbour is already in open list
			if (std::find(m_OpenList.begin(), m_OpenList.end(), pNeighbour) != m_OpenList.end())
			{
				//Check if this is a better path
				int newGScore = pCurrent->m_nGScore + pCurrent->m_Costs[i];
				if (newGScore < pNeighbour->m_nGScore)
				{
					//Update to use the better path
					pNeighbour->m_nGScore = newGScore;
					pNeighbour->m_nFScore = pNeighbour->m_nGScore + pNeighbour->m_nHScore;

					pNeighbour->m_pPrev = pCurrent;

					m_OpenList.push_back(pNeighbour);
				}
			}
			//ELSE add node to open list and calculate scores
			else
			{
				//Calculate G and F scores (and H for A*)
				pNeighbour->m_nGScore = pCurrent->m_nGScore + pCurrent->m_Costs[i];

				// Calculate H score
				if (AStar)
				{
					int diffX = abs(pEnd->m_nIndexX - pNeighbour->m_nIndexX);
					int diffY = abs(pEnd->m_nIndexY - pNeighbour->m_nIndexY);
					if (diffX > diffY)
					{
						pNeighbour->m_nHScore = (diffY * 14) + ((diffX - diffY) * 10);
					}
					else
					{
						pNeighbour->m_nHScore = (diffX * 14) + ((diffY - diffX) * 10);
					}
				}
				else
				{
					pNeighbour->m_nHScore = 0;
				}

				pNeighbour->m_nFScore = pNeighbour->m_nGScore + pNeighbour->m_nHScore;

				pNeighbour->m_pPrev = pCurrent;

				m_OpenList.push_back(pNeighbour);
			}
		}
	}

	// Returns if no path found
	return path;
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
Node* Grid::GetNodeByPos(Vector2 v2Pos)
{
	int x = (int)((v2Pos.x - OFFSET_X) / NODE_SIZE);
	int y = (int)((v2Pos.y - OFFSET_Y) / NODE_SIZE);

	if (x < 0)
		return nullptr;

	if (y < 0)
		return nullptr;

	if (x >= OFFSET_X)
		return nullptr;

	if (y >= OFFSET_Y)
		return nullptr;

	return m_pNodes[x][y];
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void Grid::SortOpenList()
{
	for (int i = 0; i < m_OpenList.size(); ++i)
	{
		for (int j = 0; j < m_OpenList.size() - 1; ++j)
		{
			if (m_OpenList[j]->m_nFScore > m_OpenList[j + 1]->m_nFScore)
			{
				Node* swap = m_OpenList[j];
				m_OpenList[j] = m_OpenList[j + 1];
				m_OpenList[j + 1] = swap;
			}
		}
	}
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void Grid::Draw(aie::Renderer2D* pRenderer)
{
	for (int x = 0; x < GRID_SIZE; ++x)
	{
		for (int y = 0; y < GRID_SIZE; ++y)
		{	
			pRenderer->setRenderColour(0xFFFFFFFF);

			Vector2 v2Pos = m_pNodes[x][y]->m_v2Pos;
			float fSize = NODE_SIZE - GRID_SPACING;

			if (m_pNodes[x][y]->m_bBlocked)
				pRenderer->setRenderColour(0xFF0000FF);

			pRenderer->drawBox(v2Pos.x,	v2Pos.y, fSize, fSize);

			if (m_pNodes[x][y]->m_bBlocked)
				continue;

			pRenderer->setRenderColour(0x0000FFFF);
			for (int i = 0; i < NEIGHBOUR_COUNT; ++i)
			{
				if (m_pNodes[x][y]->m_pNeighbours[i])
				{
					if (m_pNodes[x][y]->m_pNeighbours[i]->m_bBlocked)
						continue;

					Vector2 v2NeighbourPos = m_pNodes[x][y]->m_pNeighbours[i]->m_v2Pos;
					
					pRenderer->drawLine(v2Pos.x, v2Pos.y, v2NeighbourPos.x, v2NeighbourPos.y, 3);
				}
			}
		}
	}

	pRenderer->setRenderColour(0xFFFFFFFF);
}

