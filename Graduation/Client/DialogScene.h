#pragma once
#include "Scene.h"
class CDia_DialogBox;

class CDialogScene :
	public CScene
{
public:
	CDialogScene();
	virtual ~CDialogScene();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CDia_DialogBox*	m_pDialog;

	int iDiaCnt;
};
