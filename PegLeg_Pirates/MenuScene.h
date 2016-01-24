#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "stdafx.h"

enum Menus
{
	Title,Main,GameOver
};

class MenuScene
{
private:
	sf::Vector2f screenSize;
	sf::Texture m_mainText;
	sf::Texture m_GameOver;
	sf::Texture m_Flame;
	sf::Font font;
	sf::Text menuItem1;
	sf::Text menuItem2;
	sf::Text menuItem3;
	sf::Text menuItem4 [2];

	int flamecount = 10;
	int frameCount = 0;
	float elapsedtime;
	sf::Sprite m_Menusprite;
	sf::Sprite m_Flagsprite;
	sf::Sprite m_Flamesprite[10];
	
public:
	MenuScene();
	void initMenu(sf::Vector2u windowSize, int index = 0);
	void MenuUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);
	void MenuUnload(int index);
	void MenuDraw(sf::RenderWindow * window, int);
};
#endif