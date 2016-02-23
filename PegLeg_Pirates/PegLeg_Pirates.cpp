// PegLeg_Pirates.cpp : Defines the entry point for the console application.
//
#include "stdafx.h" 

#ifdef _DEBUG 
#pragma comment(lib, "sfml-graphics-d.lib") 
#pragma comment(lib, "sfml-audio-d.lib") 
#pragma comment(lib, "sfml-system-d.lib") 
#pragma comment(lib, "sfml-window-d.lib") 
#pragma comment(lib, "sfml-network-d.lib")
#else 
#pragma comment(lib, "sfml-graphics.lib") 
#pragma comment(lib, "sfml-audio.lib") 
#pragma comment(lib, "sfml-system.lib") 
#pragma comment(lib, "sfml-window.lib") 
#pragma comment(lib, "sfml-network.lib") 
#endif 
#pragma comment(lib, "opengl32.lib") 
#pragma comment(lib, "glu32.lib") 
#pragma comment(lib, "fmodex_vc.lib")

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "SceneManager.h"

//FMOD includes



//#include "fmod.hpp"
//#include "fmod_errors.h"

//Controls 
// Up, down, left, right: Movement
// Z: Enter
// X: Shoot/Back
// C: Heavy attack
// V: light attack
int main()
{
	
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Pegleg Priates");
	sf::Clock clock;
	
	SceneManager ManagerScreen(window);
	ManagerScreen.setIndex(Screens::UpgradeScreen);

	while (window.isOpen())
	{
		sf::Event Event;
		sf::Time elapsedTime = clock.restart();

		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed){
				window.close();
			}
		}
		 
		ManagerScreen.update(&Event, elapsedTime);

		window.clear();
		ManagerScreen.draw();
		window.display();
	}

	return EXIT_SUCCESS;
}
