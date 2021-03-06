#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

enum HitType
{
	light,
	heavy,
	gun,
	sword,
};

Player::Player(sf::Vector2f value, FMOD::Channel * channel, FMOD::System *FMODsys, FMOD_RESULT *result, sf::Texture & bodySprite, sf::Texture & shadowSprite, sf::Texture & melee) : m_playerPos(value)
{
	m_speed = 125;//pixels wished to move
	m_NumbodySprites = 5*10;
	m_bodyWidth = 65;
	m_bodyHeight = 58;
	m_body = sf::Sprite(bodySprite, sf::IntRect(1, 1, m_bodyWidth, m_bodyHeight));
	m_body.setPosition(m_playerPos);
	m_fireCooldown = 0.0f;
	setSize(sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight));

	m_invTime = 1;
	m_bulletCount = 0;
	maxBullets = 1;
	m_shadow = sf::Sprite(shadowSprite, sf::IntRect(0, 0, shadowSprite.getSize().x, shadowSprite.getSize().y));

	m_shadowWidth = (int)shadowSprite.getSize().x;
	m_shadowHeight = (int)shadowSprite.getSize().y;

	sysFMOD = FMODsys;
	resultFMOD = result;
	channelFMOD = channel;
	m_weaponSize = sf::Vector2f((float)melee.getSize().x, (float)melee.getSize().y);
	m_weapon = sf::Sprite(melee, sf::IntRect(0, 0, (int)m_weaponSize.x, (int)m_weaponSize.y));
	m_oldjump = m_playerPos.y;
	m_health = 100;
	m_activated = true;
	m_isHit = num1Pressed = false;
	m_alive = m_canbeHit = sfxtoggled = true;
	m_hitType = -1;
	setHitDamage(50);
	setHealth(100);
	setMaxHealth(100);
	initSoundEngine(sysFMOD, resultFMOD);
}

