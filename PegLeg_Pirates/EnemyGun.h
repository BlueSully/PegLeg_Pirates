#ifndef ENEMYGUN_H
#define ENEMYGUN_H

#include "Entity.h"
#include "ProjectileManager.h"

class EnemyGun : public Entity{
private:
	AnimationManager animationM;
	int m_offsetpixelsX;
	bool m_attackSideRight = true;
	bool m_attackAnimation = false;
	bool m_activated = false;
	bool m_firedGun;
	float m_speed;
	int framecount = 0;
	float animationtime = 1;
	bool m_CannotmoveRight = false;
	bool m_CannotmoveLeft = false;
	sf::Color orgColour;
	sf::Vector2f m_weaponSize;
	int m_NumbodySprites;
	int m_bodyHeight;
	int m_bodyWidth;

public:
	EnemyGun();
	~EnemyGun();

	void initialise(sf::Vector2f value, sf::Texture &, sf::Texture &, sf::Texture &, int index);
	virtual void setPos(sf::Vector2f value);
	float timeToAttack;
	bool getAttack();
	void setActive(bool value);
	bool isActivated();

	void attackRangedController(sf::Time deltaTime, ProjectileManager *manager);
	bool checkCanAttack(sf::Time deltaTime, sf::Vector2f targetBasePos, sf::Vector2f targetBaseSize);
	void checkAttackCollision(sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize);
	void moveToward(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize, sf::IntRect viewport);
	void update(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize, ProjectileManager *manager, sf::IntRect viewport);
	virtual void draw(sf::RenderWindow * window);
};

#endif