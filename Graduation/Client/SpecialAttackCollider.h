#pragma once
#include "Obj.h"
class CSpecialAttackCollider :
	public CObj
{
public:
	CSpecialAttackCollider();
	virtual ~CSpecialAttackCollider();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

