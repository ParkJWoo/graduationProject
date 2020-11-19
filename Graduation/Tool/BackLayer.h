#pragma once

class CToolView;
class CBackLayer
{
public:
	CBackLayer();
	~CBackLayer();

public:
	list<TERRAIN*>& GetBackTerrainLst() { return m_BackTerrainLst; }

public:
	void SetMainView(CToolView* pView) { m_pMainView = pView; }
	void SetPosition(D3DXVECTOR3 vPos) { m_vPosition = vPos; }
	void SetDrawID(int iDrawID) { m_iPropDrawID = iDrawID; }

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

public:
	void PopBackTerrainLst();

private:
	CToolView*			m_pMainView;
	D3DXVECTOR3			m_vPosition;
	int					m_iPropDrawID;

	list<TERRAIN*>		m_BackTerrainLst;
};

