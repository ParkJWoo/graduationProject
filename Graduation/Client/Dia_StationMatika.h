#pragma once
#include "Obj.h"
class CDia_StationMatika :
	public CObj
{
public:
	CDia_StationMatika();
	virtual ~CDia_StationMatika();

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

