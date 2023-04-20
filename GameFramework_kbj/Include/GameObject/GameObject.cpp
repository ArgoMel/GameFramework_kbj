#include "GameObject.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneCollision.h"
#include "../Resource/Animation/AnimationSequence.h"
#include "../GameManager.h"	//델타타임
#include "../Scene/Camera.h"
#include "../Collision/Collider.h"
#include "../PathManager.h"
#include "TileMap.h"
#include "Tile.h"

CGameObject::CGameObject()
	: m_scene(nullptr)
	, m_animation(nullptr)
	, m_timeScale(1.f)
	, m_moveSpeed(0.f)
	, m_renderLayer(ERender_Layer::Default)
	, m_physicsSimulate(false)
	, m_ground(false)
	, m_gravityAccel(10.f)
	, m_fallTime(0.f)
	, m_fallStartY(0.f)
	, m_jump(false)
	, m_jumpVelocity(0.f)
	, m_SideWallCheck(false)
	, m_Start(false)
	, m_HaveShoes(false)
	, m_IsSlip(false)
{
	SetTypeID<CGameObject>();
}

CGameObject::CGameObject(const CGameObject& obj)
	:CRef(obj)
	, m_scene(nullptr)
	, m_animation(nullptr)
	, m_timeScale(obj.m_timeScale)
	, m_moveSpeed(obj.m_moveSpeed)
	, m_renderLayer(obj.m_renderLayer)
	, m_pos(obj.m_pos)
	, m_size(obj.m_size)
	, m_pivot(obj.m_pivot)
	, m_physicsSimulate(obj.m_physicsSimulate)
	, m_ground(false)
	, m_gravityAccel(obj.m_gravityAccel)
	, m_fallTime(0.f)
	, m_fallStartY(0.f)
	, m_jump(false)
	, m_jumpVelocity(obj.m_jumpVelocity)
	, m_SideWallCheck(obj.m_SideWallCheck)
	, m_Start(false)
	, m_HaveShoes(false)
	, m_IsSlip(false)
{
}

CGameObject::~CGameObject()
{
	{
		auto	iter = m_colliderList.begin();
		auto	iterEnd = m_colliderList.end();
		for (; iter != iterEnd; ++iter)
		{
			(*iter)->ClearCollisionList();
		}
	}
	{
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();
		for (; iter != iterEnd; ++iter)
		{
			(*iter)->SetActive(false);
		}
	}
	SAFE_DELETE(m_animation);
}

CCollider* CGameObject::FindCollider(const std::string& name)
{
	auto	iter = m_colliderList.begin();
	auto	iterEnd = m_colliderList.end();
	for (; iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == name)
		{
			return *iter;
		}
	}
	return nullptr;
}

void CGameObject::SetTexture(const std::string& name)
{
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
	SetSize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
}

void CGameObject::SetTexture(CTexture* texture)
{
	m_texture = texture;
	SetSize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
}

void CGameObject::SetTexture(const std::string& name, const TCHAR* fileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, fileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
	if (m_texture)
	{
		SetSize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
	}
}

void CGameObject::SetTextureFullPath(const std::string& name, const TCHAR* fullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, fullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
	SetSize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
}

bool CGameObject::SetColorKey(unsigned char r, unsigned char g, unsigned char b, int index)
{
	if (!m_texture)
	{
		return false;
	}
	m_texture->SetColorKey(r, g, b, index);
	return true;
}

bool CGameObject::SetColorKeyAll(unsigned char r, unsigned char g, unsigned char b)
{
	if (!m_texture)
	{
		return false;
	}
	m_texture->SetColorKeyAll(r, g, b);
	return true;
}

void CGameObject::CreateAnimation()
{
	m_animation = new CAnimation;
	m_animation->m_owner = this;
	m_animation->m_scene = m_scene;
}

void CGameObject::AddAnimation(const std::string& sequenceName, bool loop, float playTime, float playScale, bool reverse)
{
	m_animation->AddAnimation(sequenceName, loop, playTime, playScale, reverse);
}

