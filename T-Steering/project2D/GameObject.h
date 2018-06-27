#pragma once
#include "Renderer2D.h"
#include "Matrix3.h"
#include "Vector2.h"

class GameObject
{
public:
	GameObject(Vector2 v2Pos, float fRotRadians = 0.0f);
	virtual ~GameObject();

	virtual void Update(float fDeltaTime) = 0;
	virtual void Draw(aie::Renderer2D* pRenderer) = 0;

	void SetPosition(Vector2 v2Pos);
	Vector2 GetPosition();

	void SetRotation(float fRadians);
	float GetRotation();

protected:
	Matrix3 m_GlobalTransform;
	float m_fRotation;
};

