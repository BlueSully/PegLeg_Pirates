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

using namespace sf;

enum Screens {
	TitleScreen,
	MenuScreen,
	OptionScreen,
	GameScreen,
	GameOverScreen
};

enum EnemyType {
	Sword,
	Gun,
	Bruiser,
	Boss
};


// TODO: reference additional headers your program requires here