void CGameObject::SetPlayTime(const std::string& name, float playTime)
{
	m_animation->SetPlayTime(name, playTime);
}

void CGameObject::SetPlayScale(const std::string& name, float playScale)
{
	m_animation->SetPlayScale(name, playScale);
}

void CGameObject::SetPlayLoop(const std::string& name, bool loop)
{
	m_animation->SetPlayLoop(name, loop);
}

void CGameObject::SetPlayReverse(const std::string& name, bool reverse)
{
	m_animation->SetPlayReverse(name, reverse);
}

void CGameObject::SetCurrentAnimation(const std::string& name)
{
	m_animation->SetCurrentAnimation(name);
}

void CGameObject::ChangeAnimation(const std::string& name)
{
	m_animation->ChangeAnimation(name);
}

bool CGameObject::CheckCurrentAnimation(const std::string& name)
{
	return m_animation->CheckCurrentAnimation(name);
}

void CGameObject::MoveDir(const Vector2& dir)
{
	m_pos += dir * m_moveSpeed * DELTA_TIME * m_timeScale;
}

void CGameObject::Move(const Vector2& moveValue)
{
	m_pos += moveValue *DELTA_TIME*m_timeScale;
}

void CGameObject::MoveAngle(const Vector2& angle)
{
	Vector2	Dir;
	Dir.x = cosf(DegreeToRadian(angle.x));
	Dir.y = sinf(DegreeToRadian(angle.y));
	m_pos += Dir * m_moveSpeed * DELTA_TIME * m_timeScale;
}

void CGameObject::Move(float angle)
{
	Vector2	Dir;
	Dir.x = cosf(DegreeToRadian(angle));
	Dir.y = sinf(DegreeToRadian(angle));
	m_pos += Dir * m_moveSpeed * DELTA_TIME * m_timeScale;
}

void CGameObject::Start()
{
	m_Start = true;
	m_prevPos = m_pos;
}

bool CGameObject::Init()
{
	return true;
}

void CGameObject::Update(float deltaTime)
{
	// 중력 적용
	//if (!m_ground && m_physicsSimulate)
	//{
	//	m_fallTime += deltaTime * m_gravityAccel;	// 떨어지는 시간을 누적시켜준다.
	//	// 9.8 m/s^2
	//	// t초 후 y값
	//	// V : 속도 A : 가속도 G : 중력
	//	// y = V * A - 0.5f * G * t * t
	//	// 0 = -0.5fGA^2 VA - y
	//	float velocity = 0.f;
	//	if (m_jump)
	//	{
	//		velocity = m_jumpVelocity * m_fallTime;
	//	}
	//	m_pos.y = m_fallStartY - (velocity - 0.5f * GRAVITY * m_fallTime * m_fallTime);
	//}
	if (m_animation)
	{
		m_animation->Update(deltaTime * m_timeScale);
	}
	{
		auto	iter = m_colliderList.begin();
		auto	iterEnd = m_colliderList.end();
		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_colliderList.erase(iter);
				iterEnd = m_colliderList.end();
				continue;
			}
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}
			(*iter)->Update(deltaTime);
			++iter;
		}
	}
	{
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();
		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_widgetComponentList.erase(iter);
				iterEnd = m_widgetComponentList.end();
				continue;
			}
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}
			(*iter)->Update(deltaTime);
			++iter;
		}
	}
}

