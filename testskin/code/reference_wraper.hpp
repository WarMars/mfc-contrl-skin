#ifndef REFERENCEWRAPER_HPP
#define REFERENCEWRAPER_HPP


/** 
 * @brief 引用对象资源包装类。
 *    系统的资源存在多处复用的情况，
 *    此类与智能指针结合，能避免资源重复申请。
 */
class CReferenceObject
{
public:
	inline int refCount( ) const { return m_nRefCount; }
protected:
	inline CReferenceObject( ):m_nRefCount(0) { }
	inline void ref( ){ ++m_nRefCount; }
	inline void unref( ) { unref_nodelete(); if(0==m_nRefCount){delete this;} }
	inline void unref_nodelete( ) { --m_nRefCount; }
protected:
	virtual ~CReferenceObject(){ }
private:
	CReferenceObject( const CReferenceObject& ){ }
private:
	int	m_nRefCount;
};

/** 
 * @brief 自定义类和指针指针衔接类。此类的支持智能指针
 * @usage 举例
 *	RefPtr<CClassReference<CBitmap> > bmpPtr;
 *  bmpPtr = new CClassReference<CBitmap>( );
 *  //....
 *  //程序结束时CBitmap对象自动释放
 */

template<typename T>
class CClassReference: public T,public CReferenceObject
{
	typedef CClassReference<T> ReferenceClassType;
	friend class RefPtr<ReferenceClassType>;
	friend class CImageManager;
public:
	inline CClassReference( ){}
	inline CClassReference( T*& pT )
	{
		if( NULL == T )
		{
			return;
		}
		unsigned char szBuf[sizeof(T)];
		memcpy( szBuf, this, sizeof(T) );
		memcpy( this, pT, sizeof(T) );
		memcpy( pT, szBuf, sizeof(T) );
		delete pT;
		pT = NULL;
	}
protected:
	~CClassReference(){ }
};

#endif //REFERENCEWRAPER_HPP

