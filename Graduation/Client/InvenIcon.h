#pragma once
#include "UserInterface.h"
class CInvenIcon :
	public CUserInterface
{
public:
	CInvenIcon();
	virtual ~CInvenIcon();
	
public:
	// CUserInterface��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

