#include "SceneManager.h"



SceneManager::SceneManager()
{
	

}

SceneManager::SceneManager(sf::RenderWindow &window)
{
	m_screenWindow = &window;

	c1.setRadius(20);
	c1.setPosition(sf::Vector2f(20, 50));
	c1.setFillColor(sf::Color(255, 255, 0));

	c2.setRadius(20);
	c2.setPosition(sf::Vector2f(250, 50));
	c2.setFillColor(sf::Color(255, 0, 0));

	c3.setRadius(20);
	c3.setPosition(sf::Vector2f(500, 50));
	c3.setFillColor(sf::Color(255, 0, 255));

	c4.setRadius(20);
	c4.setPosition(sf::Vector2f(780, 50));
	c4.setFillColor(sf::Color(0, 255, 255));
}

int SceneManager::getIndex()
{
	return m_sceneIndex;
}

void SceneManager::setIndex(int value)
{
	m_sceneIndex = value;
	checkindex();//initialises what screen is on
}

void SceneManager::checkindex()
{
	switch (m_sceneIndex)
	{
		case Screens::TitleScreen:
			break;
		case Screens::MenuScreen:
			break;
		case Screens::OptionScreen:
			break;
		case Screens::GameScreen:
			initGame(m_screenWindow->getSize());
			break;
		case Screens::GameOverScreen:
			break;
		default:
			break;
	}
}

void SceneManager::initSoundEngine()
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

	background->initialise();
	background->load("Music/BGM/Black Vortex.mp3");//creates a streamed sound
	background->setVolume(0.2f);
	background->play();

	result = FMODsys->createReverb(&reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_SEWERPIPE;
	reverb->setProperties(&prop);

	ambientAudioball.setRadius(20);
	ambientAudioball.setFillColor(sf::Color(0,255,0, 190));
	ambientAudioball.setOrigin(sf::Vector2f(ambientAudioball.getRadius() / 2, ambientAudioball.getRadius() / 2));
	ambientAudioball.setPosition(sf::Vector2f(500, 400));

	result = FMODsys->createSound("Music/SFX/OverWorld.mp3", FMOD_LOOP_NORMAL | FMOD_3D, 0, &sound3D);
	FMODsys->playSound(FMOD_CHANNEL_FREE, sound3D, false, &channel);
	
	channel->set3DMinMaxDistance(50, 10000);
}

void SceneManager::initGame(sf::Vector2u windowSize)
{
	// Creating floor
	m_floor.loadFromFile("Sprites/BackTex.png");
	m_playerbody.loadFromFile("Sprites/player.png");
	m_playerSprite.loadFromFile("Sprites/playerSpritesheet.png");
	m_shadow.loadFromFile("Sprites/shadow.png");
	m_meleeWeapon.loadFromFile("Sprites/meleeWeapon.png");

	initSoundEngine();

	camera = sf::View(sf::Vector2f((float)windowSize.x / 2, (float)windowSize.y / 2), sf::Vector2f((float)windowSize.x, (float)windowSize.y));
	cameraLocked = true;
	cameraMoving = false;
	debugPressed = false;
	moveWave = false;
	num2Pressed = false;
	num3Pressed = false;
	num4Pressed = false;

	spawnZone = sf::IntRect((int)camera.getCenter().x + 390, (int)-camera.getSize().y, 100, (int)camera.getSize().y * 3);

	nextWave = 4;
	groupBDist = windowSize.x / 2;
	groupCDist = windowSize.x;
	nextCameraPos = Vector2f(0, 0);
	cameraXZones.push_back((int)(camera.getCenter().x + windowSize.x / 2));

	viewport.setPosition((float)windowSize.x / 2 - windowSize.x / 2, (float)windowSize.y / 2 - windowSize.y / 2);
	viewport.setSize(sf::Vector2f((float)windowSize.x, (float)windowSize.y));

	m_sprite.setTexture(m_floor);
	m_floor.setRepeated(true);
	m_sprite.setTextureRect(sf::IntRect(0, 0, (int)windowSize.x * 3, (int)windowSize.y));
	m_sprite.setPosition(0, (float)windowSize.y / 2.0f);


	player = Player(sf::Vector2f(50, 500), channel, FMODsys, &result, m_playerSprite, m_shadow, m_meleeWeapon);
	entities.push_back(&player);
	killCount = 0;
	initEnemy(windowSize);
}

