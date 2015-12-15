#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"

class Entity
{
protected:
	std::string name;
	sf::Vector2f m_pos;

	sf::Sprite m_body;//replace all with sprites
	sf::Sprite m_shadow;
	sf::Sprite m_weapon;

	float m_invTime;
	float m_bodyHeight;
	float m_bodyWidth;
	float m_shadowHeight;
	float m_shadowWidth;

	bool m_isAttacking;
	bool m_isHit;
	bool m_canHit;
	bool m_alive;
	int m_health;

public:
	Entity();

	//get Methods
	sf::Sprite getSpriteBody();
	sf::Sprite getSpriteBase();
	sf::Sprite getSpriteWeapon();

	virtual sf::Vector2f Entity::getPos();
	virtual sf::Vector2f getSize();

	bool isHit();
	bool canHit();
	bool isAlive();
	int getHealth();

	//set methods
	void setIsHit(bool value);
	void setCanHit(bool value);
	void setPos(sf::Vector2f value);
	void setPosX(float x);
	void setPosY(float y);
	void setSize(sf::Vector2f pos);
	void setAlive(bool);

	//Methods
	float getHitCoolDown();
	void setHitCoolDown(float myCoolDown);
	void updateHealth(int value);
	
	bool onSamePlaneY(sf::Vector2f targetPos, sf::Vector2f targetSize);
	bool onSamePlaneX(sf::Vector2f targetPos, sf::Vector2f targetSize);
	bool onSamePlaneY(Entity * entityB);
	bool onSamePlaneX(Entity * entityB);

	virtual void draw(sf::RenderWindow * window) = 0;
};

#endif