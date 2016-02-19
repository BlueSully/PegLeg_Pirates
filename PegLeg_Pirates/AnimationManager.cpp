#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	m_frameCount = 0;
	elapsedtime = 0;
}

AnimationManager::~AnimationManager()
{
	std::cout << "AnimationManager Destroyed" << std::endl;
}

std::pair<sf::Vector2f, sf::Vector2f> AnimationManager::getFrame()
{
	return std::make_pair(framePos, frameDim);
}

void AnimationManager::Update(int totalFrames, int rowNum, int colNum, float speed, sf::Vector2f size, sf::Time deltatime)
{
	m_numOfFrames = totalFrames;
	m_rowNum = rowNum;
	m_colNum = colNum;
	frameDim = size;
	if (m_numOfFrames != 0)
	{
		if (elapsedtime > speed)
		{
			int row = 0;
			int col = 0;

			if (m_rowNum != 0)
				row = m_frameCount % m_rowNum;
			if (m_colNum != 0)
				col = m_frameCount / m_colNum;

			framePos.x = ((frameDim.x * row)) + 1;
			framePos.y = ((frameDim.y * col)) + 1;
			
			m_frameCount++;
			elapsedtime = 0;
			if (m_frameCount > m_numOfFrames)
			{
				m_frameCount = 0;
			}
		}

		elapsedtime += deltatime.asSeconds();
	}
}

