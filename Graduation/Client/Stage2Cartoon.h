#pragma once
#include "Scene.h"
class CStage2Cartoon :
	public CScene
{
public:
	CStage2Cartoon();
	virtual ~CStage2Cartoon();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* pCutToon;


};

