#include "EnemyGun.h"

EnemyGun::EnemyGun()
{
	//empty constructor
}

EnemyGun::~EnemyGun()
{

}

bool EnemyGun::getAttack()
{
	return m_isAttacking;
}

bool EnemyGun::isActivated()
{
	return m_activated;
}

void EnemyGun::setActive(bool value)
{
	m_activated = value;
}

void EnemyGun::setPos(sf::Vector2f value)
{
	m_pos = value;
	Entity::setPos(value);
}

void EnemyGun::initialise(sf::Vector2f value, sf::Texture &  bodySprite, sf::Texture & shadowSprite, sf::Texture & weaponSprite, int index)
{
	m_pos = value;
	orgColour = sf::Color(0, 255, 255, 125);

	m_bodyWidth = (int)bodySprite.getSize().x;
	m_bodyHeight = (int)bodySprite.getSize().y;
	m_body = sf::Sprite(bodySprite, sf::IntRect(0, 0, (int)bodySprite.getSize().x, (int)bodySprite.getSize().y));
	m_body.setPosition(m_pos);
	m_body.setColor(orgColour);
	m_NumbodySprites = 24;

	m_offsetpixelsX = 3;
	m_shadow = sf::Sprite(shadowSprite, sf::IntRect(0, 0, shadowSprite.getSize().x, shadowSprite.getSize().y));
	m_shadow.setPosition(sf::Vector2f(m_body.getPosition().x + m_offsetpixelsX, (m_body.getPosition().y + m_body.getTexture()->getSize().y) - m_shadow.getTexture()->getSize().y / 2));

	m_shadowWidth = (int)shadowSprite.getSize().x;
	m_shadowHeight = (int)shadowSprite.getSize().y;

	m_weapon = sf::Sprite(weaponSprite, sf::IntRect(0, 0, (int)weaponSprite.getSize().x, (int)weaponSprite.getSize().y));
	m_weapon.setPosition(sf::Vector2f(m_body.getPosition().x + m_bodyWidth - 25, m_body.getPosition().y + m_bodyHeight / 2));
	m_weaponSize = sf::Vector2f((float)weaponSprite.getSize().x, (float)weaponSprite.getSize().y);

	setSize(sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight));

	m_isAttacking = false;
	setIsHit(false);
	setAlive(true);
	m_speed = (float)(rand() % 50 + 30);

	setHitCoolDown(0);
	timeToAttack = (float)(rand() % 5 + 3);
	m_health = 100;
	setMaxHealth(100);
}

void EnemyGun::update(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize, ProjectileManager *manager)
{
	if (isHit() && getHitCoolDown() > 0)
	{
		setHitCoolDown(getHitCoolDown() - deltaTime.asSeconds());
		m_body.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	}
	else if (!isHit() && getHitCoolDown() < 0)
	{
		setHitCoolDown(0.4f);
		setIsHit(false);
	}

	if (m_health <= 0)
		setAlive(false);

	if (m_body.getPosition().x < targetbodyPos.x)//getting direction of enemy to attack
		m_attackSideRight = true;
	else if (m_body.getPosition().x > targetbodyPos.x)
		m_attackSideRight = false;

	if (checkCanAttack(deltaTime, targetbasePos, targetbaseSize))
		attackRangedController(deltaTime, manager);	
	else
		m_isAttacking = false;

	moveToward(deltaTime, targetbodyPos, targetbodysize, targetbasePos, targetbaseSize);

	std::pair<sf::IntRect, bool> animation;
	animation = animationM.Update(m_NumbodySprites, 3, 3, 0, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);

	m_body.setTextureRect(animation.first);//still left

	setPos(m_pos);
	m_shadow.setPosition(sf::Vector2f(m_body.getPosition().x + m_offsetpixelsX, (m_body.getPosition().y + m_body.getTexture()->getSize().y) - m_shadow.getTexture()->getSize().y / 2));
}

void EnemyGun::moveToward(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize)
{
	if ((int)targetbodyPos.x > (int)getPos().x + getSize().x - 250)
		m_pos.x += m_speed * deltaTime.asSeconds();//heading right
	else if ((int)targetbodyPos.x + targetbodysize.x < (int)getPos().x - 250)
		m_pos.x -= m_speed * deltaTime.asSeconds();//heading left

	if ((int)targetbasePos.y >(int)m_shadow.getPosition().y)//moving down
		m_pos.y += m_speed * deltaTime.asSeconds();
	else if ((int)targetbasePos.y < (int)m_shadow.getPosition().y + m_shadowHeight)
		m_pos.y -= m_speed * deltaTime.asSeconds();
}

void EnemyGun::attackRangedController(sf::Time deltaTime, ProjectileManager *manager)
{
	if (m_firedGun == false)
	{
		m_firedGun = true;

		float projectileVec;
		if (m_attackSideRight)
			projectileVec = 500;
		else
			projectileVec = -500;

		manager->createProjectile(sf::Vector2f(getPos().x + getSize().x / 2, getPos().y + getSize().y / 2), projectileVec, EntityType::EnemyEntity);
		timeToAttack = (float)(rand() % 5 + 3);
	}
}

bool EnemyGun::checkCanAttack(sf::Time deltaTime, sf::Vector2f targetBasePos, sf::Vector2f targetBaseSize)
{
	if (timeToAttack > 0)
	{
		timeToAttack -= deltaTime.asSeconds();//updating cooldown
	}
	else if (timeToAttack <= 0)//can enemy attack
	{
		if (onSamePlaneY(targetBasePos, targetBaseSize))
		{
			m_firedGun = false;
			return true;		
		}
	}
	
	return false;
}

void EnemyGun::changeColour()
{
	m_body.setColor(orgColour);
}

void EnemyGun::draw(sf::RenderWindow * window)
{
	
	//Drawing 
	window->draw(m_shadow);
	window->draw(m_body);

	sf::RectangleShape shp;
	shp.setPosition(sf::Vector2f(m_body.getPosition().x, m_body.getPosition().y - 20));
	shp.setSize(sf::Vector2f((float)getHealth() / 2, (float)20));
	window->draw(shp);
}