#pragma once
#include "Scene.h"
class CStage2_1 :
	public CScene
{
public:
	CStage2_1();
	virtual ~CStage2_1();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* m_pPlayer;

	CObj* pMonster;
	CObj* pMonster1;
	CObj* pMonster2;
	CObj* pMonster3;
	CObj* pMonster4;
	CObj* pMonster5;
	CObj* pMonster6;
	CObj* pMonster7;
	CObj* pMonster8;
	CObj* pMonster9;
	CObj* pMonster10;

	CObj* pLeftMonster;
	CObj* pLeftMonster1;
	CObj* pLeftMonster2;
	CObj* pLeftMonster3;
	CObj* pLeftMonster4;
	CObj* pLeftMonster5;
	CObj* pLeftMonster6;
	CObj* pLeftMonster7;
	CObj* pLeftMonster8;
	CObj* pLeftMonster9;

	bool bIsCreate;
	bool bIsCreate1;
	bool bIsCreate2;
};

