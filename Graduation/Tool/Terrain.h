#pragma once

class CToolView;
class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	vector<TILE*>& GetVecTile() { return m_vecTile; }

public:
	void SetMainView(CToolView* pView) { m_pMainView = pView; }

public:
	void Initialize();
	void Update();
	void Render();
	void MiniRender();
	void Release();

public:
	void TileChange(const D3DXVECTOR3& vPos, const int& iDrawID, int iOption);

private:
	int GetTileIndex(const D3DXVECTOR3& vPos);
	bool Picking(const D3DXVECTOR3& vPos, const int& iIndex);

private:
	vector<TILE*>	m_vecTile;
	CToolView*		m_pMainView;
};

