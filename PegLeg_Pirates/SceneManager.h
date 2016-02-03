#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "stdafx.h"

#include "GameScene.h"
#include "MenuScene.h"
#include "OptionsScene.h"
#include "LevelSelect.h"

class SceneManager
{
private:
	int m_sceneIndex;//Holds what screen is 
	sf::RenderWindow * m_screenWindow;
	sf::Texture m_mainText;
	sf::Font font;
	sf::Text menuItem1;
	sf::Text menuItem2;
	sf::Text menuItem3;
	
	sf::Sprite m_Menusprite;

	GameScene* game;
	MenuScene* menu;
	OptionsScene* options;
	LevelSelect levelSelect;
	
public:
	SceneManager();
	SceneManager(sf::RenderWindow &window);
	~SceneManager();
	int getIndex();
	void setIndex(int value);

	void checkindex();
	void update(sf::Event * evt, sf::Time elapsedTime);
	void draw();
};

#endif