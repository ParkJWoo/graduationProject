#pragma once

class CToolView;
class CFirstLayer
{
public:
	CFirstLayer();
	~CFirstLayer();

public:
	list<TERRAIN*>&	GetFirstTerrainList() { return m_FirstTerrainLst; }

public:
	void SetMainView(CToolView* pView) { m_pMainView = pView; }
	void SetPosition(D3DXVECTOR3 vPos) { vPosition = vPos; }
	void SetDrawID(int iDrawID) { m_iPropDrawID = iDrawID; }

public:
	void Initialize();
	void Update();
	void Render(/*list<TERRAIN*> pTerrainLst*/);
	void Release();

public:
	void PopFirstTerrainLst();

private:
	CToolView*			m_pMainView;
	D3DXVECTOR3			vPosition;
	int					m_iPropDrawID;

	list<TERRAIN*>		m_FirstTerrainLst;
};

