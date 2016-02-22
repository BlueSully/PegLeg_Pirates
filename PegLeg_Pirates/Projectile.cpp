#include "Projectile.h"

Projectile::Projectile(){

}

Projectile::~Projectile(){

}

<<<<<<< HEAD
Projectile::Projectile(sf::Vector2f position, float velocity)
{
	m_pos = position;
	m_vel = velocity;
=======
Projectile::Projectile(sf::Vector2f pos, float velo)
{
	m_pos = pos;
	m_vel = velo;
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
	m_alive = true;	
	radius = 3;
	m_ttl = 5;
	m_image = sf::CircleShape(radius, 6);
	m_image.setFillColor(sf::Color(190, 190, 190, 255));
	m_image.setOutlineThickness(1);
	m_image.setOutlineColor(sf::Color::Black);
}

bool Projectile::isAlive()
{
	return m_alive;
}

<<<<<<< HEAD
void Projectile::setAlive(bool alive)
{
	m_alive = alive;
}

void Projectile::setDead()
{
	setPos(sf::Vector2f(-10000, -10000));
	setVelo(0);
	setAlive(false);
}

=======
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
sf::Vector2f Projectile::getPos()
{
	return m_pos;
}

<<<<<<< HEAD
void Projectile::setPos(sf::Vector2f position)
{
	m_pos = position;
}

float Projectile::getVelo()
{
	return m_vel;
}

void Projectile::setVelo(float velocity)
{
	m_vel = velocity;
}

=======
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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
<<<<<<< HEAD

	if (m_ttl < 0)
	{
		m_alive = false;
	}
=======
	if (m_ttl < 0)
		m_alive = false;
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
}

void Projectile::draw(sf::RenderWindow * window)
{
	if (m_alive)
	{
		m_image.setPosition(m_pos);
		window->draw(m_image);
	}
}