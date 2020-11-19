#pragma once
#include "Obj.h"
class CFrontCage :
	public CObj
{
public:
	CFrontCage();
	virtual ~CFrontCage();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

