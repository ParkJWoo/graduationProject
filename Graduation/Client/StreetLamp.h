#pragma once
#include "Obj.h"
class CStreetLamp :
	public CObj
{
public:
	CStreetLamp();
	virtual ~CStreetLamp();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

