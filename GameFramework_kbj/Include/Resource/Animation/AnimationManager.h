#pragma once
#include "../../GameInfo.h"

class CAnimationManager
{
private:
	friend class CResourceManager;
	std::unordered_map<std::string, CSharedPtr<class CAnimationSequence>>	m_mapSequence;
	CAnimationManager();
	~CAnimationManager();
public:
	bool Init();
	bool CreateAnimationSequence(const std::string& name, class CTexture* texture);
	bool AddAnimationFrame(const std::string& name, const Vector2& start,const Vector2& end);
	bool AddAnimationFrame(const std::string& name,float posX, float posY, float sizeX, float sizeY);
	class CAnimationSequence* FindAnimation(const std::string& name);
	void ReleaseAnimation(const std::string& name);
};

