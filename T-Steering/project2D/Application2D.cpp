#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Duck.h"
#include "Grid.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	

	m_pGrid = new Grid();
	m_pPlayer = new Duck(m_shipTexture, m_pGrid, Vector2(500, 400));

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;

	return true;
}

void Application2D::shutdown() {
	
	delete m_pPlayer;
	delete m_pGrid;

	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	//Get Mouse Pos
	input->getMouseXY(&m_MouseX, &m_MouseY);

	if (m_MouseScroll == (int)input->getMouseScroll())
	{
		m_Scroll = 0.0f;
	}
	else if (m_MouseScroll > (int)input->getMouseScroll())
	{
		m_MouseScroll = (int)input->getMouseScroll();
		m_Scroll = 0.1f;
	}
	else if (m_MouseScroll < (int)input->getMouseScroll())
	{
		m_MouseScroll = (int)input->getMouseScroll();
		m_Scroll = -0.1f;
	}

	// use arrow keys to move camera

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		m_cameraY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		m_cameraY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_cameraX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_cameraX += 500.0f * deltaTime;

	// Update Player
	m_pPlayer->Update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	float scale = m_2dRenderer->getCameraScale();
	scale += m_Scroll;

	if (scale < 0.1f)
		scale = 0.1f;

	if (scale > 10.0f)
		scale = 10.0f;

	m_2dRenderer->setCameraScale(scale);

	// begin drawing sprites
	m_2dRenderer->begin();

	m_pGrid->Draw(m_2dRenderer);
	m_pPlayer->Draw(m_2dRenderer);
	
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);



	// done drawing sprites
	m_2dRenderer->end();
}