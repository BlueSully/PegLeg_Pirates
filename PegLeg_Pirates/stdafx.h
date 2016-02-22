// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#include "targetver.h"

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

<<<<<<< HEAD
=======
#include "AnimationManager.h"

>>>>>>> 8a8876937c56b69155def7748f90e4598657636f
#include "sound.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <stdio.h>
#include <tchar.h>  
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

enum Screens
{
	TitleScreen,
	MenuScreen,
	OptionScreen,
	LevelComplete,
	GameScreen,
	GameOverScreen,
	LevelSel,
};

enum Wave 
{
	wave1,
	wave2,
	wave3,
	bossWave
};

// TODO: reference additional headers your program requires here
