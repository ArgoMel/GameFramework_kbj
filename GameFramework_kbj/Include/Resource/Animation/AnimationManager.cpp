#include "AnimationManager.h"
#include "AnimationSequence.h"
#include "../Texture/Texture.h"

CAnimationManager::CAnimationManager()
{
}

CAnimationManager::~CAnimationManager()
{
}

bool CAnimationManager::Init()
{
	return true;
}

bool CAnimationManager::CreateAnimationSequence(const std::string& name, CTexture* texture)
{
	CAnimationSequence* sequence = FindAnimation(name);
	if (sequence)
	{
		return true;
	}
	sequence = new CAnimationSequence;
	sequence->SetName(name);
	sequence->m_texture = texture;
	m_mapSequence.insert(std::make_pair(name, sequence));
	return true;
}

bool CAnimationManager::AddAnimationFrame(const std::string& name, const Vector2& start, const Vector2& end)
{
	CAnimationSequence* sequence = FindAnimation(name);
	if (!sequence)
	{
		return false;
	}
	sequence->AddFrame(start, end);
	return true;
}

bool CAnimationManager::AddAnimationFrame(const std::string& name, float posX, float posY, float sizeX, float sizeY)
{
	CAnimationSequence* sequence = FindAnimation(name);
	if (!sequence)
	{
		return false;
	}
	sequence->AddFrame(posX, posY, sizeX, sizeY);
	return true;
}

CAnimationSequence* CAnimationManager::FindAnimation(const std::string& name)
{
	auto	iter = m_mapSequence.find(name);
	if (iter == m_mapSequence.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CAnimationManager::ReleaseAnimation(const std::string& name)
{
	auto	iter = m_mapSequence.find(name);
	if (iter == m_mapSequence.end())
	{
		return;
	}
	if (iter->second->GetRefCount() == 1)
	{
		m_mapSequence.erase(iter);
	}
}
