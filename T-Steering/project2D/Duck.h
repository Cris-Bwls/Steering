#pragma once
#include "Agent.h"
#include <vector>
#include "Vector2.h"

class SeekBehaviour;
class FleeBehaviour;
class WanderBehaviour;
class Grid;

class Duck :
	public Agent
{
public:
	Duck(aie::Texture* pTexture, Grid* pGrid, Vector2 v2Pos, float fRotRadians = 0.0f);
	~Duck();

	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer2D);

private:
	SeekBehaviour* m_pSeekBehaviour;
	FleeBehaviour* m_pFleeBehaviour;
	WanderBehaviour* m_pWanderBehaviour;

	Grid* m_pGrid;
	std::vector<Vector2> m_Path;
};

