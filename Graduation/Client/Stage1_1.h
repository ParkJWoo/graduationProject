#pragma once
#include "Scene.h"

class CPlayer;
class CStage1_1 :
	public CScene
{
public:
	CStage1_1();
	virtual ~CStage1_1();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* m_pPlayer;
	float fAlphaCnt;

	bool bIsNext;

	CObj* pMonster; 
	CObj* pMonster2;

	bool bIsCreate;
};

