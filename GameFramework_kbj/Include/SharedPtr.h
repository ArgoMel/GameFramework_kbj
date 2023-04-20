#pragma once
template <typename T>
class CSharedPtr
{
private:
	T* m_ptr;
public:
	CSharedPtr()
		:m_ptr(nullptr)
	{}
	CSharedPtr(const CSharedPtr<T>& ptr)
	{
		m_ptr = ptr.m_ptr;
		if(m_ptr)
		{
			m_ptr->AddRef();
		}
	}
	CSharedPtr(T* ptr)
	{
		m_ptr = ptr;
		if (m_ptr)
		{
			m_ptr->AddRef();
		}
	}
	~CSharedPtr()
	{
		if(m_ptr)
		{
			m_ptr->Release();
		}
	}
	void operator = (const CSharedPtr<T>& ptr)
	{
		if (m_ptr)
		{
			m_ptr->Release();
		}
		m_ptr = ptr.m_ptr;
		if (m_ptr) 
		{
			m_ptr->AddRef();
		}	
	}
	void operator = (T* ptr)
	{
		if (m_ptr)
		{
			m_ptr->Release();
		}
		m_ptr = ptr;
		if (m_ptr)
		{
			m_ptr->AddRef();
		}
	}
	bool operator == (const CSharedPtr<T>& ptr)	const
	{
		return m_ptr == ptr.m_ptr;
	}
	bool operator == (T* ptr)	const
	{
		return m_ptr == ptr;
	}
	bool operator != (const CSharedPtr<T>& ptr)	const
	{
		return m_ptr != ptr.m_ptr;
	}
	bool operator != (T* ptr)	const
	{
		return m_ptr != ptr;
	}
	operator T* ()	const
	{
		return m_ptr;
	}
	T* operator -> ()	const
	{
		return m_ptr;
	}
	T* operator * ()	const
	{
		return m_ptr;
	}
	T* Get()	const
	{
		return m_ptr;
	}
};