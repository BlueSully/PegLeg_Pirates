#include "Controller.h"

Controller::Controller()
{
	//Initialising Key
	left = sf::Keyboard::Left;
	right = sf::Keyboard::Right;
	up = sf::Keyboard::Up;
	down = sf::Keyboard::Down;
	lightAttack = sf::Keyboard::C;
	HeavyAttack = sf::Keyboard::V;
	Shoot = sf::Keyboard::X;
	Jump = sf::Keyboard::Space;
	Enter = sf::Keyboard::Z;
}

Controller::~Controller()
{

}

bool Controller::HandleInput(sf::Event * evt, sf::Keyboard::Key key)
{
	if ((evt->type == sf::Event::TextEntered || evt->type == sf::Event::KeyPressed) && keyPressed == false)
	{
		if (sf::Keyboard::isKeyPressed(key) && lastEntered != key)
		{
			lastEntered = key;
			keyPressed = true;
			return true;
		}
	}
	else if (evt->type != sf::Event::TextEntered && evt->type != sf::Event::KeyPressed)
	{
		keyPressed = false;
		return false;
	}
	std::cout << keyPressed << std::endl;
}