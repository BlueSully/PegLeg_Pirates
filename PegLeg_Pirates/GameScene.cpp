//this class is the actual game. fighting enemy waves.
#include "GameScene.h"


GameScene::GameScene()
{

}

GameScene::GameScene(sf::Vector2u windowSize)
{
	initGame(windowSize);
}

GameScene::~GameScene()
{
	std::cout << "GAMESCENE DESTROYED" << std::endl;

	for (std::vector<EnemySword *>::const_iterator it = enemyMelee.begin(); it != enemyMelee.end(); it++)
	{
		delete *it;
	}
	enemyMelee.clear();

	for (std::vector<EnemyGun *>::const_iterator it = enemyGun.begin(); it != enemyGun.end(); it++)
	{
		delete *it;
	}
	enemyGun.clear();

	entities.clear();
}

void GameScene::initGame(sf::Vector2u windowSize)
{
	// Creating floor
	m_floorTex.loadFromFile("Sprites/BackTex.png");
	m_railTex.loadFromFile("Sprites/Railing.png");
	m_skyTex.loadFromFile("Sprites/Sky.png");
	m_playerbody.loadFromFile("Sprites/player.png");
	m_playerSprite.loadFromFile("Sprites/playerSpritesheet.png");
	m_shadow.loadFromFile("Sprites/shadow.png");
	m_meleeWeapon.loadFromFile("Sprites/meleeWeapon.png");
	m_meleeTex.loadFromFile("Sprites/MeleePirate.png");
	initSoundEngine();

	cameraLocked = true;
	cameraMoving = false;
	num2Pressed = false;
	num3Pressed = false;
	num4Pressed = false;

	viewport.setPosition((float)windowSize.x / 2, (float)windowSize.y / 2);
	viewport.setSize(sf::Vector2f((float)windowSize.x, (float)windowSize.y));

	m_Deck.setTexture(m_floorTex);
	m_floorTex.setRepeated(true);
	m_Deck.setTextureRect(sf::IntRect(0, 0, (int)windowSize.x * 10, (int)windowSize.y));
	m_Deck.setPosition(0, (float)windowSize.y / 2.0f);

	m_Railing.setTexture(m_railTex);
	m_railTex.setRepeated(true);
	m_Railing.setTextureRect(sf::IntRect(0, 0, (int)m_railTex.getSize().x * 10, (int)m_railTex.getSize().y));
	m_Railing.setPosition(0, (float)(windowSize.y / 2.0f) - (m_railTex.getSize().y / 3)* 2.3f);

	m_Sky.setTexture(m_skyTex);
	m_skyTex.setRepeated(true);
	m_Sky.setTextureRect(sf::IntRect(0, 0, (int)m_skyTex.getSize().x * 10, (int)windowSize.y));
	m_Sky.setPosition(0, 0);

	camera = sf::View(sf::Vector2f((float)windowSize.x / 2, (float)windowSize.y / 2), sf::Vector2f((float)windowSize.x, (float)windowSize.y));
	player = Player(sf::Vector2f(50, 500), channel, FMODsys, &result, m_playerSprite, m_shadow, m_meleeWeapon);
	entities.push_back(&player);
	waveManager = WaveManager(sf::IntRect((int)camera.getCenter().x + 390, (int)-camera.getSize().y, 100, (int)camera.getSize().y * 3));

	killCount = 0;
	initEnemy(windowSize);
}

void GameScene::initSoundEngine()
{
	result = FMOD::System_Create(&FMODsys);         // Create the main system object.

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error!" << result << FMOD_ErrorString(result);
		exit(-1);
	}

	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error!" << result << FMOD_ErrorString(result);
		exit(-1);
	}

	//background->initialise();
	//background->load("Music/BGM/Black Vortex.mp3");//creates a streamed sound
	//background->setVolume(0.1f);
	//background->play();

	//result = FMODsys->createSound("Music/SFX/ambientMusic.mp3", FMOD_LOOP_NORMAL | FMOD_3D, 0, &sound3D);
	//FMODsys->playSound(FMOD_CHANNEL_FREE, sound3D, false, &channel);
	//channel->set3DMinMaxDistance(50, 1000);
}

