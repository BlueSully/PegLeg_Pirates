#pragma once

#include "stdafx.h"
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <utility> 

class AnimationManager{
private:
	int m_maxframes;
	int m_frameCount;
	int m_numOfFrames;//Total Number of Frames
	int m_rowNum;//Number of rows to be used
	int m_colNum;//Number of Frames on a Column
	bool m_finished = false;//Aniamtion finished
	float elapsedtime;//Time to update
	sf::Vector2f framePos;//sprite frame source Position
	sf::Vector2f frameDim;//sprite frame dimensions

public:
	AnimationManager();
	~AnimationManager();
	std::pair<sf::IntRect, bool> Update(int &frame, int totalanimationFrames, int rowNum, int colNum, float speed, sf::Vector2f size, sf::Time deltatime);
	std::pair<sf::IntRect, bool> Update(int &frame, int totalanimationFrames, int rowNum, int colNum, float speed, sf::Vector2f size, sf::Time deltatime, bool hold, int framenum);

};