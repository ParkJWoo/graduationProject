#pragma once
#include "Obj.h"
class CCage :
	public CObj
{
public:
	CCage();
	virtual ~CCage();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

