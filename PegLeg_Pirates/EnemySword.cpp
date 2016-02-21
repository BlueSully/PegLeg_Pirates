#include "EnemySword.h"

EnemySword::EnemySword()
{
	//empty constructor
}

EnemySword::~EnemySword()
{
}

bool EnemySword::getAttack()
{
	return m_isAttacking;
}

bool EnemySword::isActivated()
{
	return m_activated;
}

void EnemySword::setActive(bool value)
{
	m_activated = value;
}

void EnemySword::setPos(sf::Vector2f value)
{
	m_pos = value;
	Entity::setPos(value);
}

void EnemySword::initialise(sf::Vector2f value, sf::Texture & bodySprite, sf::Texture & shadowSprite, sf::Texture & weaponSprite, int index)
{
	name = "Sword";
	m_pos = value;

	m_bodyWidth = 61;
	m_bodyHeight = 56;
	m_body = sf::Sprite(bodySprite, sf::IntRect(0, 0, (int)m_bodyWidth, (int)m_bodyHeight));
	m_body.setPosition(m_pos);

	setSize(sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight));

	m_offsetpixelsX = 8;
	m_shadow = sf::Sprite(shadowSprite, sf::IntRect(0, 0, shadowSprite.getSize().x, shadowSprite.getSize().y));
	m_shadow.setPosition(sf::Vector2f(m_body.getPosition().x + m_offsetpixelsX, (m_body.getPosition().y + m_bodyHeight) - m_shadow.getTexture()->getSize().y / 2));

	m_shadowWidth = (int)shadowSprite.getSize().x;
	m_shadowHeight = (int)shadowSprite.getSize().y;

	m_weapon = sf::Sprite(weaponSprite, sf::IntRect(0, 0, (int)weaponSprite.getSize().x, (int)weaponSprite.getSize().y));
	m_weapon.setPosition(sf::Vector2f(m_body.getPosition().x + m_bodyWidth - 25, m_body.getPosition().y + m_bodyHeight / 2)); 
	m_weaponSize = sf::Vector2f((float)weaponSprite.getSize().x, (float)weaponSprite.getSize().y);

	m_isAttacking = false;
	setIsHit(false);
	setAlive(true);
	m_speed = (float)(50);

	setHitCoolDown(0);
	timeToAttack = 5;//one second;
	m_health = 100;
	setMaxHealth(100);
}

void EnemySword::update(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize, sf::IntRect viewport)
{
	if (isHit() && getHitCoolDown() > 0)
	{
		setHitCoolDown(getHitCoolDown() - deltaTime.asSeconds());
	}
	else if (!isHit() && getHitCoolDown() < 0)
	{
		setHitCoolDown(0.4f);
		setIsHit(false);
	}

	if (m_health <= 0)
	{
		setAlive(false);
	}

	if (m_body.getPosition().x < targetbodyPos.x)//getting direction of enemy to attack
	{
		m_attackSideRight = true;
		m_attackSideLeft = false;
	}
	else if (m_body.getPosition().x > targetbodyPos.x)
	{
		m_attackSideLeft = true;
		m_attackSideRight = false;
	}

	if (m_attackSideRight)
	{
		m_weapon.setPosition(sf::Vector2f(m_body.getPosition().x + m_bodyWidth - 25, m_body.getPosition().y + m_bodyHeight / 2));
	}
	else if (m_attackSideLeft)
	{
		m_weapon.setPosition(sf::Vector2f(m_body.getPosition().x - m_weaponSize.x, m_body.getPosition().y + m_bodyHeight / 2));
	}

	if (checkCanAttack(deltaTime, targetbasePos, targetbaseSize))
	{
		checkAttackCollision(targetbodyPos, targetbodysize);
	}
	else 
	{
		m_isAttacking = false;
	}

	moveToward(deltaTime, targetbodyPos, targetbodysize, targetbasePos, targetbaseSize, viewport);

	std::pair<sf::IntRect, bool> animation;

	if (m_AtkAnimation)
	{
		if (m_attackSideRight)//check which side to to use sprites for
		{
			animation = animationM.Update(framecount, 5, 5, 6, 0.2f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		else if (m_attackSideLeft)
		{
			animation = animationM.Update(framecount, 5, 5, 2, 0.2f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}

		if (framecount == 2)//hit
		{
			m_isAttacking = true;
		}
		if (animation.second == true)//animation finished one run through
		{
			m_AtkAnimation = false;
			framecount = 0;
		}
	}
	else
	{
		if (m_attackSideRight)
		{
			animation = animationM.Update(framecount, 6, 6, 5, 0.2f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		else if (m_attackSideLeft)
		{
			animation = animationM.Update(framecount, 6, 6, 1, 0.2f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		if (animation.second == true)//animation finished one run through
		{
			framecount = 0;
		}
		
	}
	m_body.setTextureRect(animation.first);//still left

	setPos(m_pos);
	m_shadow.setPosition(sf::Vector2f(m_body.getPosition().x + m_offsetpixelsX, (m_body.getPosition().y + m_bodyHeight) - m_shadow.getTexture()->getSize().y / 2));
}

void EnemySword::moveToward(sf::Time deltaTime, sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize, sf::Vector2f targetbasePos, sf::Vector2f targetbaseSize, sf::IntRect viewport)
{
	if ((int)targetbodyPos.x > (int)getPos().x + getSize().x)
	{
		m_pos.x += m_speed * deltaTime.asSeconds();//heading right
	}
	else if ((int)targetbodyPos.x + targetbodysize.x < (int)getPos().x)
	{
		m_pos.x -= m_speed * deltaTime.asSeconds();//heading left
	}

	if ((int)targetbasePos.y > (int)m_shadow.getPosition().y)//moving down
	{
		m_pos.y += m_speed * deltaTime.asSeconds();
	}
	else if ((int)targetbasePos.y < (int)m_shadow.getPosition().y + m_shadowHeight)
	{
		m_pos.y -= m_speed * deltaTime.asSeconds();
	}
}

bool EnemySword::checkCanAttack(sf::Time deltaTime, sf::Vector2f targetBasePos, sf::Vector2f targetBaseSize)
{
	if (timeToAttack > 0)
	{
		timeToAttack -= deltaTime.asSeconds();//updating cooldown
	}
	else if (timeToAttack <= 0)//can enemy attack
	{
		if (onSamePlaneY(targetBasePos, targetBaseSize))
		{
			return true;
		}
	}

	return false;
}

void EnemySword::checkAttackCollision(sf::Vector2f targetbodyPos, sf::Vector2f targetbodysize)
{
	if ((m_weapon.getPosition().x < targetbodyPos.x + targetbodysize.x &&
		m_weapon.getPosition().x + m_weaponSize.x > targetbodyPos.x &&
		m_weapon.getPosition().y < targetbodyPos.y + targetbodysize.y &&
		m_weaponSize.y + m_weapon.getPosition().y > targetbodyPos.y))
	{
		m_AtkAnimation = true;
		framecount = 0;//reset frame to zero
		timeToAttack = 5;
	}
}

void EnemySword::changeColour()
{
	m_body.setColor(orgColour);
}

void EnemySword::draw(sf::RenderWindow * window)
{

	
	//Drawing 
	window->draw(m_shadow);
	window->draw(m_body);
	window->draw(m_weapon);//weapon for debugging purpose

	sf::RectangleShape shp;
	shp.setPosition(sf::Vector2f(m_body.getPosition().x, m_body.getPosition().y - 20));
	shp.setSize(sf::Vector2f((float)getHealth() / 2, (float)20));
	window->draw(shp);
}