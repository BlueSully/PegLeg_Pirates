#include "ProjectileManager.h"

enum EntityType
{
	PlayerEntity,
	EnemyEntity,
	BossEntity,
	ObjectEntity
};

ProjectileManager::ProjectileManager()
{
	enemybulletArray.reserve(25);
	playerbulletArray.reserve(25);
}

ProjectileManager::~ProjectileManager()
{
	std::cout << "ProjectileManager DESTROYED" << std::endl;
	for (std::vector<Projectile *>::const_iterator it = playerbulletArray.begin(); it != playerbulletArray.end(); it++)
	{
		delete *it;
	}
	playerbulletArray.clear();

	for (std::vector<Projectile *>::const_iterator it = enemybulletArray.begin(); it != enemybulletArray.end(); it++)
	{
		delete *it;
	}
	enemybulletArray.clear();
}

std::vector<Projectile*> ProjectileManager::getEnemyBulletArray()
{
	return enemybulletArray;
}

std::vector<Projectile*> ProjectileManager::getPlayerBulletArray()
{
	return playerbulletArray;
}

void ProjectileManager::createProjectile(sf::Vector2f position, float velocity, int id)
{
	if (id == EntityType::EnemyEntity)//if enemy ranged shot
	{
		Projectile *projectile = new Projectile(position, velocity);
		enemybulletArray.push_back(projectile);
	}
	else if (id == EntityType::PlayerEntity)//if player shot
	{
		Projectile *projectile = new Projectile(position, velocity);
		playerbulletArray.push_back(projectile);
	}
}

bool ProjectileManager::checkCollisions(sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, int id)
{
	if (id == EntityType::EnemyEntity)//if enemy
	{
		if (playerbulletArray.size() > 0)
		{
			for (size_t i = 0; i < playerbulletArray.size(); i++)
			{
				if (checkBullet(playerbulletArray[i], targetbodyPos, targetbodysize))
				{
					playerbulletArray[i]->setCollide(true);
					return true;
				}
			}
		}
	}
	else if (id == EntityType::PlayerEntity)//if player 
	{
		if (enemybulletArray.size() > 0)
		{
			for (size_t i = 0; i < enemybulletArray.size(); i++)
			{
				if (checkBullet(enemybulletArray[i], targetbodyPos, targetbodysize))
				{
					enemybulletArray[i]->setCollide(true);
					return true;
				}
			}
		}
	}

	return false;
}

bool ProjectileManager::checkBullet(Projectile* bullet, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize)
{
	if ((bullet->getPos().x < targetbodyPos.x + targetbodysize.x &&
		bullet->getPos().x + bullet->getSize() > targetbodyPos.x &&
		bullet->getPos().y < targetbodyPos.y + targetbodysize.y &&
		bullet->getSize() + bullet->getPos().y > targetbodyPos.y))
	{
		return true;
	}
	return false;
}

void ProjectileManager::update(sf::Time deltatime)
{
	for (size_t i = 0; i < enemybulletArray.size(); i++)
	{
		enemybulletArray[i]->update(deltatime);
		if (!enemybulletArray[i]->isAlive() || enemybulletArray[i]->getCollide() == true)
		{
			//enemybulletArray.erase(std::remove(enemybulletArray.begin(), enemybulletArray.end(),
			//	enemybulletArray[i]), enemybulletArray.end());
			break;
		}
	}
	for (std::vector<Projectile *>::const_iterator it = playerbulletArray.begin(); it < playerbulletArray.end(); it++)
	{
		(*it)->update(deltatime);
		if (!(*it)->isAlive() || (*it)->getCollide() == true)
		{
			//playerbulletArray.erase((*it));
		}
	}
	
}

void ProjectileManager::draw(sf::RenderWindow * window)
{
	for (size_t i = 0; i < enemybulletArray.size(); i++)
	{
		enemybulletArray[i]->draw(window);
	}

	for (size_t i = 0; i < playerbulletArray.size(); i++)
	{
		playerbulletArray[i]->draw(window);
	}
}