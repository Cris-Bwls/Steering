#include "Duck.h"

#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WanderBehaviour.h"

#include "Grid.h"

Duck::Duck(aie::Texture* pTexture, Grid* pGrid, Vector2 v2Pos, float fRotRadians) :
	Agent(pTexture, v2Pos, fRotRadians)
{
	m_fMaxSpeed = 300.0f;

	m_pSeekBehaviour = new SeekBehaviour();
	AddBehaviour(m_pSeekBehaviour, 0.75f);

	m_pFleeBehaviour = new FleeBehaviour();
	AddBehaviour(m_pFleeBehaviour, 0.25f);

	m_pWanderBehaviour = new WanderBehaviour(25.0f, 15.0f, 1.0f);
	AddBehaviour(m_pWanderBehaviour, 0.5f);

	m_pGrid = pGrid;
	m_Path = m_pGrid->GetPath(Vector2(415, 315), Vector2(815, 615), true);
}


Duck::~Duck()
{
	delete m_pWanderBehaviour;
	delete m_pFleeBehaviour;
	delete m_pSeekBehaviour;
}

void Duck::Update(float fDeltaTime)
{
	/*
	Vector2 v2Dist = GetPosition() - Vector2(300, 300);
	float fDist = v2Dist.magnitude();

	float fFlee = 1.0f - (fDist / 300);
	if (fFlee < 0)
	{
		fFlee = 0;
	}
	else if (fFlee > 1)
	{
		fFlee = 1;
	}

	m_pFleeBehaviour->m_fWeighting = fFlee;
	m_pSeekBehaviour->m_fWeighting = 1.0f - fFlee;
	*/

	m_pFleeBehaviour->m_fWeighting = 0.0f;
	m_pSeekBehaviour->m_fWeighting = 0.0f;
	m_pWanderBehaviour->m_fWeighting = 1.0f;

	Agent::Update(fDeltaTime);
}

void Duck::Draw(aie::Renderer2D* pRenderer2D)
{
	pRenderer2D->setRenderColour(0x00FF00FF);
	for (int i = 0; i < m_Path.size(); ++i)
	{
		pRenderer2D->drawBox(m_Path[i].x, m_Path[i].y, NODE_SIZE, NODE_SIZE);
	}

	pRenderer2D->setRenderColour(0x00FFFFFF);
	pRenderer2D->drawBox(m_Path[0].x, m_Path[0].y, NODE_SIZE, NODE_SIZE);

	pRenderer2D->setRenderColour(0xFFFF00FF);
	pRenderer2D->drawBox(m_Path[m_Path.size() - 1].x, m_Path[m_Path.size() - 1].y, NODE_SIZE, NODE_SIZE);

	pRenderer2D->setRenderColour(0xFFFFFFFF);
	Agent::Draw(pRenderer2D);
}