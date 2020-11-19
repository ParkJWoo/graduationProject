#pragma once
#include "Obj.h"
class CMonster2 :
	public CObj
{
public:
	CMonster2();
	virtual ~CMonster2();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	template <typename T>
	CObj* CreateBullet()
	{
		return CAbstractFactory<T>::CreateObj(D3DXVECTOR3(m_tInfo.vPos.x - 100.f, m_tInfo.vPos.y - 90.f, 0.f));
	}

private:
	float ShootingTerm();
	float RestTerm();

private:
	float m_fSpeed;
	float m_fAngle;

	wstring m_wstrStateKey;

	CObj*	m_pTarget;

private:		//	시간
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime1;
	LARGE_INTEGER	m_OldTime2;
	LARGE_INTEGER	m_CpuTick;	// Cpu 진동수(클럭 수)

	float			m_fTime;
	float			m_fRestTime;
	
	int iShootCnt;
};

