#pragma once
#include "Obj.h"
class CMonster1 :
	public CObj
{
//public:
//	enum STATEID {
//		IDLE = 1, ATTACK, DAMAGED, RUN, DIE, STATE_END
//	};

public:
	CMonster1();
	virtual ~CMonster1();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

//private:
//	template <typename T>
//	CObj* CreateAttackCollider()
//	{
//		return CAbstractFactory<T>::CreateObj(D3DXVECTOR3(m_tInfo.vPos.x - 150.f, m_tInfo.vPos.y - 50.f, 0.f));
//	}

private:
	float AttackTerm();
	float RestTerm();

	HRESULT MonsterState(STATEID eID);

	void BehaviorFunction();

public:
	void OnLine();

private:
	float m_fSpeed;
	float m_fAngle;

	wstring m_wstrStateKey;

	CObj* m_pTarget;

	CObj* pHpBar;

private:		//	시간
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime1;
	LARGE_INTEGER	m_OldTime2;
	LARGE_INTEGER	m_CpuTick;	// Cpu 진동수(클럭 수)

	float			m_fTime;
	float			m_fRestTime;

	bool			m_bIsCheck;

	bool			m_bIsJump;

	STATEID			m_eStateID;
};

