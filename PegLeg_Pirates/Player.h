#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Projectile.h"

class Player : public Entity{
private:
	std::vector<Projectile*> bulletArray;
	sf::Vector2f m_playerPos;
	char controlType = 'A';
	float m_jumpVec = 0;//jump velocity
	float m_oldjump = 0;//last position of the jump
	float m_tempJump = 0; //temp value for jump height and move speed
	float m_gravity = 981;//gravity on player
	bool m_isJumping = false;
	bool m_jumpPressed, m_lightAttackPressed, m_strongAttackPressed = false;
	float m_hitboxLife = 0.05f;//time weak attack stays alive
	float m_strongwindUp = 0.5f;//time strong attack stays alive
	bool m_weakAttack, m_strongAttack = false;
	bool m_facingRight = true;
	int m_speed;
	float m_invTime;
	bool m_firedGun = false;

	sf::Vector2f m_weaponSize;

	FMOD::Channel *channelFMOD;
	FMOD::System *sysFMOD;
	FMOD_RESULT *resultFMOD;
	FMOD::Sound *swordWoosh;
	FMOD::Sound *gunShot;
	bool sfxtoggled;
	bool num1Pressed;
	
public:
	Player();
	Player(sf::Vector2f value, FMOD::Channel * channel, FMOD::System *FMODsys, FMOD_RESULT *result, sf::Texture & bodySprite, sf::Texture & shadowSprite, sf::Texture & melee);

	bool isAlive();
	int getHitDamage();

	//methods
	void initSoundEngine(FMOD::System *FMODsys, FMOD_RESULT *result);
	void toggleSound(void);
		
	bool checkCollisionAttack(sf::Vector2f targetpos, sf::Vector2f targetsize);
	void attackMeleeController(sf::Time deltaTime);
	void attackRangedController(sf::Time deltaTime);
	void moveController(sf::Time deltaTime, char controlType, sf::Vector2f window);
	void jumpController(sf::Time deltaTime);
	void update(sf::Time deltaTime, sf::Vector2f window);
	virtual void draw(sf::RenderWindow * window);
};

#endif