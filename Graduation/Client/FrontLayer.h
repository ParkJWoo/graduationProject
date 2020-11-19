#pragma once

#include "Obj.h"

class CFrontLayer : public CObj
{
public:
	CFrontLayer();
	virtual ~CFrontLayer();

public:
	list<TERRAIN*>& GetFrontTerrainLst() { return m_FrontTerrainLst; }

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	HRESULT LoadFrontLayer();

private:
	list<TERRAIN*>		m_FrontTerrainLst;
};