void GameScene::initEnemy(sf::Vector2u windowSize)
{
	srand(time(NULL));
	for (int i = 0; i < totalEnemySize; i++)
	{
		int random = rand() % 10;
		int type;
		if (random <= 5)
		{
			type = 0;
		}
		if(random > 5)
		{
			type = 1;
		}

		if (type == EnemyType::Sword)//intialise a sword enemy
		{
			EnemySword *melee = new EnemySword();
			melee->initialise(sf::Vector2f((float)-1000, (float)(windowSize.y / 2) + 70), m_meleeTex, m_shadow, m_meleeWeapon, i);//initialising enemy points
			enemyMelee.push_back(melee);
			waveManager.addToWave(melee, rand() % 1 + 1);
			entities.push_back(melee);//placing enemy pointers within array
		}
		else if (type == EnemyType::Gun)//intialise a Gun enemy
		{
			EnemyGun *gun = new EnemyGun();
			gun->initialise(sf::Vector2f((float)-1000, (float)(windowSize.y / 2) + 70), m_playerbody, m_shadow, m_meleeWeapon, i);//initialising enemy points
			enemyGun.push_back(gun);
			waveManager.addToWave(gun, rand() % 1 + 1);
			entities.push_back(gun);//placing enemy pointers within array
		}
	}

	waveManager.initEnemiesPosition(windowSize);
}

void GameScene::updateView(sf::Time elapsedTime)
{
	if (player.getPos().x > camera.getCenter().x && !cameraLocked)
	{
		camera.setCenter(camera.getCenter() + sf::Vector2f(125, 0) * elapsedTime.asSeconds());
	}
	if (player.getPos().y < camera.getCenter().y && !cameraLocked)
	{
		camera.setCenter(camera.getCenter() - sf::Vector2f(0, 125) * elapsedTime.asSeconds());
	}
	else if (player.getPos().y > camera.getCenter().y + 100  && camera.getCenter().y < camera.getSize().y / 2)
	{
		camera.setCenter(camera.getCenter() + sf::Vector2f(0, 125) * elapsedTime.asSeconds());
	}
	else if (camera.getCenter().y > camera.getSize().y / 2)
	{
		camera.setCenter(camera.getCenter().x, camera.getSize().y / 2);
	}
}

int GameScene::gameUpdate(sf::Time elapsedTime, sf::Vector2u windowSize)
{
	if (waveManager.getWave1().size() == 0 && waveManager.getWave2().size() == 0
		&& waveManager.getWave3().size() == 0 && killCount >= totalEnemySize)//all enemies have been killed
	{
		return Screens::GameOverScreen;
		killCount = 0;
	}

	for (int i = 0; i < totalEnemySize; i++)
	{
		if (!cameraMoving && cameraLocked)
		{//check to see if camera is locked in place
			if (waveManager.getWave1().size() == 0 && waveManager.getCurStage() == Wave::wave1)
			{
				viewport.setPosition(viewport.getPosition().x + windowSize.x / 2, viewport.getPosition().y);//move screen
				cameraLocked = false;
				cameraMoving = true;
				waveManager.setCurStage(Wave::wave2);
			}
			else if (waveManager.getWave2().size() == 0 && waveManager.getCurStage() == Wave::wave2)
			{
				viewport.setPosition(viewport.getPosition().x + windowSize.x / 2, viewport.getPosition().y);
				cameraLocked = false;
				cameraMoving = true;
				waveManager.setCurStage(Wave::wave3);
			}
		}
	}

	if (viewport.getPosition().x < (camera.getCenter().x - camera.getSize().x / 2) && !cameraLocked)
	{
		cameraLocked = true;
		cameraMoving = false;
		waveManager.setSpawnPos((int)(viewport.getPosition().x + camera.getSize().x), waveManager.getSpawner().top);
	}

	updateView(elapsedTime);

	viewportRect = sf::IntRect((int)(camera.getCenter().x - camera.getSize().x / 2), 
							   (int)(camera.getCenter().y - camera.getSize().y / 2),
							   (int)camera.getSize().x, (int)camera.getSize().y);

	player.update(elapsedTime, sf::Vector2f(windowSize), &projectileManager, viewportRect);

	//enemyUpdate(elapsedTime, windowSize, viewportRect);
	//waveUpdate(elapsedTime, windowSize);

	projectileManager.update(elapsedTime);

	if (cameraLocked)
	{
		waveManager.updateTrigger(activeCount);
	}

	for (size_t i = 0; i < projectileManager.getEnemyBulletArray().size(); i++)
	{
		if (projectileManager.checkCollisions(player.getPos(), player.getSize(), EntityType::PlayerEntity))
		{
			player.setIsHit(true);
			if (player.isHit() && player.canHit())//player is hit by bullet
			{
				player.updateHealth(-15);
			}
		}
	}

//	listenervel = { 0.0f, 0.0f, 0.0f };
//	listenerpos = { player.getPos().x + player.getSize().x / 2, 0.0f, player.getPos().y };
//
//	FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
//
//	sourcePos = { ambientAudioball.getPosition().x, 0.0f, ambientAudioball.getPosition().y };
//
//	channel->set3DAttributes(&sourcePos, 0);
//
//	reverb->set3DAttributes(&sourcePos, mindist, maxdist);
//
//	FMODsys->update();
	return -1;
}

