#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "stdafx.h"

class Projectile
{
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	bool m_alive;
	float radius;

public:
	Projectile();
	~Projectile();
	Projectile(sf::Vector2f pos, sf::Vector2f velo);

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow * window);
};

#endif