#pragma once
#include "Scene.h"

class CAfter_DialogBox;
class CAfterDialogMordeo :
	public CScene
{
public:
	CAfterDialogMordeo();
	virtual ~CAfterDialogMordeo();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CAfter_DialogBox* m_pAfterDialog;


	int iAfterDiaCnt;

	int iDrawID;
};

