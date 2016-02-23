//options 
#include "UpgradeScene.h"


UpgradeScene::UpgradeScene()
{

}
void UpgradeScene::initUpgradeScene(sf::Vector2u windowSize)
{



	m_mapTex.loadFromFile("Sprites/worldMap.png");
	m_MapSprite.setTexture(m_mapTex);
	m_mapTex.setRepeated(true);
	m_MapSprite.setTextureRect(sf::IntRect(0, 0, (int)windowSize.x, (int)windowSize.y));
	m_MapSprite.setPosition(0, 0);

	int alpha = 0;
	font.loadFromFile("Sprites/font.ttf");

	// Prepare the menu items.
	upgradeItem1.setFont(font);
	upgradeItem1.setCharacterSize(30);
	upgradeItem1.setString("UPGRADE HEALTH & DAMAGE");
	upgradeItem1.setPosition(150, 15);
	upgradeItem1.setColor(sf::Color(255, 255, 0));

	upgradeItem2.setFont(font);
	upgradeItem2.setCharacterSize(30);
	upgradeItem2.setString("Press G to Upgrade");
	upgradeItem2.setPosition(200, 150);
	upgradeItem2.setColor(sf::Color(255, 255, 0));

	upgradeItem3.setFont(font);
	upgradeItem3.setCharacterSize(30);
	upgradeItem3.setString("Press H to Upgrade");
	upgradeItem3.setPosition(200, 350);
	upgradeItem3.setColor(sf::Color(255, 255, 0));


	upgradeItem3.setFont(font);
	upgradeItem3.setCharacterSize(30);
	upgradeItem3.setString("Press H to Upgrade");
	upgradeItem3.setPosition(200, 350);
	upgradeItem3.setColor(sf::Color(255, 255, 0));
}

int UpgradeScene::UpgradeSceneUpdate(sf::Time elapsedTime, sf::Vector2u windowSize)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::G)) && money < 30)
	{
		player.setHitDamage(player.getHitDamage() + 30);
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::H)) && money < 20)
	{
		player.setMaxHealth(player.getHealth() + 30);
	}

	return -1;
}

void UpgradeScene::UpgradeSceneUnload()
{

}


void UpgradeScene::UpgradeSceneDraw(sf::RenderWindow * window)
{
	window->draw(m_MapSprite);

	window->draw(upgradeItem1);
	window->draw(upgradeItem2);
	window->draw(upgradeItem3);

}

void UpgradeScene::getCoins(int coins)
{
	money = coins;
}