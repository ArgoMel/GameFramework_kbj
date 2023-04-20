#pragma once
#include "GameInfo.h"

class CRef
{
protected:
	int m_refCount;
	std::string m_name;
	std::string m_typeName;
	size_t m_typeID;
	bool m_enable;				//==활성화 여부
	bool m_active;				//==삭제할지 여부
public:
	CRef();
	CRef(const CRef& ref);
	virtual ~CRef();
	void AddRef();
	int Release();
	int GetRefCount()	const
	{
		return m_refCount;
	}
	const std::string& GetName()	const
	{
		return m_name;
	}
	const std::string& GetTypeName()	const
	{
		return m_typeName;
	}
	size_t GetTypeID()	const
	{
		return m_typeID;
	}
	bool GetEnable() const
	{
		return m_enable;
	}
	bool GetActive() const
	{
		return m_active;
	}
	void SetName(const std::string& name)
	{
		m_name = name;
	}
	template <typename T>
	void SetTypeID()
	{
		m_typeName = typeid(T).name();		// 타입 이름을 문자열로 얻어온다.
		m_typeID = typeid(T).hash_code();		// 타입의 고유한 번호를 얻어온다.
	}
	void SetEnable(bool enable)
	{
		m_enable = enable;
	}
	void SetActive(bool active)
	{
		m_active = active;
	}
	template <typename T>
	bool CheckTypeID()	const
	{
		return m_typeID == typeid(T).hash_code();
	}
	virtual void Save(FILE* file);
	virtual void Load(FILE* file);
};

