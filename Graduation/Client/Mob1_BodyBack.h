#pragma once
#include "Obj.h"
class CMob1_BodyBack :
	public CObj
{
public:
	CMob1_BodyBack();
	virtual ~CMob1_BodyBack();

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

