#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "ProjectileManager.h"

class Player : public Entity{
private:
	sf::Vector2f m_playerPos;
	char controlType = 'A';
	AnimationManager animationM;
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
	int framecount = 0;
	bool m_firedGun = false;
	bool m_lightAtkAnimation = false;
	bool m_strongAtkingAnimation = false;
	bool m_gunShootAnimation = false;
	int m_NumbodySprites;
	int m_bodyHeight;
	int m_bodyWidth;

	bool left, right, up, down, lightAttack, heavyAttack, jump, enter, shoot;//keyboard

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
	~Player();
	bool isAlive();
	int getHitDamage();

	//methods
	void initSoundEngine(FMOD::System *FMODsys, FMOD_RESULT *result);
	void toggleSound(void);
		
	bool checkCollisionAttack(sf::Vector2f targetpos, sf::Vector2f targetsize);
	void attackMeleeController(sf::Time deltaTime);
	void attackRangedController(sf::Time deltaTime, ProjectileManager *manager);
	void moveController(sf::Time deltaTime, char controlType, sf::Vector2f window, sf::IntRect viewportRect);
	void jumpController(sf::Time deltaTime);
	void update(sf::Time deltaTime, sf::Vector2f window, ProjectileManager *manager, sf::IntRect viewportRect);
	virtual void draw(sf::RenderWindow * window);
};

#endif