//This is the class that controls main menu, title and GameOver

#include "MenuScene.h"

MenuScene::MenuScene()
{

}

MenuScene::MenuScene(sf::Vector2u windowSize, int index)
{
	controller = new Controller();
	initMenu(windowSize, index);
}

MenuScene::~MenuScene()
{
	delete controller;
	std::cout << "MenuScene Destroyed" << std::endl;
}

void MenuScene::initMenu(sf::Vector2u windowSize, int index)
{
	srand(time(NULL));
	screenSize = sf::Vector2f(windowSize);
	if (index == Screens::TitleScreen || index == MenuScreen)
	{
		m_mainText.loadFromFile("Sprites/MenuBackGround.png");
		m_Menusprite.setTexture(m_mainText);
		m_Menusprite.setTextureRect(sf::IntRect(0, 0, (int)m_Menusprite.getTextureRect().width, (int)m_Menusprite.getTextureRect().height));
		m_Menusprite.setPosition(0, 0);
		int alpha = 0;
		font.loadFromFile("Sprites/font.ttf");


		TitleItem1.setFont(font);
		TitleItem1.setCharacterSize(30);
		TitleItem1.setString("Press any Button to Play");
		TitleItem1.setPosition(150, 200);

		// Prepare the menu items.
		menuItem1.setFont(font);
		highlighted = 0;
		menuItem1.setColor(sf::Color::Yellow);
		menuItem1.setCharacterSize(30);
		menuItem1.setString("Start Game");
		menuItem1.setPosition(150, 200);

		menuItem2.setFont(font);
		menuItem2.setCharacterSize(30);
		menuItem2.setString("Options");
		menuItem2.setPosition(150, 300);

		menuItem3.setFont(font);
		menuItem3.setCharacterSize(30);
		menuItem3.setString("Quit");
		menuItem3.setPosition(150, 400);
	}
	else if (index == Screens::GameOverScreen)
	{
		m_GameOver.loadFromFile("Sprites/gameOverTest.png");
		m_Flagsprite.setTexture(m_GameOver);
		m_Flagsprite.setPosition((float)(screenSize.x / 2) - m_GameOver.getSize().x / 2, (float)(screenSize.y / 2) - m_GameOver.getSize().y / 2);

		m_Flame.loadFromFile("Sprites/Fire_Animated.png");
		for (int i = 0; i < flamecount; i++)
		{
			m_Flamesprite[i].setTexture(m_Flame);
			m_Flamesprite[i].setTextureRect(sf::IntRect(1, 1, 11, 16));
			m_Flamesprite[i].setScale(sf::Vector2f(10, 10));
		}
		m_Flamesprite[0].setPosition(sf::Vector2f((float)((120)), (float)(40)));
		m_Flamesprite[1].setPosition(sf::Vector2f((float)((220)), (float)(80)));
		m_Flamesprite[2].setPosition(sf::Vector2f((float)((340)), (float)(40)));
		m_Flamesprite[3].setPosition(sf::Vector2f((float)((460)), (float)(60)));
		m_Flamesprite[4].setPosition(sf::Vector2f((float)((560)), (float)(60)));
		m_Flamesprite[5].setPosition(sf::Vector2f((float)((100)), (float)(280)));
		m_Flamesprite[6].setPosition(sf::Vector2f((float)((220)), (float)(255)));
		m_Flamesprite[7].setPosition(sf::Vector2f((float)((320)), (float)(280)));
		m_Flamesprite[8].setPosition(sf::Vector2f((float)((440)), (float)(260)));
		m_Flamesprite[9].setPosition(sf::Vector2f((float)((540)), (float)(180)));

		for (size_t i = 0; i < 2; i++)
		{
			levEndItem4[i].setFont(font);
			levEndItem4[i].setCharacterSize(30);
			levEndItem4[i].setString("Game Over");
			if (i == 0){
				levEndItem4[i].setPosition((float)windowSize.x / 2 - 150, (float)windowSize.y / 2 - 80);
			}
			else if (i == 1){
				levEndItem4[i].setPosition(levEndItem4[0].getPosition().x - 3, levEndItem4[0].getPosition().y - 2);
			}
		}

		elapsedtime = 0;
	}
}

