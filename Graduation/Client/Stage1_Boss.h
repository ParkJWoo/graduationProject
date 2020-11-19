#pragma once
#include "Scene.h"

class CPlayer;
class CStage1_Boss :
	public CScene
{
public:
	CStage1_Boss();
	virtual ~CStage1_Boss();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* m_pPlayer;

	//CObj* pHpCase;
	//CObj* pHpBar;

	//CObj* pMpBar;
	//CObj* pMpBar2;
	//CObj* pMpCase;

	//CObj* pInvenIcon;
	//CObj* pInventory;
};
