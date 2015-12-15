#include "Player.h"


Player::Player()
{

}

Player::Player(sf::Vector2f value, FMOD::Channel * channel, FMOD::System *FMODsys, FMOD_RESULT *result, sf::Texture & bodySprite, sf::Texture & shadowSprite, sf::Texture & melee) : m_playerPos(value)
{
	name = "Player";
	m_speed = 125;//pixels wished to move
	m_body = sf::Sprite(bodySprite, sf::IntRect(1, 1, 65, 58));
	m_body.setPosition(m_playerPos);
	m_bodyWidth = 50;
	m_bodyHeight = 58;
	m_invTime = 1;
	m_shadow = sf::Sprite(shadowSprite, sf::IntRect(0, 0, shadowSprite.getSize().x, shadowSprite.getSize().y));

	m_shadowWidth = (float)shadowSprite.getSize().x;
	m_shadowHeight = (float)shadowSprite.getSize().y;

	sysFMOD = FMODsys;
	resultFMOD = result;
	channelFMOD = channel;
	m_weaponSize = sf::Vector2f((float)melee.getSize().x, (float)melee.getSize().y);
	m_weapon = sf::Sprite(melee, sf::IntRect(0, 0, (int)m_weaponSize.x, (int)m_weaponSize.y));
	m_oldjump = m_playerPos.y;
	m_health = 100;
	m_isHit = false;
	m_alive = true;
	m_canHit = true;
	sfxtoggled = true;
	num1Pressed = false;
	initSoundEngine(sysFMOD, resultFMOD);
}

//~~~~~~~~~~~~~~~~~~~METHODS
bool Player::isAlive()
{
	return m_alive;
}

void Player::initSoundEngine(FMOD::System *FMODsys, FMOD_RESULT *result)
{
	*resultFMOD = sysFMOD->createSound("Music/SFX/woosh_miss.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &swordWoosh);
	*resultFMOD = sysFMOD->createSound("Music/SFX/Gunshot.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &gunShot);
}


int Player::getHitDamage()
{
	int damage = 0;
	if (m_weakAttack)
	{
		damage = 700;
	}
	else if (m_strongAttack)
	{
		damage = 50;
	}
	return damage;
}

bool Player::checkCollisionAttack(sf::Vector2f targetpos, sf::Vector2f targetsize)
{//Checking Melee Collision
	if (m_isAttacking && (m_weakAttack || m_strongAttack))
	{
		if ((m_weapon.getPosition().x < targetpos.x + targetsize.x &&
			m_weapon.getPosition().x + m_weaponSize.x > targetpos.x &&
			m_weapon.getPosition().y < targetpos.y + targetsize.y &&
			m_weaponSize.y + m_weapon.getPosition().y > targetpos.y))//checking if melee weapon hits
		{
			//if (onSamePlaneY(targetpos, targetsize))
				return true;
		}
	}
	return false;
}

void Player::toggleSound()
{
	if (sfxtoggled)
	{
		sfxtoggled = false;
	}
	else if (!sfxtoggled)
	{
		sfxtoggled = true;
	}
}

void Player::attackMeleeController(sf::Time deltaTime)
{
	if (m_facingRight)
	{
		m_weapon.setPosition(sf::Vector2f(m_body.getPosition().x + m_bodyWidth - 25, m_body.getPosition().y + m_bodyHeight / 2));
		m_body.setTextureRect(sf::IntRect(1, (58 * 4) + 5, 65, 58));
	}
	else 
	{
		m_weapon.setPosition(sf::Vector2f(m_body.getPosition().x - m_weaponSize.x + 25, m_body.getPosition().y + m_bodyHeight / 2));
		m_body.setTextureRect(sf::IntRect(1, 1, 65, 58));
	}

	if (!m_isAttacking)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !m_lightAttackPressed)
		{
			m_isAttacking = m_weakAttack = m_lightAttackPressed = true;
			m_strongAttackPressed = m_strongAttack = false;
			m_weapon.setColor(sf::Color::Magenta);
			if (sfxtoggled)
			{
				sysFMOD->playSound(FMOD_CHANNEL_FREE, swordWoosh, false, 0);
			}
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			m_lightAttackPressed = false;
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && !m_strongAttackPressed)
		{
			m_weakAttack = m_lightAttackPressed = false;
			m_isAttacking = m_strongAttackPressed = true;
			m_hitboxLife = 0.4f;
			m_weapon.setColor(sf::Color::Green);
			
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			m_strongAttackPressed = false;
		}
	}
	else if (m_isAttacking)
	{
		if (m_weakAttack)
		{
			m_hitboxLife -= deltaTime.asSeconds();
		}
		else if (m_strongAttackPressed)
		{
			m_strongwindUp -= deltaTime.asSeconds();

			if (m_strongwindUp < 0)
			{
				m_strongAttack = true;
				m_hitboxLife -= deltaTime.asSeconds();//time for attack to be removed
				m_weapon.setColor(sf::Color::Yellow);
				if (sfxtoggled)
				{
					sysFMOD->playSound(FMOD_CHANNEL_FREE, swordWoosh, false, 0);
				}
			}
		}
	}

	if (m_hitboxLife < 0)
	{
		m_hitboxLife = 0.05f;
		m_strongwindUp = 0.5f;
		m_weakAttack = m_isAttacking = m_strongAttack = false;
	}
}

