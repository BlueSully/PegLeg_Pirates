#include "Projectile.h"

Projectile::Projectile(){

}

Projectile::~Projectile(){

}

Projectile::Projectile(sf::Vector2f pos, float velo)
{
	m_pos = pos;
	m_vel = velo;
	m_alive = true;	
	radius = 5;
	m_ttl = 5;
	m_image = sf::CircleShape(radius, 6);
}

bool Projectile::isAlive()
{
	return m_alive;
}

sf::Vector2f Projectile::getPos()
{
	return m_pos;
}

float Projectile::getSize()
{
	return radius;
}

bool Projectile::getCollide()
{
	return m_collide;
}

void Projectile::setCollide(bool value)
{
	m_collide = value;
}

void Projectile::update(sf::Time deltaTime)
{
	m_pos += sf::Vector2f(m_vel * deltaTime.asSeconds(), 0);
	m_ttl -= deltaTime.asSeconds();
	if (m_ttl < 0)
		m_alive = false;
}

void Projectile::draw(sf::RenderWindow * window)
{
	if (m_alive)
	{
		m_image.setPosition(m_pos);
		window->draw(m_image);
	}
}