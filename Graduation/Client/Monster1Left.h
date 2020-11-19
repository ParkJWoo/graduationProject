#pragma once
#include "Obj.h"
class CMonster1Left :
	public CObj
{
public:
	CMonster1Left();
	virtual ~CMonster1Left();

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

	CObj* m_pTarget;
};

