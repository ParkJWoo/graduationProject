#pragma once
#include "Scene.h"
class CStageClear :
	public CScene
{
public:
	CStageClear();
	virtual ~CStageClear();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

