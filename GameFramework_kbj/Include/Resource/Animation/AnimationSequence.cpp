#include "AnimationSequence.h"

CAnimationSequence::CAnimationSequence()
{
}

CAnimationSequence::~CAnimationSequence()
{
}

void CAnimationSequence::AddFrame(const Vector2& start, const Vector2& end)
{
	AnimationFrameData	data = {};
	data.start = start;
	data.end = end;
	m_vecFrame.push_back(data);
}

void CAnimationSequence::AddFrame(float posX, float posY, float sizeX, float sizeY)
{
	AnimationFrameData	data = {};
	data.start = Vector2(posX, posY);
	data.end = Vector2(posX+sizeX, posY+sizeY);
	m_vecFrame.push_back(data);
}