int MenuScene::MenuUpdate(sf::RenderWindow* window, sf::Event* evt, sf::Time elapsedTime, sf::Vector2u windowSize, int index)
{
	if (index == Screens::TitleScreen)
	{
		
		if ((evt->type == sf::Event::TextEntered || evt->type == sf::Event::KeyPressed) && keyPressed == false)
		{
			keyPressed = true;
			std::cout << evt->text.unicode << std::endl;
			return Screens::MenuScreen;
		}	
		else if (evt->type != sf::Event::TextEntered && evt->type != sf::Event::KeyPressed)
		{
			keyPressed = false;
		}
		
		return -1;
	}
	else if (index == MenuScreen)
	{
		//if (controller->HandleInput(evt, sf::Keyboard::Down))
		//{
		//	highlighted++;

		//	if (highlighted > 2)
		//	{
		//		highlighted = 0;
		//	}
		//}
		if ((evt->type == sf::Event::TextEntered || evt->type == sf::Event::KeyPressed) && keyPressed == false)
		{
			keyPressed = true;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				highlighted++;

					if (highlighted > 2)
					{
						highlighted = 0;
					}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				highlighted--;

				if (highlighted < 0)
				{
					highlighted = 2;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			{
				if (menuItem1.getColor() == sf::Color::Yellow)
				{
					std::cout << "Start" << std::endl;
					return Screens::GameScreen;
				}
				else if (menuItem2.getColor() == sf::Color::Yellow)
				{
					std::cout << "Options" << std::endl;
					return Screens::OptionScreen;
				}
				else if (menuItem3.getColor() == sf::Color::Yellow)
				{
					window->close();
				}
			}
			return -1;
		}
		else if (evt->type != sf::Event::TextEntered && evt->type != sf::Event::KeyPressed)
		{
			keyPressed = false;
		}

		if (highlighted == 0)
		{
			menuItem1.setColor(sf::Color::Yellow);
			menuItem2.setColor(sf::Color::White);
			menuItem3.setColor(sf::Color::White);
		}
		else if (highlighted == 1)
		{
			menuItem1.setColor(sf::Color::White);
			menuItem2.setColor(sf::Color::Yellow);
			menuItem3.setColor(sf::Color::White);
		}
		else if (highlighted == 2)
		{
			menuItem1.setColor(sf::Color::White);
			menuItem2.setColor(sf::Color::White);
			menuItem3.setColor(sf::Color::Yellow);
		}

		return -1;
	}
	else if (index == Screens::GameOverScreen)
	{
		elapsedtime += elapsedTime.asSeconds();
		return -1;
	}
	return -1;
}

void MenuScene::MenuUnload(int index)
{

}

void MenuScene::MenuDraw(sf::RenderWindow * window, int index){

	if (index == TitleScreen)
	{
		window->draw(m_Menusprite);
		window->draw(TitleItem1);
	}
	else if(index == MenuScreen)
	{
		window->draw(m_Menusprite);
		window->draw(menuItem1);
		window->draw(menuItem2);
		window->draw(menuItem3);
	}
	else if (index == GameOverScreen)
	{
		if (elapsedtime > 0.1f)
		{
			int row = frameCount % 8;

			for (int i = 0; i < flamecount; i++)
			{
				m_Flamesprite[i].setTextureRect(sf::IntRect((12 * row) + 1, 1, 11, 16));
			}
			
			frameCount++;
			elapsedtime = 0;
			if (frameCount > 3)
			{
				frameCount = 0;
			}
		}
		
		window->draw(m_Flagsprite);
		for (int i = 0; i < flamecount; i++)
		{
			window->draw(m_Flamesprite[i]);
		}
		levEndItem4[1].setColor(sf::Color::Blue);
		window->draw(levEndItem4[1]);
		window->draw(levEndItem4[0]);
	}
}

