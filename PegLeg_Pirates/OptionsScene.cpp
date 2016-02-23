//options 
#include "OptionsScene.h"


OptionsScene::OptionsScene()
{

}

OptionsScene::OptionsScene(sf::Vector2u windowSize)
{
	initOptions(windowSize);
}

OptionsScene::~OptionsScene()
{
	std::cout << "OptionScene Destroyed" << std::endl;
}

void OptionsScene::initOptions(sf::Vector2u windowSize)
{
	m_mainText.loadFromFile("Sprites/MenuBackGround.png");
	m_Menusprite.setTexture(m_mainText);
	m_Menusprite.setTextureRect(sf::IntRect(0, 0, (int)m_Menusprite.getTextureRect().width, (int)m_Menusprite.getTextureRect().height));
	m_Menusprite.setPosition(0, 0);

	int alpha = 0;

	font.loadFromFile("Sprites/font.ttf");

	// Prepare the menu items.
	highlighted = 1;
	menuItem1.setFont(font);
	menuItem1.setCharacterSize(30);
	menuItem1.setString("Mute Audio");
	menuItem1.setPosition(150, 200);

	menuItem2.setFont(font);
	menuItem2.setCharacterSize(30);
	menuItem2.setString("Back");
	menuItem2.setPosition(150, 300);
}
int OptionsScene::OptionsUpdate(sf::RenderWindow* window, sf::Event* evt, sf::Time elapsedTime, sf::Vector2u windowSize)
{
	if ((evt->type == sf::Event::TextEntered || evt->type == sf::Event::KeyPressed) && keyPressed == false)
	{
		keyPressed = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			highlighted++;

			if (highlighted > maxbuttons)
			{
				highlighted = 1;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			highlighted--;

			if (highlighted < 1)
			{
				highlighted = maxbuttons;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if (menuItem1.getColor() == sf::Color::Yellow)
			{
				std::cout << "MUTE AUDIO" << std::endl;
			}
			else if (menuItem2.getColor() == sf::Color::Yellow)
			{
				std::cout << "Back" << std::endl;
				return Screens::MenuScreen;
			}
		}
		
	}
	else if (evt->type != sf::Event::TextEntered && evt->type != sf::Event::KeyPressed)
	{
		keyPressed = false;
	}

	if (highlighted == 1)
	{
		menuItem1.setColor(sf::Color::Yellow);
		menuItem1.setString("MUTE AUDIO ( press X )");
		menuItem2.setColor(sf::Color::White);
		menuItem2.setString("Back");
	}
	else if (highlighted == 2)
	{
		menuItem1.setColor(sf::Color::White);
		menuItem1.setString("MUTE AUDIO");
		menuItem2.setColor(sf::Color::Yellow);
		menuItem2.setString("Back ( press X )");
	}

	return -1;
}

void OptionsScene::OptionsUnload()
{

}
void OptionsScene::OptionsDraw(sf::RenderWindow * window)
{
	window->draw(m_Menusprite);
	window->draw(menuItem1);
	window->draw(menuItem2);
}