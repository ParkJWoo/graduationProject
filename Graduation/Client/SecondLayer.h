#pragma once

#include "Obj.h"

class CSecondLayer : public CObj
{
public:
	CSecondLayer();
	virtual ~CSecondLayer();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual HRESULT LoadObjects() override;

private:
	D3DXMATRIX matScale, matTrans;
};