void CGameObject::PostUpdate(float deltaTime)
{
	m_move = m_pos - m_prevPos;
	if (m_animation)
	{
		CAnimationInfo* current = m_animation->m_currentAnimation;
		const AnimationFrameData& frameData = current->m_sequence->GetFrame(current->m_frame);
		m_size = frameData.end - frameData.start;
	}
	{
		auto	iter = m_colliderList.begin();
		auto	iterEnd = m_colliderList.end();
		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_colliderList.erase(iter);
				iterEnd = m_colliderList.end();
				continue;
			}
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}
			(*iter)->PostUpdate(deltaTime);
			m_scene->GetCollision()->AddCollider(*iter);
			++iter;
		}
	}
	{
		auto	iter = m_widgetComponentList.begin();
		auto	iterEnd = m_widgetComponentList.end();
		for (; iter != iterEnd;)
		{
			if (!(*iter)->GetActive())
			{
				iter = m_widgetComponentList.erase(iter);
				iterEnd = m_widgetComponentList.end();
				continue;
			}
			else if (!(*iter)->GetEnable())
			{
				++iter;
				continue;
			}
			(*iter)->PostUpdate(deltaTime);
			++iter;
		}
	}
	if (m_move.y != 0.f && m_SideWallCheck)
	{
		if (m_move.y > 0.f)
		{
			CheckFall();
			return;
		}
		else
		{
			CheckUp();
			return;
		}
	}
	if (m_move.x != 0.f && m_SideWallCheck)
	{
		if (m_move.x > 0.f)
		{
			CheckMoveRight();
			return;
		}
		else
		{
			CheckMoveLeft();
			return;
		}
	}
}

void CGameObject::Render(HDC hDC,float deltaTime)
{
	Vector2	pos;
	Vector2	cameraPos;
	Vector2	resolution;
	if (m_scene)
	{
		cameraPos = m_scene->GetCamera()->GetPos();
		resolution = m_scene->GetCamera()->GetResolution();
		pos = m_pos - m_scene->GetCamera()->GetPos();
	}
	else
	{
		CScene* scene = CSceneManager::GetInst()->GetScene();
		pos = m_pos - scene->GetCamera()->GetPos();
		cameraPos = scene->GetCamera()->GetPos();
		resolution = scene->GetCamera()->GetResolution();
	}
	if (m_animation)
	{
		CAnimationInfo* current = m_animation->m_currentAnimation;
		const AnimationFrameData& frameData = current->m_sequence->GetFrame(current->m_frame);
		Vector2	size = frameData.end - frameData.start;
		Vector2	renderLT= pos - m_pivot * size;
		Vector2	cullPos = m_pos - m_pivot * size;
		if (cullPos.x > cameraPos.x + resolution.x)
		{
			return;
		}
		else if (cullPos.x + size.x < cameraPos.x)
		{
			return;
		}
		else if (cullPos.y > cameraPos.y + resolution.y)
		{
			return;
		}
		else if (cullPos.y + size.y < cameraPos.y)
		{
			return;
		}
		if (current->m_sequence->GetTextureType() == ETexture_Type::Sprite)
		{
			if (current->m_sequence->GetTexture()->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)renderLT.x, 
									(int)renderLT.y,
									(int)size.x, 
									(int)size.y,current->m_sequence->GetTexture()->GetDC(),
									(int)frameData.start.x, 
									(int)frameData.start.y,
									(int)size.x, 
									(int)size.y,current->m_sequence->GetTexture()->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderLT.x, 
							(int)renderLT.y,
							(int)size.x, 
							(int)size.y,current->m_sequence->GetTexture()->GetDC(),
							(int)frameData.start.x, 
							(int)frameData.start.y, SRCCOPY);
			}
		}
		else
		{
			if (current->m_sequence->GetTexture()->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)renderLT.x,
									(int)renderLT.y,
									(int)size.x,
									(int)size.y, current->m_sequence->GetTexture()->GetDC(current->m_frame),
									(int)frameData.start.x,
									(int)frameData.start.y,
									(int)size.x,
									(int)size.y, current->m_sequence->GetTexture()->GetColorKey());
			}
			else
			{
				BitBlt(hDC, (int)renderLT.x,
							(int)renderLT.y,
							(int)size.x,
							(int)size.y, current->m_sequence->GetTexture()->GetDC(current->m_frame),
							(int)frameData.start.x,
							(int)frameData.start.y, SRCCOPY);
			}
		}
	}
	else
	{
		if (m_texture)
		{
			Vector2	renderLT= pos - m_pivot * m_size;
			Vector2	cullPos = m_pos - m_pivot * m_size;
			if (cullPos.x > cameraPos.x + resolution.x)
			{
				return;
			}
			else if (cullPos.x + m_size.x < cameraPos.x)
			{
				return;
			}
			else if (cullPos.y > cameraPos.y + resolution.y)
			{
				return;
			}
			else if (cullPos.y + m_size.y < cameraPos.y)
			{
				return;
			}
			if (m_texture->GetEnableColorKey())
			{
				if (m_texture->GetTextureType() == ETexture_Type::Sprite)
				{
					TransparentBlt(hDC, (int)renderLT.x, 
										(int)renderLT.y,
										(int)m_size.x, 
										(int)m_size.y, m_texture->GetDC(),0, 0, 
										(int)m_size.x, 
										(int)m_size.y, m_texture->GetColorKey());
				}
				else
				{
				}
			}
			else
			{
				if (m_texture->GetTextureType() == ETexture_Type::Sprite)
				{
					BitBlt(hDC, (int)renderLT.x, 
								(int)renderLT.y,
								(int)m_size.x, 
								(int)m_size.y, m_texture->GetDC(),0, 0, SRCCOPY);
				}
				else
				{
				}
			}
		}
	}
	auto	iter = m_colliderList.begin();
	auto	iterEnd = m_colliderList.end();
	for (; iter != iterEnd;)
	{
		if (!(*iter)->GetActive())
		{
			iter = m_colliderList.erase(iter);
			iterEnd = m_colliderList.end();
			continue;
		}
		else if (!(*iter)->GetEnable())
		{
			++iter;
			continue;
		}
		(*iter)->Render(hDC, deltaTime);
		++iter;
	}
	m_prevPos = m_pos;
}

