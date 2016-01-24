// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "sound.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <stdio.h>
#include <tchar.h>  
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace sf;

enum Screens {
	TitleScreen,
	MenuScreen,
	OptionScreen,
	LevelSel,
	GameScreen,
	GameOverScreen
};

enum EntityType {
	PlayerEntity,
	EnemyEntity,
	BossEntity,
	ObjectEntity
};

enum Stage {
	Stage1,
	Stage2,
	Stage3
};

enum EnemyType {
	Sword,
	Gun,
	Bruiser,
	Boss
};


// TODO: reference additional headers your program requires here
