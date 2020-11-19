#pragma once
#include "Obj.h"
class CMob1_LeftCalf :
	public CObj
{
public:
	CMob1_LeftCalf();
	virtual ~CMob1_LeftCalf();

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

