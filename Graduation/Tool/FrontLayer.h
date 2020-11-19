#pragma once

class CToolView;
class CFrontLayer
{
public:
	CFrontLayer();
	~CFrontLayer();

public:
	list<TERRAIN*>& GetFrontTerrainLst() { return m_FrontTerrainLst; }

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
	void PopFrontTerrainLst();

private:
	CToolView*			m_pMainView;

	D3DXVECTOR3			m_vPosition;
	int					m_iPropDrawID;

	list<TERRAIN*>		m_FrontTerrainLst;
};