//~~~~~~~~~~~~~~~~~~~METHODS
void Player::initSoundEngine(FMOD::System *FMODsys, FMOD_RESULT *result)
{
	*resultFMOD = sysFMOD->createSound("Music/SFX/woosh_miss.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &swordWoosh);
	*resultFMOD = sysFMOD->createSound("Music/SFX/Gunshot.wav", FMOD_LOOP_OFF | FMOD_2D, 0, &gunShot);
}

int Player::getHitDamage()
{
	if (m_hitType == HitType::light)
	{
		damage = (int)(m_damage * 0.5f);
	}
	else if (m_hitType == HitType::heavy)
	{
		damage = m_damage;
	}
	else if (m_hitType == HitType::gun)
	{
		damage = (int)(m_damage * 1.5f);
	}
	return damage;
}

int Player::getMaxHitDamage()
{
	return m_damage;
}

void Player::setHitDamage(int power)
{
	m_damage = power;
}

bool Player::CheckCollisionAttack(sf::Vector2f targetpos, sf::Vector2f targetsize)
{//Checking Melee Collision
	if (m_isAttacking && (m_weakAttack || m_strongAttack))
	{
		if ((m_weapon.getPosition().x < targetpos.x + targetsize.x &&
			m_weapon.getPosition().x + m_weaponSize.x > targetpos.x &&
			m_weapon.getPosition().y < targetpos.y + targetsize.y &&
			m_weaponSize.y + m_weapon.getPosition().y > targetpos.y))//checking if melee weapon hits
		{
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

void Player::AttackMeleeController(sf::Time deltaTime)
{
	if (m_facingRight)
		m_weapon.setPosition(sf::Vector2f(m_body.getPosition().x + m_bodyWidth, m_body.getPosition().y + m_bodyHeight / 2));
	else 
		m_weapon.setPosition(sf::Vector2f(m_body.getPosition().x - m_weaponSize.x, m_body.getPosition().y + m_bodyHeight / 2));

	if (lightAttack && !m_lightAttackPressed && !m_lightAtkAnimation)
	{
		m_lightAtkAnimation = m_isAttacking = m_weakAttack = m_lightAttackPressed = true;
		m_strongAtkingAnimation = m_strongAttackPressed = m_strongAttack = false;
		m_weapon.setColor(sf::Color::Magenta);
		framecount = 0;
		if (sfxtoggled)
		{
			sysFMOD->playSound(FMOD_CHANNEL_FREE, swordWoosh, false, 0);
		}
	}
	else if (!lightAttack)
	{
		m_lightAttackPressed = false;
	}

	if (heavyAttack && !m_strongAttackPressed && !m_strongAtkingAnimation)
	{
		m_lightAtkAnimation = m_weakAttack = m_lightAttackPressed = false;
		m_strongAtkingAnimation = m_isAttacking = m_strongAttackPressed = true;
		m_hitboxLife = 0.4f;
		framecount = 0;
		m_weapon.setColor(sf::Color::Green);
	}
	else if (!heavyAttack)
	{
		m_strongAttackPressed = false;
	}
	
	if (m_isAttacking)
	{
		if (m_weakAttack)
		{
			m_hitboxLife -= deltaTime.asSeconds();
		}
		else if (!m_strongAttackPressed)
		{
			m_strongwindUp -= deltaTime.asSeconds();

			if (m_strongwindUp < 0 || framecount == 3)
			{
				m_strongAttack = true;
				m_hitboxLife -= deltaTime.asSeconds();//time for attack to be removed
				m_weapon.setColor(sf::Color::Yellow);
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

void Player::AttackRangedController(sf::Time deltaTime, ProjectileManager* manager)
{
	if (shoot && m_firedGun == false && m_bulletCount != maxBullets)
	{
		m_firedGun = true;
		m_gunShootAnimation = true;
		m_bulletCount++;
		m_fireCooldown = 2.0f;
		float projectileVec;
		if (m_facingRight)
		{
			projectileVec = 500;
		}
		else
		{
			projectileVec = -500;
		}
		framecount = 0;
		if (m_facingRight)
		{
			manager->createProjectile(sf::Vector2f(getPos().x + getSize().x / 2 + 20, getPos().y + getSize().y / 2 - 11.f), projectileVec, EntityType::PlayerEntity);
		}
		else
		{
			manager->createProjectile(sf::Vector2f(getPos().x + getSize().x / 2 - 20, getPos().y + getSize().y / 2 - 11.f), projectileVec, EntityType::PlayerEntity);
		}
		sysFMOD->playSound(FMOD_CHANNEL_FREE, gunShot, false, 0);
	}
	else if (!shoot)
	{
		m_firedGun = false;
	}
	if (m_fireCooldown <= 0 && m_bulletCount != 0)
	{
		m_bulletCount--;
		m_fireCooldown = 2.0f;
	}
	m_fireCooldown -= deltaTime.asSeconds();
}

void Player::MoveController(sf::Time deltaTime, char controlType, sf::Vector2f window, sf::IntRect viewportRect)
{
	float m_tempSpeed = m_speed * deltaTime.asSeconds();

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
	else if (right && (int)(m_shadow.getPosition().x + m_shadowWidth) < (int)(viewportRect.left + viewportRect.width))
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

	if (up && (int)m_shadow.getPosition().y > (int)window.y / 2)
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
	else if (down && (int)m_shadow.getPosition().y + m_shadowHeight < (int)window.y)
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

void Player::JumpController(sf::Time deltaTime)
{
	float jumpheight = 500;

	if (m_jumpPressed == false && m_isJumping == false)
	{
		if (jump && !m_strongAttack)
		{
			m_jumpVec = jumpheight;
			m_isJumping = m_jumpPressed = true;
		}
	}
	else
	{
		if (!jump)
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

void Player::UpdateAnimation(sf::Time deltaTime)
{
	std::pair<sf::IntRect, bool> animation;

	if (m_deathAnimation)
	{
		if (m_facingRight)
		{
			animation = animationM.Update(framecount, 3, 3, 9, 0.3f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		else
		{
			animation = animationM.Update(framecount, 3, 3, 4, 0.3f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		if (animation.second == true)
		{
			m_deathAnimation = false;
			setAlive(false);
		}
	}
	else if (left && (!m_lightAtkAnimation && !m_strongAtkingAnimation && !m_isJumping && !m_gunShootAnimation))
	{
		animation = animationM.Update(framecount, 5, 5, 1, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
	}
	else if (right && (!m_lightAtkAnimation && !m_strongAtkingAnimation && !m_isJumping && !m_gunShootAnimation))
	{
		animation = animationM.Update(framecount, 5, 5, 6, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
	}
	else if ((up || down) && (!m_lightAtkAnimation && !m_strongAtkingAnimation && !m_isJumping && !m_gunShootAnimation))
	{
		if (m_facingRight)
		{
			animation = animationM.Update(framecount, 5, 5, 6, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		else
		{
			animation = animationM.Update(framecount, 5, 5, 1, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
	}
	else if (right && (!m_lightAtkAnimation && !m_strongAtkingAnimation && !m_isJumping && !m_gunShootAnimation))
	{
		animation = animationM.Update(framecount, 5, 5, 6, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
	}
	else if (m_lightAtkAnimation)
	{
		if (m_facingRight)
		{
			animation = animationM.Update(framecount, 4, 3, 8, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		else
		{
			animation = animationM.Update(framecount, 4, 3, 3, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		if (animation.second == true)
		{
			framecount = 0;
			m_lightAtkAnimation = false;
		}
	}
	else if (m_strongAtkingAnimation)
	{
		if (m_facingRight)
		{
			animation = animationM.Update(framecount, 4, 4, 8, 0.3f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime, m_strongAttackPressed, 1);
		}
		else
		{
			animation = animationM.Update(framecount, 4, 4, 3, 0.3f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime, m_strongAttackPressed, 1);
		}
		if (animation.second == true)
		{
			framecount = 0;
			m_strongAtkingAnimation = false;
		}
	}
	else if (m_gunShootAnimation)
	{
		if (m_facingRight)
		{
			animation = animationM.Update(framecount, 2, 2, 7, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		else
		{
			animation = animationM.Update(framecount, 2, 2, 2, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		if (animation.second == true)
		{
			framecount = 0;
			m_gunShootAnimation = false;
		}
	}
	else if (m_isJumping)
	{
		if (m_facingRight)
		{
			animation = animationM.Update(framecount, 3, 3, 5, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime, true, 0);
		}
		else
		{
			animation = animationM.Update(framecount, 3, 3, 0, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime, true, 0);
		}
	}
	else //standing still
	{
		if (m_facingRight)
		{
			animation = animationM.Update(framecount, 3, 3, 5, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
		else
		{
			animation = animationM.Update(framecount, 3, 3, 0, 0.1f, sf::Vector2f((float)m_bodyWidth, (float)m_bodyHeight), deltaTime);
		}
	}

	if (m_health <= 0 && !m_deathAnimation)
	{
		framecount = 0;
		m_deathAnimation = true;
	}
	else if (m_health > 0)
	{
		setAlive(true);
	}

	m_body.setTextureRect(animation.first);
}

void Player::Update(sf::Time deltaTime, sf::Vector2f window, ProjectileManager *manager, sf::IntRect viewportRect)
{
	//Updating controllers
	left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	lightAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::V);
	heavyAttack = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
	jump = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
	shoot = sf::Keyboard::isKeyPressed(sf::Keyboard::X);

	if (heavyAttack)
	{
		m_hitType = HitType::heavy;
	}
	else if (lightAttack)
	{
		m_hitType = HitType::light;
	}
	else if (shoot)
	{
		m_hitType = HitType::gun;
	}

	std::cout << m_hitType << std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		m_health = getMaxHealth();
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

	if (!m_deathAnimation)
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

		JumpController(deltaTime);

		if (!m_firedGun)//when not firing allow to move
		{
			if (!m_isAttacking)//when not attacking with sword allow movement
			{
				MoveController(deltaTime, controlType, window, viewportRect);
			}
			else if (m_isJumping)
			{
				MoveController(deltaTime, controlType, window, viewportRect);
			}
		}

		AttackMeleeController(deltaTime);
		AttackRangedController(deltaTime, manager);
	}

	UpdateAnimation(deltaTime);

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
	
	window->draw(m_shadow);
	window->draw(m_body);
	window->draw(shp);
}