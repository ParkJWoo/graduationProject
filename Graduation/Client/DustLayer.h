#pragma once
#include "Obj.h"
class CDustLayer :
	public CObj
{
public:
	CDustLayer();
	virtual ~CDustLayer();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