void Player::attackRangedController(sf::Time deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && m_firedGun == false)
	{
		m_firedGun = true;
		sf::Vector2f projectileVec;
		if (m_facingRight)
		{
			projectileVec = sf::Vector2f(500, 0);
		}
		else
		{
			projectileVec = sf::Vector2f(-500, 0);
		}

		Projectile *projectile = new Projectile(getPos(), projectileVec);
		bulletArray.push_back(projectile);
		sysFMOD->playSound(FMOD_CHANNEL_FREE, gunShot, false, 0);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_firedGun = false;
	}
}

void Player::moveController(sf::Time deltaTime, char controlType, sf::Vector2f window)
{
	float m_tempSpeed = m_speed * deltaTime.asSeconds();
	bool left, right, up, down;

	if (controlType == 'A')
	{
		left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
		up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	}
	else if (controlType == 'B')
	{
		left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	}

	if (left && (int)m_shadow.getPosition().x > 0)
	{
		if (!m_isJumping)
		{
			m_body.move(-m_tempSpeed, 0);
		}
		else 
		{
			m_body.move(-m_tempSpeed / 2, 0);
		}
	}
	//else if (right && (int)m_shadow.getPosition().x + m_shadowWidth < (int)window.x)
	else if (right)
	{
		if (!m_isJumping)
		{
			m_body.move(m_tempSpeed, 0);
		}
		else 
		{
			m_body.move(m_tempSpeed / 2, 0);
		}
	}
	
	//if (up && (int)m_shadow.getPosition().y >(int)window.y / 2)
	if (up)
	{
		if (!m_isJumping){
			m_body.move(0, -m_tempSpeed);
			m_oldjump += -m_tempSpeed;
		}
		else {
			m_body.move(0, -m_tempSpeed / 3);
			m_oldjump += -m_tempSpeed / 3;
		}
	}
	//else if (down && (int)m_shadow.getPosition().y + m_shadowHeight < (int)window.y)
	else if (down)
	{
		if (!m_isJumping)
		{
			m_body.move(0, m_tempSpeed);
			m_oldjump += m_tempSpeed;
		}
		else 
		{
			m_body.move(0, m_tempSpeed / 3);
			m_oldjump += m_tempSpeed / 3;
		}
	}

	if (left)
	{
		m_facingRight = false;
	}
	else if (right)
	{
		m_facingRight = true;
	}

}

void Player::jumpController(sf::Time deltaTime)
{
	float jumpheight = 500;

	if (m_jumpPressed == false && m_isJumping == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_strongAttack)
		{
			m_jumpVec = jumpheight;
			m_isJumping = m_jumpPressed = true;
		}
	}
	else
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_jumpPressed = false;
		}
	}
	if ((int)m_body.getPosition().y > (int)m_oldjump)//hit the floor
	{
		m_body.setPosition(m_body.getPosition().x, m_oldjump);
		m_isJumping = false;
		m_jumpVec = 0;
	}
	
	if (m_isJumping && m_strongAttack)
	{
		m_jumpVec -= m_gravity * 2 * deltaTime.asSeconds();
	}
	else if (m_isJumping)
	{//updating gravity
		m_jumpVec -= m_gravity * deltaTime.asSeconds();
	}
}

void Player::update(sf::Time deltaTime, sf::Vector2f window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		controlType = 'A';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
	{
		controlType = 'B';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		m_health = 100;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !num1Pressed)
	{
		toggleSound();
		num1Pressed = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		num1Pressed = false;
	}

	if (isHit() && getHitCoolDown() > 0)
	{
		setHitCoolDown(getHitCoolDown() - deltaTime.asSeconds());
		m_canHit = false;
	}
	else if (!isHit() && getHitCoolDown() < 0)
	{
		setHitCoolDown(0.4f);
		m_canHit = true;
	}

	jumpController(deltaTime);

	if (!m_isAttacking)
	{
		moveController(deltaTime, controlType, window);
	}
	else if (m_isJumping)
	{
		moveController(deltaTime, controlType, window);
	}

	attackMeleeController(deltaTime);
	attackRangedController(deltaTime);
	
	if (m_health < 0)
	{
		setAlive(false);
	}
	for (size_t i = 0; i < bulletArray.size(); i++)
	{
		bulletArray[i]->update(deltaTime);
	}

	m_body.move(sf::Vector2f(0, -m_jumpVec * deltaTime.asSeconds()));//updating jump
	m_playerPos = m_body.getPosition();
	m_shadow.setPosition(sf::Vector2f(m_body.getPosition().x + 3, m_oldjump + (m_bodyHeight - 15)));

	channelFMOD->setVolume(0.5f);
}

void Player::draw(sf::RenderWindow * window)
{
	sf::RectangleShape shp;
	shp.setPosition(sf::Vector2f(m_playerPos.x, m_playerPos.y -20));
	shp.setSize(sf::Vector2f((float)(getHealth() / 2), (float)(20)));

	for (size_t i = 0; i < bulletArray.size(); i++)
	{
		bulletArray[i]->draw(window);
	}
	window->draw(m_shadow);
	window->draw(m_body);
	window->draw(shp);
	if (m_isAttacking)
	{
		window->draw(m_weapon);//weapon for debugging purpose
	}
}

