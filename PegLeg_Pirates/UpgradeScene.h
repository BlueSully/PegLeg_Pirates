#ifndef UPGRADESCENE_H
#define UPGRADESCENE_H

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "Player.h"

class UpgradeScene
{
private:
	sf::Font font;
	sf::Text upgradeItem1;
	sf::Text upgradeItem2;
	sf::Text upgradeItem3;
	sf::Text upgradeItem4;

	Player player;

	sf::Texture m_mapTex;
	sf::Sprite m_MapSprite;

	int money;


public:
	//MAIN
	UpgradeScene();
	void initUpgradeScene(sf::Vector2u windowSize);
	int UpgradeSceneUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);
	void UpgradeSceneUnload();
	void UpgradeSceneDraw(sf::RenderWindow * window);
	void getCoins(int);
};
#endif