#ifndef ENEMYSWORD_H
#define ENEMYSWORD_H

#include "Player.h"
#include "Entity.h"

class EnemySword : public Entity{
private:
	int m_offsetpixelsX;
	bool m_attackSideRight = true;
	bool m_attackSideLeft = false;
	bool m_activated = false;
	float m_speed;
	float animationtime = 1;
	sf::Color orgColour;
	

	sf::Vector2f m_weaponSize;
public:
	EnemySword();
	~EnemySword();
	float timeToAttack;
	bool getAttack();
	void initialise(sf::Vector2f value, sf::Texture &, sf::Texture &, sf::Texture &, int index);

	void changeColour();
	void setActive(bool value);
	bool isActivated();
	bool checkCanAttack(sf::Time deltaTime, sf::Vector2f targetBasePos, sf::Vector2f targetBaseSize);
	void checkAttackCollision(sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize);
	void moveToward(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize);
	void update(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize);
	virtual void draw(sf::RenderWindow * window);
};

#endif