float CGameObject::InflictDamage(float damage)
{
	return damage;
}

void CGameObject::Save(FILE* file)
{
	CRef::Save(file);
	fwrite(&m_renderLayer, sizeof(ERender_Layer), 1, file);
	fwrite(&m_prevPos, sizeof(Vector2), 1, file);
	fwrite(&m_move, sizeof(Vector2), 1, file);
	fwrite(&m_pos, sizeof(Vector2), 1, file);
	fwrite(&m_size, sizeof(Vector2), 1, file);
	fwrite(&m_pivot, sizeof(Vector2), 1, file);
	bool	texture = false;
	if (m_texture)
	{
		texture = true;
	}
	fwrite(&texture, sizeof(bool), 1, file);
	if (m_texture)
	{
		m_texture->Save(file);
	}
	bool	animation = false;
	if (m_animation)
	{
		animation = true;
	}
	fwrite(&animation, sizeof(bool), 1, file);
	if (m_animation)
	{
		// Animation 저장
	}
	fwrite(&m_timeScale, sizeof(float), 1, file);
	fwrite(&m_moveSpeed, sizeof(float), 1, file);
	fwrite(&m_physicsSimulate, sizeof(bool), 1, file);
	fwrite(&m_ground, sizeof(bool), 1, file);
	fwrite(&m_gravityAccel, sizeof(float), 1, file);
	fwrite(&m_fallTime, sizeof(float), 1, file);
	fwrite(&m_fallStartY, sizeof(float), 1, file);
	fwrite(&m_jumpVelocity, sizeof(float), 1, file);
	fwrite(&m_jump, sizeof(bool), 1, file);
}