void GameScene::enemyUpdate(sf::Time elapsedTime, sf::Vector2u windowSize, sf::IntRect viewportRect)
{
	//Updating Melee Characters
	for (size_t i = 0; i < enemyMelee.size(); i++)
	{
		if (waveManager.getSpawner().contains((int)enemyMelee[i]->getPos().x, (int)enemyMelee[i]->getPos().y
			|| viewportRect.contains((int)enemyMelee[i]->getPos().x, (int)enemyMelee[i]->getPos().y)))
		{
			if (!enemyMelee[i]->isActivated()){
				enemyMelee[i]->setActive(true);//activate enemy if within spawning zone
				activeCount++;
			}
		}
		if (!enemyMelee[i]->isAlive() && enemyMelee[i]->isActivated())
		{
			killCount++;
			enemyMelee[i]->setActive(false);
			activeCount--;
		}

		if (enemyMelee[i]->isAlive() && enemyMelee[i]->isActivated())
		{
			if (enemyMelee[i]->getAttack())
			{
				player.setIsHit(true);
				if (player.isHit() && player.canHit())
				{
					player.updateHealth(-5);
				}
			}
			if (player.checkCollisionAttack(enemyMelee[i]->getPos(), enemyMelee[i]->getSize()))
			{
				enemyMelee[i]->setIsHit(true);
				if (enemyMelee[i]->isHit() && enemyMelee[i]->getHitCoolDown() <= 0)
				{
					enemyMelee[i]->setHitCoolDown(0.4f);
					enemyMelee[i]->updateHealth(-player.getHitDamage());
				}
			}

			enemyMelee[i]->update(elapsedTime, player.getPos(), player.getSize(), player.getSpriteBase().getPosition(),
				sf::Vector2f((float)player.getSpriteBase().getTextureRect().width, 
				(float)player.getSpriteBase().getTextureRect().height), viewportRect);
		}

		for (std::vector<EnemySword *>::const_iterator it = enemyMelee.begin(); it != enemyMelee.end(); it++)
		{
			if (!(*it)->isAlive() && !(*it)->isActivated())
			{
				enemyMelee.erase(std::remove(enemyMelee.begin(), enemyMelee.end(), (*it)), enemyMelee.end());//delete from vector array if not alive
			}
		}
	}

	//Updating Gun Characters
	for (size_t i = 0; i < enemyGun.size(); i++)
	{
		if (waveManager.getSpawner().contains((int)enemyGun[i]->getPos().x, (int)enemyGun[i]->getPos().y
			|| viewportRect.contains((int)enemyGun[i]->getPos().x, (int)enemyGun[i]->getPos().y)))
		{
			if (!enemyGun[i]->isActivated()){
				enemyGun[i]->setActive(true);//activate enemy if within spawning zone
				activeCount++;
			}
		}
		if (!enemyGun[i]->isAlive() && enemyGun[i]->isActivated())
		{
			killCount++;
			enemyGun[i]->setActive(false);
			activeCount--;
		}

		if (enemyGun[i]->isAlive() && enemyGun[i]->isActivated())
		{
			if (player.checkCollisionAttack(enemyGun[i]->getPos(), enemyGun[i]->getSize()))//player attacks enemy
			{
				enemyGun[i]->setIsHit(true);
				if (enemyGun[i]->isHit() && enemyGun[i]->getHitCoolDown() <= 0)
				{
					enemyGun[i]->setHitCoolDown(0.4f);
					enemyGun[i]->updateHealth(-player.getHitDamage());
				}
			}

			enemyGun[i]->update(elapsedTime, player.getPos(),
				player.getSize(), player.getSpriteBase().getPosition(),
				sf::Vector2f((float)player.getSpriteBase().getTextureRect().width,
				(float)player.getSpriteBase().getTextureRect().height), &projectileManager);
		}
		else if (!enemyGun[i]->isAlive() && !enemyGun[i]->isActivated())
		{
			for (std::vector<EnemyGun *>::const_iterator it = enemyGun.begin(); it != enemyGun.end(); it++)
			{
				if (!(*it)->isAlive() && !(*it)->isActivated())
				{
					enemyGun.erase(std::remove(enemyGun.begin(), enemyGun.end(), (*it)), enemyGun.end());
				}
			}
		}

	}
}

