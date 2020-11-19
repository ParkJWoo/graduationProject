#pragma once
#include "UserInterface.h"
class CMpBarRight :
	public CUserInterface
{
public:
	CMpBarRight();
	virtual ~CMpBarRight();

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

	int m_iMp = 0;
};

