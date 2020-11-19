#pragma once
#include "Scene.h"
class CLogIn :
	public CScene
{
public:
	CLogIn();
	virtual ~CLogIn();

public:
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj* pStart;
	CObj* pFade;

	float fAlphaCnt;
};

