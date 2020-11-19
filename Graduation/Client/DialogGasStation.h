#pragma once
#include "Scene.h"
class CDia_StationDiaBox;

class CDialogGasStation :
	public CScene
{
public:
	CDialogGasStation();
	virtual ~CDialogGasStation();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CDia_StationDiaBox* m_pStationDialog;

	int			iStationDiaCnt;
};

