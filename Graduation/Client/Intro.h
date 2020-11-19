#pragma once
#include "Scene.h"

class CCutToon;
class CIntro :
	public CScene
{
public:
	CIntro();
	virtual ~CIntro();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CObj*	pCutToon;

	float fAlphaCnt;
};