void CGameObject::Load(FILE* file)
{
	CRef::Load(file);
	fread(&m_renderLayer, sizeof(ERender_Layer), 1, file);
	fread(&m_prevPos, sizeof(Vector2), 1, file);
	fread(&m_move, sizeof(Vector2), 1, file);
	fread(&m_pos, sizeof(Vector2), 1, file);
	fread(&m_size, sizeof(Vector2), 1, file);
	fread(&m_pivot, sizeof(Vector2), 1, file);
	bool	texture = false;
	fread(&texture, sizeof(bool), 1, file);
	if (texture)
	{
		m_texture = m_scene->GetSceneResource()->LoadTexture(file);
	}
	bool	animation = false;
	fread(&animation, sizeof(bool), 1, file);
	if (animation)
	{
		// Animation 불러오기
	}
	fread(&m_timeScale, sizeof(float), 1, file);
	fread(&m_moveSpeed, sizeof(float), 1, file);
	fread(&m_physicsSimulate, sizeof(bool), 1, file);
	fread(&m_ground, sizeof(bool), 1, file);
	fread(&m_gravityAccel, sizeof(float), 1, file);
	fread(&m_fallTime, sizeof(float), 1, file);
	fread(&m_fallStartY, sizeof(float), 1, file);
	fread(&m_jumpVelocity, sizeof(float), 1, file);
	fread(&m_jump, sizeof(bool), 1, file);
}

void CGameObject::SaveFullPath(const char* fullPath)
{
	FILE* file = nullptr;
	fopen_s(&file, fullPath, "wb");
	if (!file)
	{
		return;
	}
	Save(file);
	fclose(file);
}

void CGameObject::LoadFullPath(const char* fullPath)
{
	FILE* file = nullptr;
	fopen_s(&file, fullPath, "rb");
	if (!file)
	{
		return;
	}
	Load(file);
	fclose(file);
}

void CGameObject::SaveFileName(const char* fileName, const std::string& pathName)
{
	const PathInfo* info = CPathManager::GetInst()->FindPath(pathName);
	char	fullPath[MAX_PATH] = {};
	if (info)
	{
		strcpy_s(fullPath, info->pathMultibyte);
	}
	strcat_s(fullPath, fileName);
	SaveFullPath(fullPath);
}

void CGameObject::LoadFileName(const char* fileName, const std::string& pathName)
{
	const PathInfo* info = CPathManager::GetInst()->FindPath(pathName);
	char	fullPath[MAX_PATH] = {};
	if (info)
	{
		strcpy_s(fullPath, info->pathMultibyte);
	}
	strcat_s(fullPath, fileName);
	LoadFullPath(fullPath);
}

void CGameObject::CheckFall()
{
	CTileMap* tileMap = m_scene->GetTileMap();
	float	prevBottom = m_prevPos.y + (1.f - m_pivot.y) * m_ColliderSize.y+m_OffsetSize.y;
	float	curBottom = m_pos.y + (1.f - m_pivot.y) * m_ColliderSize.y+ m_OffsetSize.y;
	float	prevLeft = m_prevPos.x - m_pivot.x * m_ColliderSize.x+ m_OffsetSize.x;
	float	curLeft = m_pos.x - m_pivot.x * m_ColliderSize.x+ m_OffsetSize.x;
	float	prevRight = m_prevPos.x + (1.f - m_pivot.x) * m_ColliderSize.x+ m_OffsetSize.x;
	float	curRight = m_pos.x + (1.f - m_pivot.x) * m_ColliderSize.x+ m_OffsetSize.x;

	float resultLeft = prevLeft < curLeft ? prevLeft : curLeft;
	float resultRight = prevRight > curRight ? prevRight : curRight;
	float resultTop = prevBottom < curBottom ? prevBottom : curBottom;
	float resultBottom = prevBottom > curBottom ? prevBottom : curBottom;

	int leftIndex = tileMap->GetTileOriginIndexX(resultLeft);
	int rightIndex = tileMap->GetTileOriginIndexX(resultRight);
	int topIndex = tileMap->GetTileOriginIndexY(resultTop);
	int bottomIndex = tileMap->GetTileOriginIndexY(resultBottom);

	leftIndex = leftIndex < 0 ? 0 : leftIndex;
	topIndex = topIndex < 0 ? 0 : topIndex;
	rightIndex = rightIndex > tileMap->GetCountX() - 1 ? tileMap->GetCountX() - 1 : rightIndex;
	bottomIndex = bottomIndex > tileMap->GetCountY() - 1 ? tileMap->GetCountY() - 1 : bottomIndex;
	if (leftIndex <= tileMap->GetCountX() - 1 && topIndex <= tileMap->GetCountY() - 1 && rightIndex >= 0 && bottomIndex >= 0)
	{
		bool	check = false;
		for (int i = topIndex; i <= bottomIndex; ++i)
		{
			for (int j = leftIndex; j <= rightIndex; ++j)
			{
				CTile* tile = tileMap->GetTile(j, i);
				if (!tile)
				{
					continue;
				}
				if (tile->GetPos().y < prevBottom)
				{
					continue;
				}
				if (tile->GetOption() == ETile_Option::ImpossibleToMove)
				{
					check = true;
					m_fallTime = 0.f;
					m_pos.y = tile->GetPos().y - (1.f - m_pivot.y) * m_ColliderSize.y- m_OffsetSize.y;
					m_ground = true;
					m_jump = false;
					break;
				}
			}
			if (check)
			{
				break;
			}
		}
		if (!check)
		{
			if (m_ground)
			{
				m_fallTime = 0.f;
				m_fallStartY = m_pos.y;
			}
			m_ground = false;
		}
	}
}

