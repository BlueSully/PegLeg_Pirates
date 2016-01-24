#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "stdafx.h"

class LevelSelect
{
private:
	sf::Texture m_mainText;
	sf::Font font;
	sf::Text menuItem1;
	sf::Text menuItem2;
	sf::Text menuItem3;
	sf::Sprite m_Menusprite;

public:
	//MAIN
	LevelSelect();
	void initLevelSelect(sf::Vector2u windowSize);
	void LevelSelectUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);
	void LevelSelectUnload();
	void LevelSelectDraw(sf::RenderWindow * window);
};
#endif