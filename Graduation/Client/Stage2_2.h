#pragma once
#include "Scene.h"
class CStage2_2 :
	public CScene
{
public:
	CStage2_2();
	virtual ~CStage2_2();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;


};

