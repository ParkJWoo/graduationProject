#pragma once
#include "Obj.h"
class CBackLight :
	public CObj
{
public:
	CBackLight();
	virtual ~CBackLight();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	D3DXMATRIX matScale, matTrans;
};

