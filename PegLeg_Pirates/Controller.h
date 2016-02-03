#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "stdafx.h"

class Controller
{
private:
	bool keyPressed = false;
	int lastEntered;
	int left, right, up, down, lightAttack, HeavyAttack, Shoot, Jump, Enter;
public:
	Controller();
	~Controller();

	bool HandleInput(sf::Event * evt, sf::Keyboard::Key key);
};

#endif
