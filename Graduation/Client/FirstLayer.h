#pragma once

#include "Obj.h"

class CFirstLayer : public CObj
{
public:
	CFirstLayer();
	virtual ~CFirstLayer();

public:
	void SetImageID(int iDrawID) { m_iDrawID = iDrawID; }

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual HRESULT LoadObjects() override;

};

