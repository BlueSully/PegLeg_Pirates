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
	float m_gravity = 981;//gravity on player pixels per second
	bool m_isJumping = false;
	bool m_jumpPressed, m_lightAttackPressed, m_strongAttackPressed = false;
	float m_hitboxLife = 0.05f;//time weak attack stays alive
	float m_strongwindUp = 0.5f;//time strong attack stays alive
	bool m_weakAttack, m_strongAttack = false;
	bool m_facingRight = true;
	int m_speed;
	int m_damage = 0;
	float m_invTime;
	int framecount = 0;
	bool m_firedGun = false;
	bool m_lightAtkAnimation = false;
	bool m_strongAtkingAnimation = false;
	bool m_gunShootAnimation = false;
	bool m_deathAnimation = false;
	int m_NumbodySprites;
	int m_bodyHeight;
	int m_bodyWidth;
	int m_hitType;

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

	int getHitDamage();
	void setHitDamage(int power);
	void toggleSound(void);

	//methods
	void initSoundEngine(FMOD::System *FMODsys, FMOD_RESULT *result);	
	bool CheckCollisionAttack(sf::Vector2f targetpos, sf::Vector2f targetsize);
	void AttackMeleeController(sf::Time deltaTime);
	void AttackRangedController(sf::Time deltaTime, ProjectileManager *manager);
	void MoveController(sf::Time deltaTime, char controlType, sf::Vector2f window, sf::IntRect viewportRect);
	void JumpController(sf::Time deltaTime);
	void UpdateAnimation(sf::Time deltaTime);
	void Update(sf::Time deltaTime, sf::Vector2f window, ProjectileManager *manager, sf::IntRect viewportRect);
	virtual void draw(sf::RenderWindow * window);
};

#endif