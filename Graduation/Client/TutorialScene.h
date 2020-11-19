#pragma once
#include "Scene.h"
class CDoor;
class CCage;
class CTutorialScene :
	public CScene
{
public:
	CTutorialScene();
	virtual ~CTutorialScene();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* pPlayer;

	CObj* pHpCase;
	CObj* pHpBar;

	CObj* pMpBar;
	CObj* pMpBar2;
	CObj* pMpCase;

	CObj* pInvenIcon;
	CObj* pInventory;

	CDoor* m_pDoor;

	CCage* m_pCage;
};
