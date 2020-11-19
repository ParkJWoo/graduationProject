#pragma once
#include "Obj.h"
class CInventory;

class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	const D3DXMATRIX& GetMatrix() const { return m_tInfo.matWorld; }

public:
	void IsJumping();

private:
	void KeyCheck();

	template <typename T>
	CObj* CreateAttackCollider()
	{
		return CAbstractFactory<T>::CreateObj(D3DXVECTOR3(m_tInfo.vPos.x + 100.f, m_tInfo.vPos.y, 0.f));
	}

	template <typename T>
	CObj* CreateLeftAttackCollider()
	{
		return CAbstractFactory<T>::CreateObj(D3DXVECTOR3(m_tInfo.vPos.x - 100.f, m_tInfo.vPos.y, 0.f));
	}

	template <typename T>
	CObj* CreateSpecialAttack()
	{
		return CAbstractFactory<T>::CreateObj(D3DXVECTOR3(m_tInfo.vPos.x - 100.f, m_tInfo.vPos.y, 0.f));
	}

	template <typename T>
	CObj* CreateLeftAttackEffect()
	{
		return CAbstractFactory<T>::CreateObj(D3DXVECTOR3(m_tInfo.vPos.x + 100.f, m_tInfo.vPos.y, 0.f));
	}

private:
	//wstring	m_wstrStateKey;

	float	m_fSpeed;

	float	m_fJupPow;	// 점프 힘(v)
	float	m_fJupAcc;	// 점프 가속도(t)

	bool	m_bIsJump;

	bool	m_bIsDamage;
private:
	CObj* pHpCase;
	CObj* pHpBar;

	CObj* pMpBar;
	CObj* pMpBar2;
	CObj* pMpCase;

	CInventory* pInven;
};