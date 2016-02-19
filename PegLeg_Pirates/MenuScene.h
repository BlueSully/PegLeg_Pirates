#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "stdafx.h"

class MenuScene
{
private:
	sf::Vector2f screenSize;
	sf::Texture m_mainText;
	sf::Texture m_GameOver;
	sf::Texture m_Flame;
	sf::Font font;
	sf::Text TitleItem1;
	sf::Text menuItem1, menuItem2, menuItem3;
	sf::Text levEndItem4 [2];
	bool keyPressed = false;
	int flamecount = 10;
	int frameCount = 0;
	float elapsedtime;
	int highlighted;
	sf::Sprite m_Menusprite;
	sf::Sprite m_Flagsprite;
	sf::Sprite m_Flamesprite[10];

public:
	MenuScene();
	MenuScene(sf::Vector2u windowSize, int index = 0);
	~MenuScene();
	void initMenu(sf::Vector2u windowSize, int index = 0);
	int MenuUpdate(sf::RenderWindow* window, sf::Event* evt, sf::Time elapsedTime, sf::Vector2u windowSize, int index);
	void MenuUnload(int index);
	void MenuDraw(sf::RenderWindow * window, int);
};
#endif