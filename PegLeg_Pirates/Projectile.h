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
	Projectile(sf::Vector2f pos, float velo);

	bool isAlive();
	sf::Vector2f getPos();
	float getSize();
	bool getCollide();//use for deletion purpose
	void setCollide(bool value);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow * window);
};

#endif