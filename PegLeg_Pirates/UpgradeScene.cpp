//options 
#include "UpgradeScene.h"


UpgradeScene::UpgradeScene()
{
	health = 0;
	damage = 0;
	bank = 0;
}

int UpgradeScene::getHealth()
{
	return health;
}
void UpgradeScene::setHealth(int value)
{
	health = value;
}

int UpgradeScene::getDamage()
{
	return damage;
}
void UpgradeScene::setDamage(int value)
{
	damage = value;
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

	upgradeItem4.setFont(font);
	upgradeItem4.setCharacterSize(30);
	upgradeItem4.setString("Bank : " + bank);
	upgradeItem4.setPosition(100, 510);
	upgradeItem4.setColor(sf::Color(255, 255, 0));
}

int UpgradeScene::UpgradeSceneUpdate(sf::Time elapsedTime, sf::Vector2u windowSize)
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::G)) && !buyDamage && bank > 30)
	{
		setDamage(getDamage() + 10);
		bank -= 30;
		buyDamage = true;
	}
	else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::G)))
	{
		buyDamage = false;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::H)) && !buyHealth && bank > 20)
	{
		setHealth(getHealth() + 20);
		bank -= 20;
		buyHealth = true;
	}
	else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::H)))
	{
		buyHealth = false;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !keypressed)
	{
		keypressed = true;
		return Screens::GameScreen;
	}
	else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)))
	{
		keypressed = false;
	}
	upgradeItem4.setString("Bank : " + std::to_string(bank));
	return -1;
}

void UpgradeScene::UpgradeSceneUnload()
{

}

void UpgradeScene::UpgradeSceneDraw(sf::RenderWindow * window)
{
	sf::View camera = sf::View(sf::Vector2f((float)window->getSize().x / 2, (float)window->getSize().y / 2), sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	window->setView(camera);
	window->draw(m_MapSprite);

	window->draw(upgradeItem1);
	window->draw(upgradeItem2);
	window->draw(upgradeItem3);
	window->draw(upgradeItem4);

}

void UpgradeScene::setCoins(int coins)
{
	bank = coins;
}