#pragma once
#include "Scene.h"
class CStage1_3 :
	public CScene
{
public:
	CStage1_3();
	virtual ~CStage1_3();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

