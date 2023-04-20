#pragma once
#include "../../Ref.h"
#include "../Texture/Texture.h"

class CAnimationSequence :public CRef
{
private:
	friend class CAnimationManager;
	friend class CAnimationInfo;
	CSharedPtr<CTexture>  m_texture;
	std::vector<AnimationFrameData> m_vecFrame;
	CAnimationSequence();
	~CAnimationSequence();
public:
    CTexture* GetTexture()    const
    {
        return m_texture;
    }
    ETexture_Type GetTextureType()  const
    {
        return m_texture->GetTextureType();
    }
    const AnimationFrameData& GetFrame(int index)   const
    {
        return m_vecFrame[index];
    }
    int GetFrameCount() const
    {
        return (int)m_vecFrame.size();
    }
    void AddFrame(const Vector2& start, const Vector2& end);
    void AddFrame(float posX, float posY, float sizeX, float sizeY);
};

