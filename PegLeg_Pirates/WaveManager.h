#pragma once
#include "EnemySword.h"
#include "stdafx.h"

class WaveManager
{
private:
	std::vector<Entity *> wave1;
	std::vector<Entity *> wave2;
	std::vector<Entity *> wave3;
	int wave1Size;
	int wave2Size;
	int wave3Size;
	int curStage;
	sf::IntRect spawnTrigger;
	sf::Vector2u window;

public:
	WaveManager();
	WaveManager(sf::IntRect spawnRect);
	~WaveManager();

	//GET METHODS
	std::vector<Entity *> getWave1();
	std::vector<Entity *> getWave2();
	std::vector<Entity *> getWave3();
	int getCurStage();
	sf::IntRect getSpawner();

	//SET Methods
	void setSpawnPos(int x, int y);
	void setCurStage(int value);

	//Methods
	void initEnemiesPosition(sf::Vector2u windowSize);
	void update();
	void updateTrigger(int value);
	void addToWave(Entity * enemy, int indexWave);
	void moveSpawnTrigger(int x);
	
};