void CGameObject::CheckUp()
{
	CTileMap* tileMap = m_scene->GetTileMap();
	float	prevTop = m_prevPos.y - m_pivot.y * m_ColliderSize.y + m_OffsetSize.y;
	float	curTop = m_pos.y - m_pivot.y * m_ColliderSize.y + m_OffsetSize.y;
	float	prevLeft = m_prevPos.x - m_pivot.x * m_ColliderSize.x + m_OffsetSize.x;
	float	curLeft = m_pos.x - m_pivot.x * m_ColliderSize.x + m_OffsetSize.x +2.f;
	float	prevRight = m_prevPos.x + (1.f - m_pivot.x) * m_ColliderSize.x + m_OffsetSize.x;
	float	curRight = m_pos.x + (1.f - m_pivot.x) * m_ColliderSize.x + m_OffsetSize.x -2.f;

	float resultLeft = prevLeft < curLeft ? prevLeft : curLeft;	
	float resultRight = prevRight > curRight ? prevRight : curRight;
	float resultTop = prevTop > curTop ? prevTop : curTop;
	float resultBottom = prevTop < curTop ? prevTop : curTop;

	int leftIndex = tileMap->GetTileOriginIndexX(resultLeft);
	int rightIndex = tileMap->GetTileOriginIndexX(resultRight);
	int topIndex = tileMap->GetTileOriginIndexY(resultTop);
	int bottomIndex = tileMap->GetTileOriginIndexY(resultBottom);

	leftIndex = leftIndex < 0 ? 0 : leftIndex;
	topIndex = topIndex < 0 ? 0 : topIndex;
	rightIndex = rightIndex > tileMap->GetCountX() - 1 ? tileMap->GetCountX() - 1 : rightIndex;
	bottomIndex = bottomIndex > tileMap->GetCountY() - 1 ? tileMap->GetCountY() - 1 : bottomIndex;
	if (leftIndex <= tileMap->GetCountX() - 1 && topIndex <= tileMap->GetCountY() - 1 && rightIndex >= 0 && bottomIndex >= 0)
	{
		for (int i = bottomIndex; i >= topIndex; --i)
		{
			for (int j = leftIndex; j <= rightIndex; ++j)
			{
				CTile* tile = tileMap->GetTile(j, i);
				if (!tile)
				{
					continue;
				}
				if (tile->GetPos().y > prevTop)				
				{
					continue;
				}
				if (tile->GetOption() == ETile_Option::ImpossibleToMove)
				{
					m_pos.y = tile->GetPos().y + tile->GetSize().y + m_pivot.y * m_ColliderSize.y - m_OffsetSize.y-0.001f;
					break;
				}
			}
		}
	}
}

