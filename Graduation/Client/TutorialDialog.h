#pragma once
#include "Obj.h"
class CTutorialDialog :
	public CObj
{
public:
	CTutorialDialog();
	virtual ~CTutorialDialog();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	HRESULT LoadTutorialText();

private:
	vector<TCHAR*> m_vecTutorialDialog;

	DIALOG* pTutorialDialog;

	int m_iDiaCnt;

	float m_fSpeed;


	CObserver* pObserver;

	float m_fStartTime;
};

