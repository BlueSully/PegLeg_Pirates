#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANGAER_H

#include "stdafx.h"
#include <utility>

class AnimationManager{
private:
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

	void Update(int totalFrames, int rowNum, int colNum, float speed, sf::Vector2f size, sf::Time deltatime);
	std::pair<sf::Vector2f, sf::Vector2f> getFrame();
};

#endif