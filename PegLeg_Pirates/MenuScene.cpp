//This is the class that controls main menu, title and GameOver

#include "MenuScene.h"

MenuScene::MenuScene()
{
	
}

void MenuScene::initMenu(sf::Vector2u windowSize, int index)
{
	srand(time(NULL));
	screenSize = sf::Vector2f(windowSize);
	if (index == Screens::TitleScreen || index == MenuScreen)
	{
		m_mainText.loadFromFile("Sprites/MenuBackGround.png");
		m_Menusprite.setTexture(m_mainText);
		m_mainText.setRepeated(true);
		m_Menusprite.setTextureRect(sf::IntRect(0, 0, (int)screenSize.x, (int)screenSize.y));
		m_Menusprite.setPosition(0, 0);
		int alpha = 0;
		font.loadFromFile("Sprites/font.ttf");

		// Prepare the menu items.
		menuItem1.setFont(font);

		menuItem1.setCharacterSize(30);
		menuItem1.setString("Start Game (Press O)");
		menuItem1.setPosition(150, 200);

		menuItem2.setFont(font);
		menuItem2.setCharacterSize(30);
		menuItem2.setString("Options (I)");
		menuItem2.setPosition(150, 300);

		menuItem3.setFont(font);
		menuItem3.setCharacterSize(30);
		menuItem3.setString("Quit  (Press P)");
		menuItem3.setPosition(150, 400);
	}
	if (index == Screens::GameOverScreen)
	{
		m_GameOver.loadFromFile("Sprites/gameOverTest.png");
		m_Flagsprite.setTexture(m_GameOver);
		m_Flagsprite.setPosition((float)(screenSize.x / 2) - m_GameOver.getSize().x / 2, (float)(screenSize.y / 2) - m_GameOver.getSize().y / 2);

		m_Flame.loadFromFile("Sprites/Fire_Animated.png");
		for (int i = 0; i < flamecount; i++)
		{
			m_Flamesprite[i].setTexture(m_Flame);
			m_Flamesprite[i].setTextureRect(sf::IntRect(1, 1, 11, 16));
			m_Flamesprite[i].setPosition(sf::Vector2f((float)(-100), (float)(-100)));
			m_Flamesprite[i].setScale(sf::Vector2f(10, 10));
		}
		m_Flamesprite[0].setPosition(sf::Vector2f((float)((103)), (float)(100)));
		m_Flamesprite[1].setPosition(sf::Vector2f((float)((223)), (float)(70)));
		m_Flamesprite[2].setPosition(sf::Vector2f((float)((333)), (float)(40)));
		m_Flamesprite[3].setPosition(sf::Vector2f((float)((443)), (float)(60)));
		m_Flamesprite[4].setPosition(sf::Vector2f((float)((553)), (float)(60)));
		m_Flamesprite[5].setPosition(sf::Vector2f((float)((103)), (float)(280)));
		m_Flamesprite[6].setPosition(sf::Vector2f((float)((223)), (float)(300)));
		m_Flamesprite[7].setPosition(sf::Vector2f((float)((343)), (float)(300)));
		m_Flamesprite[8].setPosition(sf::Vector2f((float)((433)), (float)(270)));
		m_Flamesprite[9].setPosition(sf::Vector2f((float)((533)), (float)(250)));

		for (size_t i = 0; i < 2; i++)
		{
			menuItem4[i].setFont(font);
			menuItem4[i].setCharacterSize(30);
			menuItem4[i].setString("Game Over,You dead Bitch");
			if (i == 0){
				menuItem4[i].setPosition(150, 250);
			}
			else if (i == 1){
				menuItem4[i].setPosition(menuItem4[0].getPosition().x - 3, menuItem4[0].getPosition().y - 2);
			}
		}

		elapsedtime = 0;
	}
}
void MenuScene::MenuUpdate(sf::Time elapsedTime, sf::Vector2u windowSize)
{
	elapsedtime += elapsedTime.asSeconds();
}

void MenuScene::MenuUnload(int index)
{
	if (index == Screens::TitleScreen)
	{
	}	
	if (index == Screens::GameOverScreen)
	{
	}
}

void MenuScene::MenuDraw(sf::RenderWindow * window, int index){

	if (index == TitleScreen || index == MenuScreen)
	{
		window->draw(m_Menusprite);
		window->draw(menuItem1);
		std::cout << "TitleMenu: "  << std::endl;


	}
	else if(index == MenuScreen)
	{
		window->draw(m_Menusprite);
		window->draw(menuItem1);
		window->draw(menuItem2);
		window->draw(menuItem3);
		std::cout << "mainMenu: " << std::endl;
	}
	else if (index == GameOverScreen)
	{
		if (elapsedtime > 0.1f)
		{
			int row = frameCount % 8;

			for (size_t i = 0; i < flamecount; i++)
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
		menuItem4[1].setColor(sf::Color::Blue);
		window->draw(menuItem4[1]);
		window->draw(menuItem4[0]);
		
		std::cout << "GameOverScreen: " << std::endl;
	}
}

