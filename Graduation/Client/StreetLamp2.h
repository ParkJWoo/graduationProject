#pragma once
#include "Obj.h"
class CStreetLamp2 :
	public CObj
{
public:
	CStreetLamp2();
	virtual ~CStreetLamp2();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	D3DXMATRIX matScale, matTrans;
};

