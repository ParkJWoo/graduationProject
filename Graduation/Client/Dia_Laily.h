#pragma once
#include "Obj.h"
class CDia_Laily :
	public CObj
{
public:
	CDia_Laily();
	virtual ~CDia_Laily();

public:
	void SetLailyCnt(int iCnt) { iLailyCnt = iCnt; }

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int iLailyCnt;
};

