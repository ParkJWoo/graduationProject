#pragma once
#include "Obj.h"
class CAttackCollider :
	public CObj
{
public:
	CAttackCollider();
	virtual ~CAttackCollider();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* m_pPlayer;

	D3DXVECTOR3 m_vPoint[4];

	HDC m_hDC;
};

