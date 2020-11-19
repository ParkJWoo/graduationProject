#pragma once
#include "Obj.h"
class CBossFrontLayer :
	public CObj
{
public:
	CBossFrontLayer();
	virtual ~CBossFrontLayer();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

