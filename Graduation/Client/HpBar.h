#pragma once
#include "UserInterface.h"
class CHpBar :
	public CUserInterface
{
public:
	CHpBar();
	virtual ~CHpBar();

public:
	void SetImageKey(TCHAR* pImageKey) { m_pImageKey = pImageKey; }
	void SetDamage(int iDamage) { const_cast<TEXINFO*>(pTexInfo)->tImgInfo.Width -= iDamage; }
	void SetDamaged(int iDamage) { m_iHpNum -= iDamage; }
 
public:
	// CUserInterface을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	const TEXINFO* pTexInfo;

	float fDamage;

	int m_iHp;
};