void SceneManager::initEnemy(sf::Vector2u windowSize)
{
	for (int i = 0; i < totalEnemySize; i++)
	{
		int row = i / 4;//Creates enemies in a grid
		int col = i % 4;
		int distance = 0;//select which group position it will be in
		int type = 0;

		if (i < (int)totalEnemySize / 5)
		{
			distance = groupADist;
		}
		else if (i >= totalEnemySize / 5 && i < totalEnemySize / 2)
		{
			distance = groupBDist;
		}
		else if (i >= totalEnemySize / 2)
		{
			distance = groupCDist;
		}

		//Add random number generator for other enemy types
		if (type == EnemyType::Sword)//intialise a sword enemy
		{
			EnemySword *enemy = new EnemySword();
			enemy->initialise(sf::Vector2f((float)windowSize.x + distance + (100 * row) + 10, (float)(windowSize.y / 2) + 70 * col), m_playerbody, m_shadow, m_meleeWeapon, i);//initialising enemy points
			enemyMelee.push_back(enemy);
			entities.push_back(enemyMelee[i]);//placing enemy pointers within array
		}
		else if (type = 1)//intialise a Gun enemy
		{

		}
		else if (type = 2)//intialise a Bruiser enemy
		{

		}
	}
}

void SceneManager::updateView(sf::Time elapsedTime)
{
	//Debugging Tools
	//*******************************************************************
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))//fix for when the player kills all enemies on screen
	{
		cameraLocked = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		cameraLocked = true;
	}
	//**********************DEBUGGING*************************************

	if (player.getPos().x > camera.getCenter().x && !cameraLocked)
	{
		camera.setCenter(camera.getCenter() + sf::Vector2f(125, 0) * elapsedTime.asSeconds());
	}
	if (player.getPos().y < camera.getCenter().y && !cameraLocked)
	{
		camera.setCenter(camera.getCenter() - sf::Vector2f(0, 125) * elapsedTime.asSeconds());
	}
	else if (player.getPos().y > camera.getCenter().y + 100 && !cameraLocked && camera.getCenter().y < camera.getSize().y / 2)
	{
		camera.setCenter(camera.getCenter() + sf::Vector2f(0, 125) * elapsedTime.asSeconds());
	}
	else if (camera.getCenter().y > camera.getSize().y / 2)
	{
		camera.setCenter(camera.getCenter().x, camera.getSize().y / 2);
	}
}

void SceneManager::getNextScreen()
{
	if (nextCameraPos.x == 0)
	{
		nextCameraPos.x = (float)groupBDist + 200;
	}
	else if (nextCameraPos.x == groupBDist + 200)
	{
		nextCameraPos.x = (float)groupBDist + 300;
	}

	viewport.setPosition(viewport.getPosition() + nextCameraPos);
}

