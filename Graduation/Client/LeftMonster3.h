#pragma once
#include "Obj.h"
class CLeftMonster3 :
	public CObj
{
public:
	CLeftMonster3();
	virtual ~CLeftMonster3();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float m_fSpeed;
	float m_fAngle;

	wstring m_wstrStateKey;

	CObj* m_pTarget;
};

