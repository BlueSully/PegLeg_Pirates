#include "waveManager.h"

WaveManager::WaveManager()
{
	wave1Size = rand() % 4 + 4;
	wave2Size = rand() % 4 + 8;
	wave3Size = 18;
	curStage = Wave::wave1;
}

WaveManager::WaveManager(sf::IntRect spawnRect)
{
	wave1Size = 6;
	wave2Size = 8;
	wave3Size = 16;
	spawnTrigger = spawnRect;
	curStage = Wave::wave1;
}

WaveManager::~WaveManager()
{
	std::cout << "WaveManager Destroyed" << std::endl;

	//Enemies are deleted elsewhere just clear lists
	wave1.clear();
	wave2.clear();
	wave3.clear();
}

std::vector<Entity *> WaveManager::getWave1()
{
	return wave1;
}

std::vector<Entity *> WaveManager::getWave2()
{
	return wave2;
}

std::vector<Entity *> WaveManager::getWave3()
{
	return wave3;
}

sf::IntRect WaveManager::getSpawner()
{
	return spawnTrigger;
}

int WaveManager::getCurStage()
{
	return curStage;
}

void WaveManager::initEnemiesPosition(sf::Vector2u windowSize)
{
	for (size_t i = 0; i < wave1.size(); i++)
	{
		int row = i / 4;
		int col = i % 4;
		wave1[i]->setPos(sf::Vector2f((float)windowSize.x + (100 * row) + 10, (float)(windowSize.y / 2) + 70 * col));
	}
	for (size_t i = 0; i < wave2.size(); i++)
	{
		int row = i / 4;
		int col = i % 4;
		wave2[i]->setPos(sf::Vector2f((float)((windowSize.x + windowSize.x / 2) + (100 * row) + 10), (float)(windowSize.y / 2) + 70 * col));
	}
	for (size_t i = 0; i < wave3.size(); i++)
	{
		int row = i / 4;
		int col = i % 4;
		wave3[i]->setPos(sf::Vector2f((float)(windowSize.x * 2) + (100 * row) + 10, (float)(windowSize.y / 2) + 70 * col));
	}
}

void WaveManager::update()
{
	for (size_t i = 0; i < wave1.size(); i++)
	{
		if (!wave1[i]->isAlive())
		{
			wave1.erase(std::remove(wave1.begin(), wave1.end(), wave1[i]), wave1.end());
		}
	}
	for (size_t i = 0; i < wave2.size(); i++)
	{
		if (!wave2[i]->isAlive())
		{
			wave2.erase(std::remove(wave2.begin(), wave2.end(), wave2[i]), wave2.end());
		}
	}
	for (size_t i = 0; i < wave3.size(); i++)
	{
		if (!wave3[i]->isAlive())
		{
			wave3.erase(std::remove(wave3.begin(), wave3.end(), wave3[i]), wave3.end());
		}
	}
}

void WaveManager::updateTrigger(int value)
{
	if (value == 0)
	{
		if (wave1.size() > 0 && curStage == Wave::wave1)
		{
			moveSpawnTrigger(spawnTrigger.left + spawnTrigger.width);
		}
		else if (wave2.size() > 0 && curStage == Wave::wave2)
		{
			moveSpawnTrigger(spawnTrigger.left + spawnTrigger.width);
		}
		else if (wave3.size() > 0 && curStage == Wave::wave3)
		{
			moveSpawnTrigger(spawnTrigger.left + spawnTrigger.width);
		}
	}
}

void WaveManager::addToWave(Entity * enemy, int indexWave)
{
	if (indexWave == 1 && wave1.size() != wave1Size)
	{
		wave1.push_back(enemy);
	}
	else if (indexWave == 2 && wave2.size() != wave2Size)
	{
		wave2.push_back(enemy);
	}
	else
	{
		if (wave3.size() != wave3Size)
		{
			wave3.push_back(enemy);
		}
	}
}

void WaveManager::setSpawnPos(int x, int y)
{
	spawnTrigger.left = x;
	spawnTrigger.top = y;
}

void  WaveManager::setCurStage(int value)
{
	if (value <= Wave::wave3)
	{
		curStage = value;
	}
}

void WaveManager::moveSpawnTrigger(int x)
{
	spawnTrigger.left = x;
}