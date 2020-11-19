#pragma once
#include "Obj.h"
class CEnemy :
	public CObj
{
public:
	CEnemy();
	virtual ~CEnemy();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float	m_fSpeed;
	float	m_fAngle;

	wstring m_wstrStateKey;

	CObj*	m_pTarget;
};