#ifndef REFERENCEPTR_HPP
#define REFERENCEPTR_HPP

/** 
 * @brief 简单智能指针
 * @usage 简化代码，尤其在函数多种异常退出情况，且存在需要释放的资源。
 */
template<class T>
class SimplePtr
{
public:
	SimplePtr( ):m_ptr(0) { }
	SimplePtr( T* ptr ):m_ptr(ptr) { }
	~SimplePtr(){ reset(); }
	SimplePtr& swap( SimplePtr& othr ){ T* tmp = m_ptr;m_ptr = othr.m_ptr;othr.m_ptr=tmp; }

	// 让此类使用起来无异于指针

	SimplePtr& operator=(T* ptr){ reset(); m_ptr = ptr; return *this; }
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	operator T*( ){ return m_ptr; }

	// 安全地获取指针
	T* get() const { return m_ptr; }

	//指针运算
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
 * @brief 智能指针。
 * @note  T类限制：必须是CReferenceObject的子类
 * @usage  生命周期持续到程序结束或生命周期不可预测，如：共享的位图、画笔等GDI资源。
 */
template<class T>
class RefPtr
{
public:
	typedef T element_type;

	//构造
	inline RefPtr() : m_ptr(0) {}
	inline RefPtr(T* ptr) : m_ptr(ptr) { if (m_ptr) m_ptr->ref(); }
	inline RefPtr(const RefPtr& rp) : m_ptr(rp.m_ptr) { if (m_ptr) m_ptr->ref(); }

	//析构
	inline ~RefPtr() 
	{ 
		if (m_ptr) m_ptr->unref();  m_ptr = 0; 
	}

	//赋值
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
		
		//新指针
		if (m_ptr)
		{
			m_ptr->ref();
		}
		//旧指针
		if (tmp_ptr)
		{
			tmp_ptr->unref();
		}
		return *this;
	}

	// 隐式类型转换
	inline operator T*() const { return m_ptr; }
	// 比较
	inline bool operator == (const RefPtr& rp) const { return (m_ptr==rp.m_ptr); }
	inline bool operator == (const T* ptr) const { return (m_ptr==ptr); }
	friend bool operator == (const T* ptr, const RefPtr& rp) { return (ptr==rp.m_ptr); }

	bool operator != (const RefPtr& rp) const { return (m_ptr!=rp.m_ptr); }
	bool operator != (const T* ptr) const { return (m_ptr!=ptr); }
	friend bool operator != (const T* ptr, const RefPtr& rp) { return (ptr!=rp.m_ptr); }

	//一般不用的比较
	bool operator < (const RefPtr& rp) const { return (m_ptr<rp.m_ptr); }

private:
	typedef T* RefPtr::*unspecified_bool_type;

public:
	// 转换为bool值
	operator unspecified_bool_type() const { return valid()? &RefPtr::m_ptr : 0; }

	// 让此类使用起来无异于指针
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }

	// 安全地获取指针
	T* get() const { return m_ptr; }

	//指针运算
	bool operator!() const   { return m_ptr==0; }
	bool valid() const       { return m_ptr!=0; }

	//释放当前存储的指针，不删除
	T* release() { T* tmp=m_ptr; if (m_ptr) m_ptr->unref_nodelete(); m_ptr=0; return tmp; }

	//交换2个对象存储的指针
	void swap(RefPtr& rp) { T* tmp=m_ptr; m_ptr=rp.m_ptr; rp.m_ptr=tmp; }

private:

	//赋值操作
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
