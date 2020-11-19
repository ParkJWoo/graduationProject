#pragma once
#include "Obj.h"
class CBossAttackCollider :
	public CObj
{
public:
	CBossAttackCollider();
	virtual ~CBossAttackCollider();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* m_pBoss;
};

