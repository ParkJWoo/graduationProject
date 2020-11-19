#pragma once
#include "Obj.h"
class CButton :
	public CObj
{
public:
	CButton();
	virtual ~CButton();

public:
	void SetImageKey(TCHAR* pImageKey) { m_pImageKey = pImageKey; }

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float fAlphaCnt;
};