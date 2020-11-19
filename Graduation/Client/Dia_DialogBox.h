#pragma once
#include "Obj.h"
class CDia_DialogBox :
	public CObj
{
public:
	CDia_DialogBox();
	virtual ~CDia_DialogBox();

public:
	const int& GetDiaCnt() const { return m_iDiaCnt; }

public:
	void SetDiaCnt(int iDiaCnt) { m_iDiaCnt = iDiaCnt; }

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	HRESULT LoadText();

private:
	//TCHAR szDialog[MAX_STR] = L"";

	vector<TCHAR*> m_vecDialog;

	DIALOG* pDialog;

	/*list<TCHAR*>::iterator iter_begin;
	list<TCHAR*>::iterator iter_end;*/

	int m_iDiaCnt;
};

