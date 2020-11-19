#pragma once
#include "Obj.h"
class CStage2CutToon :
	public CObj
{
public:
	CStage2CutToon();
	virtual ~CStage2CutToon();

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

