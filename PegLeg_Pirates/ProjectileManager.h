#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include "Projectile.h"
#include "stdafx.h"

class ProjectileManager
{
private:
	std::vector<Projectile*> enemybulletArray;
	std::vector<Projectile*> playerbulletArray;
public:
	ProjectileManager();
	~ProjectileManager();

	std::vector<Projectile*> getEnemyBulletArray();
	std::vector<Projectile*> getPlayerBulletArray();

	void createProjectile(sf::Vector2f position, float velocity, int id);
	bool checkCollisions(sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, int id);
	bool checkBullet(Projectile* bullet, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize);
	void update(sf::Time deltatime);
	void draw(sf::RenderWindow * window);
};

#endif
