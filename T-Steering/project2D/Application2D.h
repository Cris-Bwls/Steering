#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Vector2.h"
#include <vector>

class Agent;
class Grid;

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;

	Agent* m_pPlayer;
	Grid* m_pGrid;

	float m_cameraX, m_cameraY;
	float m_timer;

	int m_MouseX, m_MouseY;
	int m_MouseScroll;
	float m_Scroll;
};