//options 
#include "LevelSelect.h"


LevelSelect::LevelSelect()
{

}
void LevelSelect::initLevelSelect(sf::Vector2u windowSize)
{
	m_mainText.loadFromFile("Sprites/worldMap.png");
	m_Menusprite.setTexture(m_mainText);
	m_mainText.setRepeated(true);
	m_Menusprite.setTextureRect(sf::IntRect(0, 0, (int)windowSize.x, (int)windowSize.y));
	m_Menusprite.setPosition(0, 0);

	int alpha = 0;


	font.loadFromFile("Sprites/font.ttf");


	// Prepare the menu items.
	menuItem1.setFont(font);

	menuItem1.setCharacterSize(30);
	menuItem1.setString("I AM THE LEVEL SELECT");
	menuItem1.setPosition(150, 200);
	menuItem1.setColor(Color(255, 255, 0));

	menuItem2.setFont(font);
	menuItem2.setCharacterSize(30);
	menuItem2.setString("LOVE ME");
	menuItem2.setPosition(150, 300);
	menuItem2.setColor(Color(255, 255, 0));

}
void LevelSelect::LevelSelectUpdate(sf::Time elapsedTime, sf::Vector2u windowSize)
{

}
void LevelSelect::LevelSelectUnload()
{

}
void LevelSelect::LevelSelectDraw(sf::RenderWindow * window)
{
	window->draw(m_Menusprite);
	window->draw(menuItem1);
	window->draw(menuItem2);
	std::cout << "level: " << std::endl;
}