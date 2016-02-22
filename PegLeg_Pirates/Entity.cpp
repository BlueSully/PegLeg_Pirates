#include "Entity.h"

Entity::Entity()
{
	m_isAttacking = false;
<<<<<<< HEAD
	m_canbeHit = false;
=======
	m_canHit = false;
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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
	return sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight);
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

<<<<<<< HEAD
bool Entity::canBeHit()
{
	return m_canbeHit;
=======
bool Entity::canHit()
{
	return m_canHit;
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
}

void Entity::setIsHit(bool value)
{
	m_isHit = value;
}

void Entity::setMaxHealth(int value)
{
	m_maxHealth = value;
}

<<<<<<< HEAD
void Entity::setCanBeHit(bool value)
{
	m_canbeHit = value;
=======
void Entity::setCanHit(bool value)
{
	m_canHit = value;
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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
	m_bodyHeight = (int)pos.x;
	m_bodyWidth = (int)pos.y;
}

void Entity::setActive(bool value)
{
	m_activated = value;
}

bool Entity::isActivated()
{
	return m_activated;
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
		else if (m_health + value > 0)
		{
			m_health += value;
		}
	}
}

<<<<<<< HEAD
bool Entity::onSamePlaneX(Entity * entityB)
{
	if (m_shadow.getPosition().x < entityB->getPos().x + entityB->m_bodyWidth &&
		m_shadow.getPosition().x + m_shadowWidth > entityB->getPos().x)
	{
		return true;
	}

	return false;
}
=======
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f

bool Entity::onSamePlaneY(Entity * entityB)
{
	if (m_shadow.getPosition().y < entityB->getSpriteBase().getPosition().y + entityB->m_shadowHeight &&
		m_shadow.getPosition().y + m_shadowHeight > entityB->getSpriteBase().getPosition().y ||
		m_shadow.getPosition().y > entityB->getSpriteBase().getPosition().y + entityB->m_shadowHeight &&
		m_shadow.getPosition().y + m_shadowHeight < entityB->getSpriteBase().getPosition().y)
	{
		return true;
	}

	return false;
}

<<<<<<< HEAD
bool Entity::onSamePlaneX(sf::Vector2f targetPos, sf::Vector2f targetSize){
	if (m_shadow.getPosition().x < targetPos.x + targetSize.x &&
		m_shadow.getPosition().x + m_shadowWidth > targetPos.x)
=======
bool Entity::onSamePlaneX(Entity * entityB)
{
	if (m_shadow.getPosition().x < entityB->getPos().x + entityB->m_bodyWidth &&
		m_shadow.getPosition().x + m_shadowWidth > entityB->getPos().x)
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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
<<<<<<< HEAD
=======
}

bool Entity::onSamePlaneX(sf::Vector2f targetPos, sf::Vector2f targetSize){
	if (m_shadow.getPosition().x < targetPos.x + targetSize.x &&
		m_shadow.getPosition().x + m_shadowWidth > targetPos.x)
	{
		return true;
	}

	return false;
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
}