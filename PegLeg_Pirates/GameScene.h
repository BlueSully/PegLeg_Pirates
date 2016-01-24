#include "Player.h"
#include "EnemySword.h"
#include "EnemyGun.h"
#include "Projectile.h"
#include "ProjectileManager.h"
#include "waveManager.h"

class GameScene
{
private:
	sf::RenderWindow * m_screenWindow;

	sf::View camera;
	int killCount;
	int activeCount = 0;

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

	// Declare and load a texture
	sf::Texture m_playerSprite;
	sf::Texture m_floor, m_playerbody, m_shadow, m_meleeWeapon;
	sf::Sprite m_sprite;

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
	void initGame(sf::Vector2u windowSize);
	void initEnemy(sf::Vector2u windowSize);
	void enemyUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);
	void GameScene::initSoundEngine();
	void audioControls();

	void gameUpdate(sf::Time elapsedTime, sf::Vector2u windowSize);
	void gameUnload();
	void gameDraw(sf::RenderWindow * window);

	void updateView(sf::Time elapsedTime);
};