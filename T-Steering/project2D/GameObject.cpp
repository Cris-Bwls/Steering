#include "GameObject.h"



GameObject::GameObject(Vector2 v2Pos, float fRotRadians)
{
	SetPosition(v2Pos);
	SetRotation(fRotRadians);
}


GameObject::~GameObject()
{
}


void GameObject::SetPosition(Vector2 v2Pos)
{
	m_GlobalTransform.SetPosition(v2Pos);
}


Vector2 GameObject::GetPosition()
{
	return m_GlobalTransform.GetPosition();
}


void GameObject::SetRotation(float fRadians)
{
	m_GlobalTransform.SetRotate2D(fRadians);

	m_fRotation = fRadians;
}


float GameObject::GetRotation()
{
	return m_fRotation;
}