void CGameObject::CheckMoveRight()
{
	Vector2	LT = m_pos - m_pivot * m_ColliderSize+ m_OffsetSize;
	Vector2	RB = LT + m_ColliderSize;
	Vector2	prevLT = m_prevPos - m_pivot * m_ColliderSize+ m_OffsetSize;
	Vector2	prevRB = prevLT + m_ColliderSize;
	CTileMap* tileMap = m_scene->GetTileMap();
	if(!tileMap)
	{
		return;
	}
	Vector2	resultLT;
	Vector2 resultRB = RB;
	resultLT.x = prevRB.x;
	resultLT.y = LT.y < prevLT.y ? LT.y : prevLT.y;
	resultRB.y = RB.y > prevRB.y ? RB.y : prevRB.y;

	int leftIndex = tileMap->GetTileOriginIndexX(resultLT.x);
	int topIndex = tileMap->GetTileOriginIndexY(resultLT.y + 0.001f);
	int rightIndex = tileMap->GetTileOriginIndexX(resultRB.x);
	int bottomIndex = tileMap->GetTileOriginIndexY(resultRB.y + 0.001f);

	leftIndex = leftIndex < 0 ? 0 : leftIndex;
	topIndex = topIndex < 0 ? 0 : topIndex;
	rightIndex = rightIndex > tileMap->GetCountX() - 1 ? tileMap->GetCountX() - 1 : rightIndex;
	bottomIndex = bottomIndex > tileMap->GetCountY() - 1 ? tileMap->GetCountY() - 1 : bottomIndex;
	if (leftIndex <= tileMap->GetCountX() - 1 && topIndex <= tileMap->GetCountY() - 1 &&rightIndex >= 0 && bottomIndex >= 0)
	{
		bool	sideCollision = false;
		for (int i = topIndex; i <= bottomIndex; ++i)
		{
			for (int j = leftIndex; j <= rightIndex; ++j)
			{
				CTile* tile = tileMap->GetTile(j, i);
				if (tile->GetOption() != ETile_Option::ImpossibleToMove || !tile->GetSideCollision())
				{
					continue;
				}
				Vector2	tilePos = tile->GetPos();
				Vector2	tileSize = tile->GetSize();
				if (tilePos.y - 0.001f <= RB.y && RB.y <= tilePos.y + 0.001f)
				{
					continue;
				}
				if (LT.x <= tilePos.x + tileSize.x && LT.y <= tilePos.y + tileSize.y && RB.x >= tilePos.x && RB.y >= tilePos.y)
				{
					sideCollision = true;
					float moveX = tilePos.x - RB.x - 0.001f;
					m_pos.x += moveX;
					m_move.x += moveX;
					break;
				}
			}
			if (sideCollision)
			{
				break;
			}
		}
	}
}

