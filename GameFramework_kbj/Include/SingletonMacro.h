#pragma once

#define	DECLARE_SINGLE(Type)	\
private:\
	static Type*	m_Inst;\
	Type();\
	~Type();\
public:\
	static Type* GetInst()\
	{\
		if (!m_Inst)\
			m_Inst = new Type;\
		return m_Inst;\
	}\
	static void DestroyInst()\
	{\
		if(m_Inst)\
		{\
			delete m_Inst;\
			m_Inst = nullptr;\
		}\
	}

#define	DEFINITION_SINGLE(Type)	Type* Type::m_Inst = nullptr;
