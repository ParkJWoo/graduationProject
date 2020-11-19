#pragma once
#include "Obj.h"
class CRightAttackEffect :
	public CObj
{
public:
	CRightAttackEffect();
	virtual ~CRightAttackEffect();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* m_pPlayer;

	float m_fTime;

	wstring m_wstrStateKey;
};

