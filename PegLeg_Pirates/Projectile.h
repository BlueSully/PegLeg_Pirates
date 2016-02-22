#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "stdafx.h"


class Projectile
{
private:
	sf::Vector2f m_pos;
	float m_vel;
	sf::CircleShape m_image;
	bool m_alive;
	float m_ttl;
	float radius;
	bool m_collide;

public:
	Projectile();
	~Projectile();
	Projectile(sf::Vector2f position, float velocity);

	bool isAlive();
	void setAlive(bool alive);
	void setDead();
	sf::Vector2f getPos();
	void setPos(sf::Vector2f position);
	float getVelo();
	void setVelo(float velocity);
	float getSize();
	bool getCollide();//use for deletion purpose
	void setCollide(bool value);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow * window);
};

#endif