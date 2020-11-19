#pragma once

class CObj;

template <typename T>
class CAbstractFactory
{
public:
	static HRESULT CreateObj(CObj*& pObject)
	{
		pObject = new T;

		if (FAILED(pObject->Initialize()))
		{
			SafeDelete(pObject);
			return E_FAIL;
		}

		return S_OK;
	}

	static HRESULT CreateObj(CObj*& pObject, D3DXVECTOR3& vPos)
	{
		pObject = new T;

		if (FAILED(pObject->Initialize()))
		{
			SafeDelete(pObject);
			return E_FAIL;
		}

		pObject->SetPos(vPos);

		return S_OK;
	}

	static CObj* CreateObj(D3DXVECTOR3& vPos)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos);

		return pObj;
	}

	static CObj* CreateObj(CObj*& pObject, D3DXVECTOR3& vPos, int& iDrawID)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(vPos);
		pObj->SetDrawID(iDrawID);

		return pObj;
	}
};

template <typename T1, typename T2>
class CEffectFactory
{
public:
	static CObj* CreateEffect(D3DXVECTOR3& vPos, const TCHAR* szStateKey, const FRAME& tFrame)
	{
		T2* pAnim = new T2;	// ±¸ÇöÃþ
		pAnim->SetStateKey(szStateKey);
		pAnim->SetFrame(tFrame);

		CObj* pEffect = nullptr; // Ãß»óÃþ
		CAbstractFactory<T1>::CreateObj(pEffect, vPos);
		dynamic_cast<T1*>(pEffect)->SetBridge(pAnim);

		return pEffect;
	}

	static CObj* CreateEffect(D3DXVECTOR3& vPos, const TCHAR* szStateKey, float fTime)
	{
		T2* pNonAnim = new T2;
		pNonAnim->SetStateKey(szStateKey);
		pNonAnim->SetTime(fTime);

		CObj* pEffect = nullptr;
		CAbstractFactory<T1>::CreateObj(pEffect, vPos);
		dynamic_cast<T1*>(pEffect)->SetBridge(pNonAnim);

		return pEffect;
	}

	static CObj* CreateEffect(const TCHAR* szStateKey, const FRAME& tFrame)
	{
		T2* pAnim = new T2;	// ±¸ÇöÃþ
		pAnim->SetStateKey(szStateKey);
		pAnim->SetFrame(tFrame);

		CObj* pEffect = nullptr; // Ãß»óÃþ
		CAbstractFactory<T1>::CreateObj(pEffect);
		dynamic_cast<T1*>(pEffect)->SetBridge(pAnim);

		return pEffect;
	}

	static CObj* CreateEffect(const TCHAR* szStateKey, float fTime)
	{
		T2* pNonAnim = new T2;
		pNonAnim->SetStateKey(szStateKey);
		pNonAnim->SetTime(fTime);

		CObj* pEffect = nullptr;
		CAbstractFactory<T1>::CreateObj(pEffect);
		dynamic_cast<T1*>(pEffect)->SetBridge(pNonAnim);

		return pEffect;
	}
};