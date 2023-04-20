#include "Ref.h"

CRef::CRef()
	:m_refCount(0)
	,m_typeID(0)
	,m_enable(true)
	,m_active(true)
{
}

CRef::CRef(const CRef& ref)
	: m_refCount(0)
	, m_typeName(ref.m_typeName)
	, m_typeID(ref.m_typeID)
	, m_enable(ref.m_enable)
	, m_active(ref.m_active)
{
}

CRef::~CRef()
{
}

void CRef::AddRef()
{
	++m_refCount;
}

int CRef::Release()
{
	--m_refCount;
	if(m_refCount<=0)
	{
		delete this;
		return 0;
	}
	return m_refCount;
}

void CRef::Save(FILE* file)
{
	size_t	length = m_name.length();
	fwrite(&length, sizeof(int), 1, file);
	fwrite(m_name.c_str(), sizeof(char), length, file);
	length = m_typeName.length();
	fwrite(&length, sizeof(int), 1, file);
	fwrite(m_typeName.c_str(), sizeof(char), length, file);
	fwrite(&m_typeID, sizeof(size_t), 1, file);
}

void CRef::Load(FILE* file)
{
	int	length = 0;
	char	text[256] = {};
	fread(&length, sizeof(int), 1, file);
	assert(length > sizeof(char));
	fread(text, sizeof(char), length, file);
	m_name = text;
	memset(text, 0, 256);
	fread(&length, sizeof(int), 1, file);
	assert(length > sizeof(char));
	fread(text, sizeof(char), length, file);
	m_typeName = text;
	fread(&m_typeID, sizeof(size_t), 1, file);
}
