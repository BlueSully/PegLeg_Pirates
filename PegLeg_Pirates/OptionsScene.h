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
	int highlighted;
	int maxbuttons = 2;
	bool keyPressed = false;
	sf::Sprite m_Menusprite;

public:
	//MAIN
	OptionsScene();
	OptionsScene(sf::Vector2u windowSize);
	~OptionsScene();
	void initOptions(sf::Vector2u windowSize);
	int OptionsUpdate(sf::RenderWindow* window, sf::Event* evt, sf::Time elapsedTime, sf::Vector2u windowSize);
	void OptionsUnload();
	void OptionsDraw(sf::RenderWindow * window);
};

#endif