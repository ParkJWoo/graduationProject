#pragma once
#include "Scene.h"

class CStage1_2 :
	public CScene
{
public:
	CStage1_2();
	virtual ~CStage1_2();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float fAlphaCnt;
	bool bIsNext;

};

