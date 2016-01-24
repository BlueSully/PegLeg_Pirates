#include "SceneManager.h"



SceneManager::SceneManager()
{
	

}

SceneManager::SceneManager(sf::RenderWindow &window)
{
	m_screenWindow = &window;

	game = GameScene();
	menu = MenuScene();
	options = OptionsScene();
	menu.initMenu(m_screenWindow->getSize());
	options.initOptions(m_screenWindow->getSize());
	levelSelect.initLevelSelect(m_screenWindow->getSize());
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
		case Screens::GameScreen:
			game.initGame(m_screenWindow->getSize());
			break;
		case Screens::GameOverScreen:
			menu.initMenu(m_screenWindow->getSize(), Screens::GameOverScreen);
			break;
		default:
			break;
	}
}



void SceneManager::update(sf::Time elapsedTime)
{
	if (getIndex() == GameScreen)
	{
		game.gameUpdate(elapsedTime, sf::Vector2u(m_screenWindow->getSize()));
	}
	else if (getIndex() == GameOverScreen)
	{
		menu.MenuUpdate(elapsedTime, sf::Vector2u(m_screenWindow->getSize()));
	}
}

void SceneManager::draw()
{
	if (getIndex() == GameScreen)
	{
		game.gameDraw(m_screenWindow);
	}
	else if (getIndex() == TitleScreen)
	{
		menu.MenuDraw(m_screenWindow, TitleScreen);
	}
	else if (getIndex() == MenuScreen)
	{
		menu.MenuDraw(m_screenWindow, MenuScreen);
	}
	else if (getIndex() == LevelSel)
	{
		levelSelect.LevelSelectDraw(m_screenWindow);
	}
	else if (getIndex() == OptionScreen)
	{
		options.OptionsDraw(m_screenWindow);
	}
	else if (getIndex() == GameOverScreen)
	{
		menu.MenuDraw(m_screenWindow, GameOverScreen);
	}
}






