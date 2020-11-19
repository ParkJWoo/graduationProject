#pragma once
#include "Obj.h"
class CMob1_LeftLeg :
	public CObj
{
public:
	CMob1_LeftLeg();
	virtual ~CMob1_LeftLeg();

public:
	void SetImageKey(TCHAR* pImageKey) { m_pImageKey = pImageKey; }

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	const TEXINFO* pTexInfo;
};