void SceneManager::gameUpdate(sf::Time elapsedTime, sf::Vector2u windowSize)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && debugPressed == false)//fix for when the player kills all enemies on screen
	{
		spawnZone.left += 100;
		debugPressed = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R))//fix for when the player kills all enemies on screen
	{
		debugPressed = false;
	}

	for (int i = 0; i < totalEnemySize; i++)
	{
		if (killCount == (int)totalEnemySize / 5 && activeCount <= 0 && !cameraMoving && cameraLocked)
		{
			getNextScreen();//move screen
			cameraLocked = false;
			cameraMoving = true;
		}
		else if (killCount == (int)totalEnemySize / 2 && activeCount <= 0 && !cameraMoving && cameraLocked)
		{
			getNextScreen();
			cameraLocked = false;
			cameraMoving = true;
		}
		if (!enemyMelee[i]->isAlive() && enemyMelee[i]->isActivated())
		{
			killCount++;
			enemyMelee[i]->setActive(false);
			activeCount--;
		}
	}

	if (viewport.getPosition().x < (camera.getCenter().x - camera.getSize().x / 2) && !cameraLocked)
	{
		cameraLocked = true;
		cameraMoving = false;
		spawnZone.left = (int)(viewport.getPosition().x + camera.getSize().x);
	}

	if (killCount == nextWave && activeCount == 0)
	{
		spawnZone.left += 100;
		nextWave += 4;
	}

	updateView(elapsedTime);

	player.update(elapsedTime, sf::Vector2f(windowSize));

	for (size_t i = 0; i < enemyMelee.size(); i++)
	{
		sf::IntRect viewport = sf::IntRect((int)(camera.getCenter().x - camera.getCenter().x),
			(int)(camera.getCenter().y - camera.getCenter().y),
			(int)camera.getSize().x, (int)camera.getSize().y);

		if (spawnZone.contains((int)enemyMelee[i]->getPos().x, (int)enemyMelee[i]->getPos().y
			|| viewport.contains((int)enemyMelee[i]->getPos().x, (int)enemyMelee[i]->getPos().y)))
		{
			if (!enemyMelee[i]->isActivated()){
				enemyMelee[i]->setActive(true);//activate enemy if within spawning zone
				activeCount++;
			}
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
				sf::Vector2f((float)player.getSpriteBase().getTextureRect().width, (float)player.getSpriteBase().getTextureRect().height));
		}
	}

	audioControls();

	listenervel = { 0.0f, 0.0f, 0.0f };
	listenerpos = { player.getPos().x + player.getSize().x / 2, 0.0f, player.getPos().y };

	FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);

	sourcePos = { ambientAudioball.getPosition().x, 0.0f, ambientAudioball.getPosition().y };

	channel->set3DAttributes(&sourcePos, 0);

	reverb->set3DAttributes(&sourcePos, mindist, maxdist);

	std::cout << canReverbPlay << std::endl;

	FMODsys->update();
}

void SceneManager::audioControls()
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
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		num2Pressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !num3Pressed)
	{
		num3Pressed = true;
		if (!can3DsoundPlay)
		{
			can3DsoundPlay = true;
			channel->setPaused(can3DsoundPlay);
		}
		else if (can3DsoundPlay)
		{
			can3DsoundPlay = false;
			channel->setPaused(can3DsoundPlay);
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
			reverb->setActive(canReverbPlay);
		}
		else if (!canReverbPlay)
		{
			canReverbPlay = true;
			reverb->setActive(canReverbPlay);
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		num4Pressed = false;
	}
}

void SceneManager::gameDraw(sf::RenderWindow * window)
{
	if (killCount >= totalEnemySize)
	{
		setIndex(getIndex() + 1);
		killCount = 0;
	}
	
	sf::RectangleShape spawne;
	spawne.setPosition((float)spawnZone.left, (float)spawnZone.top);
	spawne.setSize(sf::Vector2f((float)spawnZone.width, (float)spawnZone.height));
	spawne.setFillColor(sf::Color(0, 255, 0, 84));

	viewport.setFillColor(sf::Color(255, 255, 255, 84));

	window->draw(m_sprite);
	//window->draw(spawne);
	//window->draw(viewport);

	//Error with Bufferring where objects stutterring on the same plane
	for (int i = 0; i < (int)entities.size(); i++)//bubble sort / z-buffer
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

	for (int i = 0; i < (int)entities.size(); i++)//bubble sort / z-buffer
	{
		if (entities[i]->isAlive())
		{
			entities[i]->draw(window);//draw
		}
	}
	if (!can3DsoundPlay)
	{
		window->draw(ambientAudioball);
	}

	window->setView(camera);
}

void SceneManager::update(sf::Time elapsedTime)
{
	if (getIndex() == GameScreen)
	{
		gameUpdate(elapsedTime, sf::Vector2u(m_screenWindow->getSize()));
	}
}

void SceneManager::draw()
{
	if (getIndex() == GameScreen)
	{
		gameDraw(m_screenWindow);
	}
	else if (getIndex() == TitleScreen)
	{
		m_screenWindow->draw(c1);
	}
	else if (getIndex() == MenuScreen)
	{
		m_screenWindow->draw(c2);
	}
	else if (getIndex() == OptionScreen)
	{
		m_screenWindow->draw(c3);
	}
	else if (getIndex() == GameOverScreen)
	{
		m_screenWindow->draw(c1);
		m_screenWindow->draw(c2);
		m_screenWindow->draw(c3);
	}
}