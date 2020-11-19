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
	// CObj��(��) ���� ��ӵ�
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

private:		//	�ð�
	LARGE_INTEGER	m_CurTime;
	LARGE_INTEGER	m_OldTime1;
	LARGE_INTEGER	m_OldTime2;
	LARGE_INTEGER	m_CpuTick;	// Cpu ������(Ŭ�� ��)

	float			m_fTime;
	float			m_fRestTime;

	bool			m_bIsCheck;

	bool			m_bIsJump;

	STATEID			m_eStateID;
};

