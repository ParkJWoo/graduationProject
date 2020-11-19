#pragma once
#include "Obj.h"
class CFade :
	public CObj
{
public:
	CFade();
	virtual ~CFade();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* pStart;
};

