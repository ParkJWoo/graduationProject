#pragma once
#include "Obj.h"
class CDia_LeoLayer :
	public CObj
{
public:
	CDia_LeoLayer();
	virtual ~CDia_LeoLayer();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int m_iAppCnt;
};

