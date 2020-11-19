#pragma once
#include "UserInterface.h"
class CInvenIcon :
	public CUserInterface
{
public:
	CInvenIcon();
	virtual ~CInvenIcon();
	
public:
	// CUserInterface을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

