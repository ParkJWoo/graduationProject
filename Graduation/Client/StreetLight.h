#pragma once
#include "Obj.h"
class CStreetLight :
	public CObj
{
public:
	CStreetLight();
	virtual ~CStreetLight();

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

