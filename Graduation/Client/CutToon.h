#pragma once
#include "Obj.h"
class CCutToon :
	public CObj
{
public:
	CCutToon();
	virtual ~CCutToon();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float fSpeed;
	float fTime;
};

