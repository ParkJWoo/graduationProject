#pragma once
#include "Obj.h"
class CMob1_RightArm :
	public CObj
{
public:
	CMob1_RightArm();
	virtual ~CMob1_RightArm();

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
	const TEXINFO* pTexInfo;
};

