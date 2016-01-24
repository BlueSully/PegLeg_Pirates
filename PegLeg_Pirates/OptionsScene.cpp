//options 
#include "OptionsScene.h"


OptionsScene::OptionsScene()
{

}
void OptionsScene::initOptions(sf::Vector2u windowSize)
{
	m_mainText.loadFromFile("Sprites/MenuBackGround.png");
	m_Menusprite.setTexture(m_mainText);
	m_mainText.setRepeated(true);
	m_Menusprite.setTextureRect(sf::IntRect(0, 0, (int)windowSize.x, (int)windowSize.y));
	m_Menusprite.setPosition(0, 0);

	int alpha = 0;


	font.loadFromFile("Sprites/font.ttf");


	// Prepare the menu items.
	menuItem1.setFont(font);

	menuItem1.setCharacterSize(30);
	menuItem1.setString("MUTE AUDIO (Press O)");
	menuItem1.setPosition(150, 200);

	menuItem2.setFont(font);
	menuItem2.setCharacterSize(30);
	menuItem2.setString("Return to Previous (P)");
	menuItem2.setPosition(150, 300);

}
void OptionsScene::OptionsUpdate(sf::Time elapsedTime, sf::Vector2u windowSize)
{

}
void OptionsScene::OptionsUnload()
{

}
void OptionsScene::OptionsDraw(sf::RenderWindow * window)
{
	window->draw(m_Menusprite);
	window->draw(menuItem1);
	window->draw(menuItem2);
	std::cout << "options: " << std::endl;


}