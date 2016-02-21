#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

class LevelSelect
{
private:
	sf::Font font;
	sf::Text menuItem1;

	sf::Texture m_mapTex, m_Ship;
	sf::Sprite m_MapSprite, m_Shipsprite;

	std::vector<sf::Vector2f> m_waypoints;
	sf::Vector2f w1;
	sf::Vector2f w2;
	sf::Vector2f w3;
	sf::Vector2f w4;

	std::vector<sf::CircleShape> m_levelpoints;//The Sprites for the points
	sf::Vector2f playerShip;

public:
	//MAIN
	LevelSelect();
	void initLevelSelect(sf::Vector2u windowSize);
	int LevelSelectUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);
	void pointSelect(sf::Vector2f Point);
	void LevelSelectUnload();
	void LevelSelectDraw(sf::RenderWindow * window);
};
#endif