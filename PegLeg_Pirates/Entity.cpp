#include "Entity.h"

Entity::Entity()
{
	m_isAttacking = false;
	m_canHit = false;
	m_invTime = 0;
}

sf::Vector2f Entity::getPos()
{
	return m_body.getPosition();
}

void Entity::setPos(sf::Vector2f value)
{
	m_body.setPosition(value);
}

void Entity::setPosX(float x)
{
	m_pos.x = x;
}
void Entity::setPosY(float y)
{
	m_pos.y = y;
}

sf::Sprite Entity::getSpriteBody()
{
	return m_body;
}
sf::Sprite Entity::getSpriteBase()
{
	return m_shadow;
}
sf::Sprite Entity::getSpriteWeapon()
{
	return m_weapon;
}

sf::Vector2f Entity::getSize()
{
	return sf::Vector2f(m_bodyWidth, m_bodyHeight);
}

int Entity::getHealth()
{
	return m_health;
}

bool Entity::isAlive()
{
	return m_alive;
}

void Entity::setAlive(bool value)
{
	m_alive = value;
}

bool Entity::isHit()
{
	return m_isHit;
}

void Entity::setIsHit(bool value)
{
	m_isHit = value;
}

bool Entity::canHit()
{
	return m_canHit;
}

void Entity::setCanHit(bool value)
{
	m_canHit = value;
}

float Entity::getHitCoolDown()
{
	return m_invTime;
}

void Entity::setHitCoolDown(float time)
{
	m_invTime = time;
}

void Entity::setSize(sf::Vector2f pos)
{
	m_bodyHeight = pos.x;
	m_bodyWidth = pos.y;
}

void Entity::updateHealth(int value)
{
	if (m_isHit)
	{
		if (value < 0)
		{
			m_health += value;
			m_isHit = false;
		}
		else if (value > 0)
		{
			m_health += value;
		}
	}
}


bool Entity::onSamePlaneY(Entity * entityB)
{
	if (m_shadow.getPosition().y < entityB->getSpriteBase().getPosition().y + entityB->m_shadowHeight &&
		m_shadow.getPosition().y + m_shadowHeight > entityB->getSpriteBase().getPosition().y)
	{
		return true;
	}

	return false;
}

bool Entity::onSamePlaneX(Entity * entityB)
{
	if (m_shadow.getPosition().x < entityB->getPos().x + entityB->m_bodyWidth &&
		m_shadow.getPosition().x + m_shadowWidth > entityB->getPos().x)
	{
		return true;
	}

	return false;
}

bool Entity::onSamePlaneY(sf::Vector2f targetPos, sf::Vector2f targetSize){
	if (m_shadow.getPosition().y < targetPos.y + targetSize.y &&//Checking for intersection of the y plane (at infinity x)
		m_shadow.getPosition().y + m_shadowHeight > targetPos.y ||
		m_shadow.getPosition().y > targetPos.y + targetSize.y &&
		m_shadow.getPosition().y + m_shadowHeight < targetPos.y)
	{
		return true;
	}

	return false;
}

bool Entity::onSamePlaneX(sf::Vector2f targetPos, sf::Vector2f targetSize){
	if (m_shadow.getPosition().x < targetPos.x + targetSize.x &&
		m_shadow.getPosition().x + m_shadowWidth > targetPos.x)
	{
		return true;
	}

	return false;
}