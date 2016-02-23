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

	m_bodyWidth = 63;
	m_bodyHeight = 48;
	m_body = sf::Sprite(bodySprite, sf::IntRect(0, 0, (int)m_bodyWidth, (int)m_bodyHeight));
	m_body.setPosition(m_pos);
	m_NumbodySprites = 24;

	m_offsetpixelsX = 3;
	m_shadow = sf::Sprite(shadowSprite, sf::IntRect(0, 0, shadowSprite.getSize().x, shadowSprite.getSize().y));
	m_shadow.setPosition(sf::Vector2f(m_body.getPosition().x + m_offsetpixelsX, (m_body.getPosition().y + m_bodyHeight) - m_shadow.getTexture()->getSize().y / 2));

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

void EnemyGun::update(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize, ProjectileManager *manager, sf::IntRect viewport)
{
	if (getHitCoolDown() > 0)
	{
		setCanBeHit(false);
		setHitCoolDown(getHitCoolDown() - deltaTime.asSeconds());
	}
	else
	{
		setCanBeHit(true);
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

	moveToward(deltaTime, targetbodyPos, targetbodysize, targetbasePos, targetbaseSize, viewport);

	std::pair<sf::IntRect, bool> animation;
	if (m_attackAnimation)
	{
		if (m_attackSideRight)
			animation = animationM.Update(framecount, 4, 4, 6, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		else if(!m_attackSideRight)
			animation = animationM.Update(framecount, 4, 4, 2, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		if (animation.second == true)
		{
			framecount = 0;
			m_attackAnimation = false;
		}
	}
	else 
	{
		if (m_attackSideRight)
			animation = animationM.Update(framecount, 2, 2, 5, 0.3f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		else if (!m_attackSideRight)
			animation = animationM.Update(framecount, 2, 2, 1, 0.3f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
	}

	m_body.setTextureRect(animation.first);//still left

	setPos(m_pos);
	m_shadow.setPosition(sf::Vector2f(m_body.getPosition().x + m_offsetpixelsX, (m_body.getPosition().y + m_bodyHeight) - m_shadow.getTexture()->getSize().y / 2));
}

void EnemyGun::moveToward(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize, sf::IntRect viewport)
{
	if ((int)targetbodyPos.x + targetbodysize.x < (int)getPos().x - 250 && getPos().x > viewport.left)
		m_pos.x -= m_speed * deltaTime.asSeconds();//heading left
	else if ((int)targetbodyPos.x > (int)getPos().x + getSize().x - 250 && getPos().x + getSize().x < viewport.left + viewport.width)
		m_pos.x += m_speed * deltaTime.asSeconds();//heading right
	
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
		m_attackAnimation = true;
		float projectileVec;
		if (m_attackSideRight)
			projectileVec = 500;
		else
			projectileVec = -500;

		if (m_attackSideRight)
		{
			manager->createProjectile(sf::Vector2f(getPos().x + getSize().x / 2 + 20, getPos().y + getSize().y / 2 - 11.f), projectileVec, EntityType::EnemyEntity);
		}
		else
		{
			manager->createProjectile(sf::Vector2f(getPos().x + getSize().x / 2 - 20, getPos().y + getSize().y / 2 - 11.f), projectileVec, EntityType::EnemyEntity);
		}
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