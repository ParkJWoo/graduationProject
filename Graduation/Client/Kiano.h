#pragma once
#include "Obj.h"
class CKiano :
	public CObj
{
public:
	CKiano();
	virtual ~CKiano();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	const D3DXMATRIX& GetMatrix() const { return m_tInfo.matWorld; }

private:
	template <typename T>
	CObj* CreateAttackCollider()
	{
		return CAbstractFactory<T>::CreateObj(D3DXVECTOR3(m_tInfo.vPos.x - 100.f, m_tInfo.vPos.y, 0.f));
	}

private:
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime1;
	LARGE_INTEGER	m_OldTime2;
	LARGE_INTEGER	m_CpuTick;	// Cpu 진동수(클럭 수)

	float			m_fTime;
	float			m_fRestTime;

	float m_fSpeed;
	float m_fAngle;

	wstring m_wstrStateKey;

	CObj* m_pTarget;

	DATA m_tKianoData;

	CObj* pHpCase;
	CObj* pHpBar;
};

