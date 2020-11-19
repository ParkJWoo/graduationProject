#pragma once
#include "UserInterface.h"
class CSettingIcon :
	public CUserInterface
{
public:
	CSettingIcon();
	virtual ~CSettingIcon();

public:
	// CUserInterface��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

