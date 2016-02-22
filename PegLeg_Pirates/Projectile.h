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
<<<<<<< HEAD
	Projectile(sf::Vector2f position, float velocity);

	bool isAlive();
	void setAlive(bool alive);
	void setDead();
	sf::Vector2f getPos();
	void setPos(sf::Vector2f position);
	float getVelo();
	void setVelo(float velocity);
=======
	Projectile(sf::Vector2f pos, float velo);

	bool isAlive();
	sf::Vector2f getPos();
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
	float getSize();
	bool getCollide();//use for deletion purpose
	void setCollide(bool value);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow * window);
};

#endif