void GameScene::waveUpdate(sf::Time elapsedTime, sf::Vector2u windowSize)
{
	if (waveManager.getCurStage() == Wave::wave1)
	{
		for (size_t i = 0; i < waveManager.getWave1().size(); i++)
		{
			for (size_t j = 0; j < projectileManager.getPlayerBulletArray().size(); j++)
			{
				if (projectileManager.checkCollisions(waveManager.getWave1()[i]->getPos(), waveManager.getWave1()[i]->getSize(), EntityType::EnemyEntity))
				{
					waveManager.getWave1()[i]->setIsHit(true);
					if (waveManager.getWave1()[i]->isHit())//player is hit by bullet
					{
						waveManager.getWave1()[i]->updateHealth(-15);
					}
				}
			}
		}
	}
	else if (waveManager.getCurStage() == Wave::wave2)
	{
		for (size_t i = 0; i < waveManager.getWave2().size(); i++)
		{
			for (size_t j = 0; j < projectileManager.getPlayerBulletArray().size(); j++)
			{
				if (projectileManager.checkCollisions(waveManager.getWave2()[i]->getPos(), waveManager.getWave2()[i]->getSize(), EntityType::EnemyEntity))
				{
					waveManager.getWave2()[i]->setIsHit(true);
					if (waveManager.getWave2()[i]->isHit())//player is hit by bullet
					{
						waveManager.getWave2()[i]->updateHealth(-15);
					}
				}
			}
		}
	}
	else if (waveManager.getCurStage() == Wave::wave3)
	{
		for (size_t i = 0; i < waveManager.getWave3().size(); i++)
		{
			for (size_t j = 0; j < projectileManager.getPlayerBulletArray().size(); j++)
			{
				if (projectileManager.checkCollisions(waveManager.getWave3()[i]->getPos(), waveManager.getWave3()[i]->getSize(), EntityType::EnemyEntity))
				{
					waveManager.getWave3()[i]->setIsHit(true);
					if (waveManager.getWave3()[i]->isHit())//player is hit by bullet
					{
						waveManager.getWave3()[i]->updateHealth(-15);
					}
				}
			}
		}
	}

	waveManager.update();
}

void GameScene::audioControls()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && num2Pressed == false)
	{
		num2Pressed = true;
		if (!canBGMPlay){
			canBGMPlay = true;
			background->setPause(canBGMPlay);
		}
		else if (canBGMPlay)
		{
			canBGMPlay = false;
			background->setPause(canBGMPlay);
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !num3Pressed)
	{
		num3Pressed = true;
		if (!can3DsoundPlay)
		{
			can3DsoundPlay = true;
			//channel->setPaused(can3DsoundPlay);
		}
		else if (can3DsoundPlay)
		{
			can3DsoundPlay = false;
		//	channel->setPaused(can3DsoundPlay);
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		num3Pressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && !num4Pressed)
	{
		num4Pressed = true;
		if (canReverbPlay)
		{
			canReverbPlay = false;
		//	reverb->setActive(canReverbPlay);
		}
		else if (!canReverbPlay)
		{
			canReverbPlay = true;
		//	reverb->setActive(canReverbPlay);
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		num4Pressed = false;
	}
}

void GameScene::gameDraw(sf::RenderWindow * window)
{
	window->draw(m_Sky);
	window->draw(m_Deck);
	window->draw(m_Railing);
	
	//Error with Bufferring where objects stuttering on the same plane
	for (int i = 0; i < (int)entities.size(); i++)//bubble sort / z-buffer
	{
		if (waveManager.getSpawner().contains((int)entities[i]->getPos().x, (int)entities[i]->getPos().y
			|| viewportRect.contains((int)entities[i]->getPos().x, (int)entities[i]->getPos().y)))
		{
			for (int j = 0; j < (int)(entities.size() - 1) - i; j++)
			{
				if ((entities[j]->getPos().y - entities[j + 1]->getPos().y > 1
					|| entities[j + 1]->getPos().y - entities[j]->getPos().y > 1)
					&& (entities[i]->isAlive() && entities[j + 1]->isAlive()))//limiter added to stop Objects fighting for the same spot with minisule distances
				{
					if (entities[j]->getPos().y > entities[j + 1]->getPos().y)
					{
						std::swap(entities[j], entities[j + 1]);
					}
				}
			}
		}
	}

	for (int i = 0; i < (int)entities.size(); i++)//bubble sort / z-buffer
	{
		if (entities[i]->isAlive() && entities[i]->isActivated())
		{
			entities[i]->draw(window);//draw
		}
	}
	if (!can3DsoundPlay)
	{
		window->draw(ambientAudioball);
	}
	
	projectileManager.draw(window);

	window->setView(camera);
}