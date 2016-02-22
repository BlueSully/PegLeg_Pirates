#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "stdafx.h"

#include "Player.h"
#include "EnemySword.h"
#include "EnemyGun.h"
#include "ProjectileManager.h"
#include "waveManager.h"

enum EnemyType
{
	Sword,
	Gun,
	Bruiser,
	Boss
};

class GameScene
{
private:
	sf::RenderWindow * m_screenWindow;

	sf::View camera;

	int killCount;
	int activeCount = 0;

	bool cameraLocked, cameraMoving;

	bool num2Pressed, num3Pressed, num4Pressed;

	bool canReverbPlay, canBGMPlay, can3DsoundPlay;

	sf::RectangleShape viewport;
	sf::IntRect viewportRect;

	// Declare and load a texture
	sf::Texture m_floorTex, m_railTex, m_skyTex;
	sf::Texture m_playerSprite, m_playerbody, m_shadow, m_meleeWeapon;

	sf::Texture m_meleeTex;
	sf::Sprite m_Deck, m_Railing, m_Sky;

	//Entities and entity controllers
	Player player;

	int totalEnemySize = 30;
	WaveManager waveManager;
	ProjectileManager projectileManager;
	std::vector<EnemySword *> enemyMelee;
	std::vector<EnemyGun *> enemyGun;
	std::vector<Entity *> entities;

	//ADUIO
	sf::CircleShape ambientAudioball;
	Sound *background;
	FMOD::Sound *sound3D;
	FMOD::Channel *channel = 0;
	FMOD::Reverb *reverb;
	float mindist = 0.0f;
	float maxdist = 400;
	FMOD::System *FMODsys; //will point to the FMOD system
	FMOD_RESULT result;
	FMOD_VECTOR  listenervel;
	FMOD_VECTOR  listenerpos;
	FMOD_VECTOR  sourcePos;

public:
	GameScene();
	GameScene(sf::Vector2u windowSize);
	~GameScene();

	void initGame(sf::Vector2u windowSize);
	void initEnemy(sf::Vector2u windowSize);
	
	void initSoundEngine();
	void audioControls();

	int gameUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);
	void enemyUpdate(sf::Time elapsedTime, sf::Vector2u windowSize, sf::IntRect viewportRect);
	void waveUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);

	void gameUnload();
	void gameDraw(sf::RenderWindow * window);

	void updateView(sf::Time elapsedTime);
};
#endif