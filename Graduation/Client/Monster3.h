#pragma once
#include "Obj.h"
class CMonster3 :
	public CObj
{
public:
	CMonster3();
	virtual ~CMonster3();
	
public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float m_fSpeed;
	float m_fAngle;

	wstring m_wstrStateKey;

	CObj*	m_pTarget;
};

