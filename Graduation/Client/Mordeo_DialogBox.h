#pragma once
#include "Obj.h"
class CMordeo_DialogBox :
	public CObj
{
public:
	CMordeo_DialogBox();
	virtual ~CMordeo_DialogBox();

public:
	const int& GetMordeoDiaCnt() const { return m_iMordeoDiaCnt; }

public:
	void SetMordeoDiaCnt(int iDiaCnt) { m_iMordeoDiaCnt = iDiaCnt; }

public:
	HRESULT LoadMordeoText();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	//TCHAR szDialog[MAX_STR] = L"";

	vector<TCHAR*> m_vecMordeoDialog;

	DIALOG* pMordeoDialog;

	/*list<TCHAR*>::iterator iter_begin;
	list<TCHAR*>::iterator iter_end;*/

	int m_iMordeoDiaCnt;
};