void CGameObject::CheckMoveLeft()
{
	Vector2	LT = m_pos - m_pivot * m_ColliderSize+ m_OffsetSize;
	Vector2	RB = LT + m_ColliderSize;
	Vector2	prevLT = m_prevPos - m_pivot * m_ColliderSize+ m_OffsetSize;
	Vector2	prevRB = prevLT + m_ColliderSize;
	CTileMap* tileMap = m_scene->GetTileMap();
	if (!tileMap)
	{
		return;
	}
	Vector2	resultLT = LT;
	Vector2 resultRB;
	resultLT.y = LT.y < prevLT.y ? LT.y : prevLT.y;
	resultRB.x = prevLT.x;
	resultRB.y = RB.y > prevRB.y ? RB.y : prevRB.y;

	int leftIndex = tileMap->GetTileOriginIndexX(resultLT.x);
	int topIndex = tileMap->GetTileOriginIndexY(resultLT.y + 0.001f);
	int rightIndex = tileMap->GetTileOriginIndexX(resultRB.x);
	int bottomIndex = tileMap->GetTileOriginIndexY(resultRB.y + 0.001f);

	leftIndex = leftIndex < 0 ? 0 : leftIndex;
	topIndex = topIndex < 0 ? 0 : topIndex;
	rightIndex = rightIndex > tileMap->GetCountX() - 1 ? tileMap->GetCountX() - 1 : rightIndex;
	bottomIndex = bottomIndex > tileMap->GetCountY() - 1 ? tileMap->GetCountY() - 1 : bottomIndex;

	if (leftIndex <= tileMap->GetCountX() - 1 && topIndex <= tileMap->GetCountY() - 1 &&rightIndex >= 0 && bottomIndex >= 0)
	{
		bool	sideCollision = false;
		for (int i = topIndex; i <= bottomIndex; ++i)
		{
			for (int j = rightIndex; j >= leftIndex; --j)
			{
				CTile* tile = tileMap->GetTile(j, i);
				if (tile->GetOption() != ETile_Option::ImpossibleToMove || !tile->GetSideCollision())
				{
					continue;
				}
				Vector2	tilePos = tile->GetPos();
				Vector2	tileSize = tile->GetSize();
				if (tilePos.y - 0.001f <= RB.y && RB.y <= tilePos.y + 0.001f)
				{
					continue;
				}
				if (LT.x <= tilePos.x + tileSize.x && LT.y <= tilePos.y + tileSize.y && RB.x >= tilePos.x && RB.y >= tilePos.y)
				{
					sideCollision = true;
					float moveX = tilePos.x + tileSize.x - LT.x + 0.001f;
					m_pos.x += moveX;
					m_move.x += moveX;
					break;
				}
			}
			if (sideCollision)
			{
				break;
			}
		}
	}
}

void CGameObject::Slippery()
{
	CTileMap* tileMap = m_scene->GetTileMap();
	int indexX = tileMap->GetTileIndexX(m_pos.x);
	int indexY = tileMap->GetTileIndexY(m_pos.y);
	indexX = indexX < 1 ? 1 : indexX;
	indexY = indexY < 1 ? 1 : indexY;
	indexX = indexX > tileMap->GetCountX() - 2 ? tileMap->GetCountX() - 2 : indexX;
	indexY = indexY > tileMap->GetCountY() - 2 ? tileMap->GetCountY() - 2 : indexY;
	if (tileMap->GetTile(indexX, indexY)->GetOption() == ETile_Option::Slippery)
	{
		m_jumpVelocity -= 50.f*DELTA_TIME;
		float velocity = m_jumpVelocity * DELTA_TIME;
		if(m_jumpVelocity<0)
		{
			m_jumpVelocity = 0;
		}
		if (abs(m_move.x) > abs(m_move.y))
		{
			if (m_move.x > 0.f)
			{
				m_pos.x += velocity;
			}
			else
			{
				m_pos.x -= velocity;
			}
		}
		else
		{
			if (m_move.y > 0.f)
			{
				m_pos.y += velocity;
			}
			else
			{
				m_pos.y -= velocity;
			}
		}
	}
}

#ifdef UNICODE
void CGameObject::SetTexture(const std::string& name, const std::vector<std::wstring>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
	SetSize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
}

void CGameObject::SetTextureFullPath(const std::string& name, const std::vector<std::wstring>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
	SetSize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
}
#else
void CGameObject::SetTexture(const std::string& name,const std::vector<std::string>& vecFileName, const std::string& pathName)
{
	m_scene->GetSceneResource()->LoadTexture(name, vecFileName, pathName);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
	SetSize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
}

void CGameObject::SetTextureFullPath(const std::string& name,const std::vector<std::string>& vecFullPath)
{
	m_scene->GetSceneResource()->LoadTextureFullPath(name, vecFullPath);
	m_texture = m_scene->GetSceneResource()->FindTexture(name);
	SetSize((float)m_texture->GetWidth(), (float)m_texture->GetHeight());
}
#endif