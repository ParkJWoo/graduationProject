#pragma once

#include "Obj.h"

class CBackLayer : public CObj
{
public:
	CBackLayer();
	virtual ~CBackLayer();

public:
	list<TERRAIN*>& GetBackTerrainLst() { return m_BackTerrainLst; }

public:
	void SetImageID(int iDrawID) { m_iDrawID = iDrawID; }

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	HRESULT LoadBackLayer();

private:
	list<TERRAIN*>		m_BackTerrainLst;

	float				m_fAngle;
	float				m_fRotSpeed;
};

