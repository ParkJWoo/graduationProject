#pragma once
#include "UserInterface.h"
class CMpBarRight :
	public CUserInterface
{
public:
	CMpBarRight();
	virtual ~CMpBarRight();

public:
	// CUserInterface��(��) ���� ��ӵ�
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

