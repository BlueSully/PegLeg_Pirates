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
<<<<<<< HEAD

=======
	enemybulletArray.reserve(25);
	playerbulletArray.reserve(25);
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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
<<<<<<< HEAD
					playerbulletArray[i]->setDead();
=======
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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
<<<<<<< HEAD
					enemybulletArray[i]->setDead();
=======
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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
<<<<<<< HEAD
	
	for (size_t i = 0; i < enemybulletArray.size(); i++)
	{	
		if (enemybulletArray[i]->isAlive() == false)
		{
			enemybulletArray[i]->setDead();//Projectiles not being used or hit enemy goes out off area to then be deleted
		}
		else
		{
			enemybulletArray[i]->update(deltatime);
		}
	}
	
	for (size_t i = 0; i < playerbulletArray.size(); i++)
	{
		if (playerbulletArray[i]->isAlive() == false)
		{
			playerbulletArray[i]->setDead();
		}
		else
		{
			playerbulletArray[i]->update(deltatime);
		}
	}

	//Deletion of projectiles 
	for (std::vector<Projectile *>::iterator it = playerbulletArray.begin(); it < playerbulletArray.end(); it++)//player bullet array
	{
		if ((*it)->isAlive() == false)
		{
			playerbulletArray.erase(it);
			break;
		}
	}

	for (std::vector<Projectile *>::iterator it = enemybulletArray.begin(); it < enemybulletArray.end(); it++)//enemy bullet array
	{
		if ((*it)->isAlive() == false)
		{
			enemybulletArray.erase(it);
			break;
		}
	}

	std::cout << playerbulletArray.size() << std::endl;
	std::cout << enemybulletArray.size() << std::endl;
=======
	//Deletion of Projectiles
	std::vector<Projectile *>::iterator enemyiter = enemybulletArray.begin();
	while (enemyiter != enemybulletArray.end())
	{
		(*enemyiter)->update(deltatime);
		if (!(*enemyiter)->isAlive() || (*enemyiter)->getCollide() == true)
		{
			enemyiter = enemybulletArray.erase(enemyiter);
		}
		else
		{
			++enemyiter;
		}
	}

	std::vector<Projectile *>::iterator playeriter = playerbulletArray.begin();
	while (playeriter != playerbulletArray.end())
	{
		(*playeriter)->update(deltatime);
		if (!(*playeriter)->isAlive() || (*playeriter)->getCollide() == true)
		{
			playeriter = playerbulletArray.erase(playeriter);
		}
		else
		{
			++playeriter;
		}
	}
>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
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