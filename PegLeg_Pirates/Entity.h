#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"
<<<<<<< HEAD
#include "AnimationManager.h"
=======

>>>>>>> 8a8876937c56b69155def7748f90e4598657636f

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
<<<<<<< HEAD
=======
	std::string name;
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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
<<<<<<< HEAD
	bool m_canbeHit;
=======
	bool m_canHit;
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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
<<<<<<< HEAD
	virtual bool canBeHit();
=======
	virtual bool canHit();
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
	virtual bool isAlive();
	virtual int getHealth();
	virtual void setActive(bool value);
	virtual bool isActivated();

	//set methods
	virtual void setIsHit(bool value);
	virtual void setMaxHealth(int value);
<<<<<<< HEAD
	virtual void setCanBeHit(bool value);
=======
	virtual void setCanHit(bool value);
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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