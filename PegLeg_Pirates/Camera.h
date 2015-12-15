#ifndef CAMERA_H
#define CAMERA_H

#include "stdafx.h"
#include "Player.h"

using namespace sf;

class Camera{
private:
	Vector2f m_pos;
	Vector2f m_dim;
	Vector2f m_targetPos;

public:
	Camera();
	Camera(Vector2f postion, Vector2f dimensions);
	Vector2f getPosition() const;

	void follow(Vector2f targetPosition, Vector2f targetDim);
	void setTarget(Vector2f targetPosition);
};

#endif