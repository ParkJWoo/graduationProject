#pragma once
#include "Obj.h"
class CDia_StationMatika :
	public CObj
{
public:
	CDia_StationMatika();
	virtual ~CDia_StationMatika();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

