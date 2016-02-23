#include "SceneManager.h"

SceneManager::SceneManager()
{
	
}

SceneManager::SceneManager(sf::RenderWindow &window)
{
	m_screenWindow = &window;
	menu = new MenuScene(m_screenWindow->getSize(), Screens::TitleScreen);
	options = new OptionsScene(m_screenWindow->getSize());
}

SceneManager::~SceneManager()
{
	delete menu;
	delete options;
	delete game;
}

int SceneManager::getIndex()
{
	return m_sceneIndex;
}

void SceneManager::setIndex(int value)
{
	m_sceneIndex = value;
	checkindex();//initialises what screen is on
}

void SceneManager::checkindex()
{
	switch (m_sceneIndex)
	{
		case Screens::UpgradeScreen:
			UpgradeScene.initUpgradeScene(m_screenWindow->getSize());
			break;
		case Screens::GameScreen:
			game = new GameScene(m_screenWindow->getSize());
			break;
		case Screens::GameOverScreen:
			menu->initMenu(m_screenWindow->getSize(), Screens::GameOverScreen);
			break;
		default:
			break;
	}
}

void SceneManager::update(sf::Event * evt, sf::Time elapsedTime)
{
	int sceneValue = 0;
	if (getIndex() == Screens::GameScreen)
	{
		sceneValue = game->gameUpdate(elapsedTime, sf::Vector2u(m_screenWindow->getSize()));
	}
	else if (getIndex() == Screens::TitleScreen)
	{
		sceneValue = menu->MenuUpdate(m_screenWindow, evt, elapsedTime, sf::Vector2u(m_screenWindow->getSize()), Screens::TitleScreen);
	}
	else if (getIndex() == Screens::MenuScreen)
	{
		sceneValue = menu->MenuUpdate(m_screenWindow, evt, elapsedTime, sf::Vector2u(m_screenWindow->getSize()), Screens::MenuScreen);
	}
	else if (getIndex() == Screens::OptionScreen)
	{
		sceneValue = options->OptionsUpdate(m_screenWindow, evt, elapsedTime, sf::Vector2u(m_screenWindow->getSize()));
	}
	else if (getIndex() == Screens::GameOverScreen)
	{
		sceneValue = menu->MenuUpdate(m_screenWindow, evt, elapsedTime, sf::Vector2u(m_screenWindow->getSize()), Screens::GameOverScreen);
	}
	else if (getIndex() == Screens::UpgradeScreen)
	{
		sceneValue = UpgradeScene.UpgradeSceneUpdate(elapsedTime, sf::Vector2u(m_screenWindow->getSize()));
	}

	if (sceneValue != -1)
	{
		if (sceneValue > 0)
		{
			std::cout << "Moving Scene To " << sceneValue << std::endl;
			setIndex(sceneValue);
		}
	}
}

void SceneManager::draw()
{
	if (getIndex() == GameScreen)
	{
		game->gameDraw(m_screenWindow);
	}
	else if (getIndex() == TitleScreen)
	{
		menu->MenuDraw(m_screenWindow, TitleScreen);
	}
	else if (getIndex() == MenuScreen)
	{
		menu->MenuDraw(m_screenWindow, MenuScreen);
	}
	else if (getIndex() == UpgradeScreen)
	{
		UpgradeScene.UpgradeSceneDraw(m_screenWindow);
	}
	else if (getIndex() == OptionScreen)
	{
		options->OptionsDraw(m_screenWindow);
	}
	else if (getIndex() == GameOverScreen)
	{
		menu->MenuDraw(m_screenWindow, GameOverScreen);
	}
}






