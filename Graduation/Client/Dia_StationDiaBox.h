#pragma once
#include "Obj.h"
class CDia_StationDiaBox :
	public CObj
{
public:
	CDia_StationDiaBox();
	virtual ~CDia_StationDiaBox();

public:
	const int& GetStationDiaCnt() const { return m_iStationDiaCnt; }

public:
	void SetStationDiaCnt(int iDiaCnt) { m_iStationDiaCnt = iDiaCnt; }

public:
	HRESULT LoadStationText();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	//TCHAR szDialog[MAX_STR] = L"";

	vector<TCHAR*> m_vecStationDialog;

	DIALOG* pStationDialog;

	/*list<TCHAR*>::iterator iter_begin;
	list<TCHAR*>::iterator iter_end;*/

	int m_iStationDiaCnt;
};

