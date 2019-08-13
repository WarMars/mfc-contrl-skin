#ifndef REFERENCEPTR_HPP
#define REFERENCEPTR_HPP

/** 
 * @brief ������ָ��
 * @usage �򻯴��룬�����ں��������쳣�˳�������Ҵ�����Ҫ�ͷŵ���Դ��
 */
template<class T>
class SimplePtr
{
public:
	SimplePtr( ):m_ptr(0) { }
	SimplePtr( T* ptr ):m_ptr(ptr) { }
	~SimplePtr(){ reset(); }
	SimplePtr& swap( SimplePtr& othr ){ T* tmp = m_ptr;m_ptr = othr.m_ptr;othr.m_ptr=tmp; }

	// �ô���ʹ������������ָ��

	SimplePtr& operator=(T* ptr){ reset(); m_ptr = ptr; return *this; }
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	operator T*( ){ return m_ptr; }

	// ��ȫ�ػ�ȡָ��
	T* get() const { return m_ptr; }

	//ָ������
	bool operator!() const   { return m_ptr==0; }
	bool valid() const       { return m_ptr!=0; }
	T* release( ){T* temp = m_ptr; m_ptr = NULL;return temp;}
	void reset( ){ if(NULL!=m_ptr){ delete m_ptr; m_ptr = NULL;} }
private:
	SimplePtr( const SimplePtr& ){}
	SimplePtr& operator=(const SimplePtr&){}

	T* m_ptr;
};

/** 
 * @brief ����ָ�롣
 * @note  T�����ƣ�������CReferenceObject������
 * @usage  �������ڳ���������������������ڲ���Ԥ�⣬�磺�����λͼ�����ʵ�GDI��Դ��
 */
template<class T>
class RefPtr
{
public:
	typedef T element_type;

	//����
	inline RefPtr() : m_ptr(0) {}
	inline RefPtr(T* ptr) : m_ptr(ptr) { if (m_ptr) m_ptr->ref(); }
	inline RefPtr(const RefPtr& rp) : m_ptr(rp.m_ptr) { if (m_ptr) m_ptr->ref(); }

	//����
	inline ~RefPtr() 
	{ 
		if (m_ptr) m_ptr->unref();  m_ptr = 0; 
	}

	//��ֵ
	inline RefPtr& operator = (const RefPtr& rp)
	{
		assign(rp);
		return *this;
	}

	template<class Other> 
	RefPtr& operator = (const RefPtr<Other>& rp)
	{
		assign(rp);
		return *this;
	}

	inline RefPtr& operator = (T* ptr)
	{
		if (m_ptr==ptr)
		{
			return *this;
		}
		T* tmp_ptr = m_ptr;
		m_ptr = ptr;
		
		//��ָ��
		if (m_ptr)
		{
			m_ptr->ref();
		}
		//��ָ��
		if (tmp_ptr)
		{
			tmp_ptr->unref();
		}
		return *this;
	}

	// ��ʽ����ת��
	inline operator T*() const { return m_ptr; }
	// �Ƚ�
	inline bool operator == (const RefPtr& rp) const { return (m_ptr==rp.m_ptr); }
	inline bool operator == (const T* ptr) const { return (m_ptr==ptr); }
	friend bool operator == (const T* ptr, const RefPtr& rp) { return (ptr==rp.m_ptr); }

	bool operator != (const RefPtr& rp) const { return (m_ptr!=rp.m_ptr); }
	bool operator != (const T* ptr) const { return (m_ptr!=ptr); }
	friend bool operator != (const T* ptr, const RefPtr& rp) { return (ptr!=rp.m_ptr); }

	//һ�㲻�õıȽ�
	bool operator < (const RefPtr& rp) const { return (m_ptr<rp.m_ptr); }

private:
	typedef T* RefPtr::*unspecified_bool_type;

public:
	// ת��Ϊboolֵ
	operator unspecified_bool_type() const { return valid()? &RefPtr::m_ptr : 0; }

	// �ô���ʹ������������ָ��
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }

	// ��ȫ�ػ�ȡָ��
	T* get() const { return m_ptr; }

	//ָ������
	bool operator!() const   { return m_ptr==0; }
	bool valid() const       { return m_ptr!=0; }

	//�ͷŵ�ǰ�洢��ָ�룬��ɾ��
	T* release() { T* tmp=m_ptr; if (m_ptr) m_ptr->unref_nodelete(); m_ptr=0; return tmp; }

	//����2������洢��ָ��
	void swap(RefPtr& rp) { T* tmp=m_ptr; m_ptr=rp.m_ptr; rp.m_ptr=tmp; }

private:

	//��ֵ����
	template<class Other> void assign(const RefPtr<Other>& rp)
	{
		if (m_ptr==rp.m_ptr)
		{
			return;
		}
		T* tmp_ptr = m_ptr;
		m_ptr = rp.m_ptr;
		if (m_ptr)
		{
			m_ptr->ref();
		}
		if (tmp_ptr)
		{
			tmp_ptr->unref();
		}
	}

	template<class Other> friend class RefPtr;

	T* m_ptr;
};

#include "reference_wraper.hpp"

#define DECLARE_REF_PTR(classType) \
	typedef CClassReference<classType> C##classType##Ref;\
	typedef RefPtr<C##classType##Ref> C##classType##RefPtr

#define DECLARE_REF_PTR_NC(classType) \
	typedef CClassReference<classType> classType##Ref;\
	typedef RefPtr<classType##Ref> classType##RefPtr

#define DECLARE_LOCAL_PTR( classType) \
	typedef SimplePtr<classType>	CLocal##classType##Ptr
#endif //REFERENCEPTR_HPP
