#pragma once
#include "Scene.h"
class CMordeo_DialogBox;

class CDialogMordeo :
	public CScene
{
public:
	CDialogMordeo();
	virtual ~CDialogMordeo();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CMordeo_DialogBox* m_pMordeoDialog;


	int iMordeoDiaCnt;
};

