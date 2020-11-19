#pragma once

#include "Obj.h"

class CTerrain : public CObj
{
public:
	CTerrain();
	virtual ~CTerrain();

public:
	vector<TILE*>& GetVecTile() { return m_vecTile; }
	vector<list<TILE*>>& GetVecAdjacency() { return m_vecAdjacency; }

public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	HRESULT LoadTile();
	//void ReadyAdjacency();

private:
	vector<TILE*>	m_vecTile;

	// �� Ÿ���� ���� ������ ������ �׷���.
	vector<list<TILE*>> m_vecAdjacency;

	
};
