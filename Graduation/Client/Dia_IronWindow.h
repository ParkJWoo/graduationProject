#pragma once
#include "Obj.h"
class CDia_IronWindow :
	public CObj
{
public:
	CDia_IronWindow();
	virtual ~CDia_IronWindow();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

