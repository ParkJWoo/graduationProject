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
	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	CDia_StationDiaBox* m_pStationDialog;

	int			iStationDiaCnt;
};
