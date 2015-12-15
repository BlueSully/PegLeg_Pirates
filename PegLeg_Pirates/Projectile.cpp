#include "Projectile.h"

Projectile::Projectile(){


}

Projectile::~Projectile(){


}

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f velo)
{
	m_pos = pos;
	m_vel = velo;
	m_alive = true;
	radius = 5;
}

void Projectile::update(sf::Time deltaTime)
{
	m_pos += sf::Vector2f(m_vel.x * deltaTime.asSeconds(), m_vel.y * deltaTime.asSeconds());
}

void Projectile::draw(sf::RenderWindow * window)
{
	sf::CircleShape m_image = sf::CircleShape(radius, 6);
	m_image.setPosition(m_pos);
	window->draw(m_image);
}