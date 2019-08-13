#ifndef REFERENCEWRAPER_HPP
#define REFERENCEWRAPER_HPP


/** 
 * @brief ���ö�����Դ��װ�ࡣ
 *    ϵͳ����Դ���ڶദ���õ������
 *    ����������ָ���ϣ��ܱ�����Դ�ظ����롣
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
 * @brief �Զ������ָ��ָ���ν��ࡣ�����֧������ָ��
 * @usage ����
 *	RefPtr<CClassReference<CBitmap> > bmpPtr;
 *  bmpPtr = new CClassReference<CBitmap>( );
 *  //....
 *  //�������ʱCBitmap�����Զ��ͷ�
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

