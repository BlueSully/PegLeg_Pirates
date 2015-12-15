#include "Player.h"
#include "EnemySword.h"
#include "stdafx.h"
#include <stdlib.h>    
#include <time.h>    
#include "Projectile.h"

class SceneManager{
private:
	int m_sceneIndex;//Holds what screen is 
	sf::CircleShape c1, c2, c3, c4;//testers circles
	sf::RenderWindow * m_screenWindow;

	sf::View camera;
	int killCount;
	int nextWave;
	int activeCount;

	bool debugPressed;
	bool cameraLocked;
	bool cameraMoving;
	
	bool num2Pressed;
	bool num3Pressed;
	bool num4Pressed;

	bool canReverbPlay;
	bool canBGMPlay;
	bool can3DsoundPlay;

	sf::RectangleShape viewport;
	sf::IntRect spawnZone;
	bool moveWave;
	sf::Vector2f nextCameraPos;
	std::vector<int> cameraXZones;

	// Declare and load a texture
	sf::Texture m_playerSprite;
	sf::Texture m_floor, m_playerbody, m_shadow, m_meleeWeapon;

	sf::Sprite m_sprite;

	float m_enemyOnScreenCount;

	int groupADist = 0;
	int groupBDist;
	int groupCDist;
	int totalEnemySize = 40;

	Player player;

	std::vector<EnemySword *> enemyMelee;
	std::vector<Entity *> entities;

	sf::CircleShape ambientAudioball;
	sf::CircleShape reverbAudioball;

	Sound *background;

	FMOD::Sound *sound;
	FMOD::Channel *channel = 0;
	FMOD::Reverb *reverb;
	float mindist = 0.0f;
	float maxdist = 400;
	FMOD::System *FMODsys; //will point to the FMOD system
	FMOD_RESULT result;
	FMOD::Sound *sound3D;

	FMOD_VECTOR  listenervel;
	FMOD_VECTOR  listenerpos;
	FMOD_VECTOR  sourcePos;
public:
	SceneManager();
	SceneManager(sf::RenderWindow &window);

	int getIndex();
	void setIndex(int value);

	//SceneManager Methods
	void checkindex();
	void initSoundEngine();
	void getNextScreen();
	void updateView(sf::Time elapsedTime);
	void update(sf::Time elapsedTime);
	void draw();

	//GameScreen Methods
	void initGame(sf::Vector2u windowSize);
	void initEnemy(sf::Vector2u windowSize);
	void audioControls();
	void gameUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);
	void gameUnload();
	void gameDraw(sf::RenderWindow * window);
};