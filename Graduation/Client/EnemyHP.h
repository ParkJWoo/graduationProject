#pragma once
#include "UserInterface.h"
class CEnemyHP :
	public CUserInterface
{
public:
	CEnemyHP();
	virtual ~CEnemyHP();

public:
	// CUserInterface을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	const TEXINFO* pTexInfo;

	int m_iHp;
};

