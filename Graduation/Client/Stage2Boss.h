#pragma once
#include "Scene.h"

class CPlayer;
class CStage2Boss :
	public CScene
{
public:
	CStage2Boss();
	virtual ~CStage2Boss();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* m_pPlayer;
};

