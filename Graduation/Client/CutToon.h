#pragma once
#include "Obj.h"
class CCutToon :
	public CObj
{
public:
	CCutToon();
	virtual ~CCutToon();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float fSpeed;
	float fTime;
};

