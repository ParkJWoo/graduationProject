#pragma once
#include "Obj.h"
class CSpecialAttackCollider :
	public CObj
{
public:
	CSpecialAttackCollider();
	virtual ~CSpecialAttackCollider();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

