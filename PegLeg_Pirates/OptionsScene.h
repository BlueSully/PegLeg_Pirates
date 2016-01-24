#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H

#include "stdafx.h"
class OptionsScene
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
	OptionsScene();
	void initOptions(sf::Vector2u windowSize);
	void OptionsUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);
	void OptionsUnload();
	void OptionsDraw(sf::RenderWindow * window);
};

#endif