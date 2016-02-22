//options 
#include "LevelSelect.h"


LevelSelect::LevelSelect()
{

}
void LevelSelect::initLevelSelect(sf::Vector2u windowSize)
{
	w1 = sf::Vector2f(425, 100);
	w2 = sf::Vector2f(425, 150);
	w3 = sf::Vector2f(425, 300);
	w4 = sf::Vector2f(525, 150);

	m_Ship.loadFromFile("Sprites/MapShip.png");
	m_Shipsprite.setTexture(m_Ship);
	m_Shipsprite.setScale(0.7f, 0.7f);

	m_mapTex.loadFromFile("Sprites/worldMap.png");
	m_MapSprite.setTexture(m_mapTex);
	m_mapTex.setRepeated(true);
	m_MapSprite.setTextureRect(sf::IntRect(0, 0, (int)windowSize.x, (int)windowSize.y));
	m_MapSprite.setPosition(0, 0);

	int alpha = 0;
	font.loadFromFile("Sprites/font.ttf");

	// Prepare the menu items.
	menuItem1.setFont(font);
	menuItem1.setCharacterSize(30);
	menuItem1.setString("Move to Level");
	menuItem1.setPosition(350, 15);
	menuItem1.setColor(sf::Color(255, 255, 0));

	m_waypoints.push_back(w1);
	m_waypoints.push_back(w2);
	m_waypoints.push_back(w3);
	m_waypoints.push_back(w4);

	playerShip = (m_waypoints[0]);

	for (size_t i = 0; i < m_waypoints.size(); i++)
	{
		sf::CircleShape point = sf::CircleShape(10);
		point.setPosition(m_waypoints[i]);
		m_levelpoints.push_back(point);
	}

	m_levelpoints[0].setFillColor(sf::Color::Red);
}

int LevelSelect::LevelSelectUpdate(sf::Time elapsedTime, sf::Vector2u windowSize)
{
	m_Shipsprite.setPosition(playerShip.x - 20, playerShip.y - 30);

	bool enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);

	//How the movement will work, don't know how to use your controller class
	// Just for the testing
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)))
	{
		playerShip = (m_waypoints[0]);
		pointSelect(m_waypoints[0]);
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)))
	{
		playerShip = (m_waypoints[1]);
		pointSelect(m_waypoints[1]);
	}
	else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)))
	{
		playerShip = (m_waypoints[2]);
		pointSelect(m_waypoints[2]);
	}
	else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)))
	{
		playerShip = (m_waypoints[3]);
		pointSelect(m_waypoints[3]);
	}

	if (playerShip == m_waypoints[0] && enter)
	{
		//goto Level 1 cos we ain't got no levels yo!
		return 4;
	}
	if (playerShip == m_waypoints[1] && enter)
	{
		//goto Level 2
		return 4;
	}
	if (playerShip == m_waypoints[2] && enter)
	{
		//goto Level 3
		return 4;
	}
	if (playerShip == m_waypoints[3] && enter)
	{
		//goto Level 4
		return 4;
	}
	return -1;
}

void LevelSelect::LevelSelectUnload()
{

}

void LevelSelect::pointSelect(sf::Vector2f waypoint)
{
	for (size_t i = 0; i < m_levelpoints.size(); i++)
	{
		if (m_levelpoints[i].getPosition() == waypoint)
		{
			m_levelpoints[i].setFillColor(sf::Color::Red);
		}
		else 
		{
			m_levelpoints[i].setFillColor(sf::Color::White);
		}
	}
}

void LevelSelect::LevelSelectDraw(sf::RenderWindow * window)
{
	window->draw(m_MapSprite);

	window->draw(menuItem1);

	for (size_t i = 0; i < m_levelpoints.size(); i++)
	{
		window->draw(m_levelpoints[i]);
	}

	window->draw(m_Shipsprite);
}