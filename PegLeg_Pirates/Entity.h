#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"
#include "AnimationManager.h"

enum EntityType
{
	PlayerEntity,
	EnemyEntity,
	BossEntity,
	ObjectEntity
};

class Entity
{
protected:
	sf::Vector2f m_pos;

	sf::Sprite m_body;
	sf::Sprite m_shadow;
	sf::Sprite m_weapon;

	float m_invTime;
	int m_bodyHeight;
	int m_bodyWidth;
	int m_shadowHeight;
	int m_shadowWidth;

	bool m_isAttacking;
	bool m_activated;
	bool m_isHit;
	bool m_canbeHit;
	bool m_alive;
	int m_health;
	int m_maxHealth;

public:
	Entity();

	//get Methods
	virtual sf::Sprite getSpriteBody();
	virtual sf::Sprite getSpriteBase();
	virtual sf::Sprite getSpriteWeapon();

	virtual sf::Vector2f Entity::getPos();
	virtual sf::Vector2f getSize();

	virtual bool isHit();
	virtual bool canBeHit();
	virtual bool isAlive();
	virtual int getHealth();
	virtual int getMaxHealth();
	virtual void setActive(bool value);
	virtual bool isActivated();

	//set methods
	virtual void setIsHit(bool value);
	virtual void setHealth(int value);
	virtual void setMaxHealth(int value);
	virtual void setCanBeHit(bool value);
	virtual void setPos(sf::Vector2f value);
	virtual void setPosX(float x);
	virtual void setPosY(float y);
	virtual void setSize(sf::Vector2f pos);
	virtual void setAlive(bool);

	//Methods
	virtual float getHitCoolDown();
	virtual void setHitCoolDown(float myCoolDown);
	virtual void updateHealth(int value);
	
	virtual bool onSamePlaneY(sf::Vector2f targetPos, sf::Vector2f targetSize);
	virtual bool onSamePlaneX(sf::Vector2f targetPos, sf::Vector2f targetSize);
	virtual bool onSamePlaneY(Entity * entityB);
	virtual bool onSamePlaneX(Entity * entityB);

	virtual void draw(sf::RenderWindow * window) = 0;
};

#endif