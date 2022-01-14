#pragma once

#include "EliteMath/EMath.h"

class GameObject
{
public:
	GameObject() = default;;
	GameObject(Elite::Vector2 pos)
	:m_pos(pos){};
	~GameObject() = default;

	void SetPosition(Elite::Vector2 pos) { m_pos = pos; };
	Elite::Vector2 GetPosition() const { return m_pos; };

protected:
	Elite::Vector2 m_pos;
};


