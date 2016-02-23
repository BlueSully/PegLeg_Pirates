#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	m_frameCount = 0;
	elapsedtime = 0;
}

AnimationManager::~AnimationManager()
{

}

std::pair<sf::IntRect, bool> AnimationManager::Update(int &frame, int totalanimationFrames, int rowNum, int colNum, float speed, sf::Vector2f size, sf::Time deltatime)
{
	m_frameCount = frame;
	m_numOfFrames = totalanimationFrames;
	m_rowNum = rowNum;
	m_colNum = colNum;
	frameDim = size;
	m_finished = false;

	if (m_numOfFrames != 0 )
	{
		if (elapsedtime > speed)
		{
			int row = 0;
			int col = m_colNum;

			if (m_rowNum != 0)
				row = m_frameCount % m_rowNum;

			framePos.x = ((1 + frameDim.x) * row) + 1;
			framePos.y = ((1 + frameDim.y) * col) + 1;

			m_frameCount++;
			
			elapsedtime = 0;
			if (m_frameCount > m_numOfFrames)
			{
				m_frameCount = 0;
				
				m_finished = true;
			}
		}
		elapsedtime += deltatime.asSeconds();
	}

	frame = m_frameCount;

	return std::make_pair(sf::IntRect((int)framePos.x, (int)framePos.y, (int)frameDim.x, (int)frameDim.y), m_finished);
}

std::pair<sf::IntRect, bool> AnimationManager::Update(int &frame, int totalanimationFrames, int rowNum, int colNum, float speed, sf::Vector2f size, sf::Time deltatime, bool hold, int framenum)
{
	m_frameCount = frame;
	m_numOfFrames = totalanimationFrames;
	m_rowNum = rowNum;
	m_colNum = colNum;
	frameDim = size;
	m_finished = false;

	if (m_numOfFrames != 0)
	{
		if (elapsedtime > speed)
		{
			int row = 0;
			int col = m_colNum;

			if (m_rowNum != 0)
				row = m_frameCount % m_rowNum;

			framePos.x = ((1 + frameDim.x) * row) + 1;
			framePos.y = ((1 + frameDim.y) * col) + 1;

			elapsedtime = 0;//reset time

			if (hold == false || m_frameCount != framenum)
			{
				m_frameCount++;
				
				if (m_frameCount > m_numOfFrames)
				{
					m_frameCount = 0;
					m_finished = true;
				}
			}
		}

		elapsedtime += deltatime.asSeconds();
	}

	frame = m_frameCount;

	return std::make_pair(sf::IntRect((int)framePos.x, (int)framePos.y, (int)frameDim.x, (int)frameDim.y), m_finished);
}