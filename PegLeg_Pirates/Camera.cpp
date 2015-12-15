#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(Vector2f postion, Vector2f dimensions)
{
	m_pos = postion;
	m_dim = dimensions;
}

Vector2f Camera::getPosition() const
{
	return m_pos;
}

void Camera::follow(Vector2f targetPosition, Vector2f targetDim)
{
	//follow target
	if (m_pos.x > targetPosition.x)
	{
		m_pos.x = targetPosition.x;
	}
	else if (m_pos.x + m_dim.x / 2 < targetPosition.x + targetDim.x)
	{
		m_pos.x = targetPosition.x + targetDim.x - m_dim.x / 2;
	}

	if (m_pos.y > targetPosition.y)
	{
		m_pos.y = targetPosition.y;
	}
	else if (m_pos.y + m_dim.y / 2 < targetPosition.y + targetDim.x)
	{
		m_pos.y = targetPosition.y + targetDim.x - m_dim.y / 2;
	}

	////world boundaries
	//if (m_pos.x < 0)
	//{
	//	m_pos.x = 0;
	//}
	//if (m_pos.x + this.camWidth > mapWidth)
	//{
	//	m_pos.x = mapWidth - this.camWidth;
	//}

	//if (m_pos.y < 0)
	//{
	//	m_pos.y = 0;
	//}
	//if (m_pos.y + this.camHeight > mapHeight)
	//{
	//	m_pos.y = mapHeight - this.camHeight;
	//}
}

void Camera::setTarget(Vector2f targetPosition)
{
	m_targetPos = targetPosition;
}