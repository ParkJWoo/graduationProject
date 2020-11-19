#pragma once
#include "Obj.h"
class CAfter_DialogBox :
	public CObj
{
public:
	CAfter_DialogBox();
	virtual ~CAfter_DialogBox();

public:
	const int& GetAfterDiaCnt() const { return m_iAfterDialog; }

public:
	void SetAfterDiaCnt(int iDiaCnt) { m_iAfterDialog = iDiaCnt; }

public:
	HRESULT LoadAfterDialog();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	vector<TCHAR*> m_vecAfterDialog;

	DIALOG* pAfterDialog;

	int m_iAfterDialog;
};

