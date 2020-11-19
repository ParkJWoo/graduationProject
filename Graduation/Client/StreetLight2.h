#pragma once
#include "Obj.h"
class CStreetLight2 :
	public CObj
{
public:
	CStreetLight2();
	virtual ~CStreetLight2();

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

