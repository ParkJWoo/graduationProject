#pragma once

class CToolView;
class CLine
{
public:
	CLine();
	~CLine();

public:
	vector<LINEINFO*>& GetVecLine() { return m_vecLine; }

public:
	void SetStartPoint(D3DXVECTOR2 vPos) { vStartPos = vPos; }
	void SetEndPoint(D3DXVECTOR2 vPos) { vEndPos = vPos; }
	void SetMainView(CToolView* pView) { m_pMainView = pView; }

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

private:
	D3DXVECTOR2			vPoint[3];

	D3DXVECTOR2			vStartPos;
	D3DXVECTOR2			vEndPos;

	vector<LINEINFO*>	m_vecLine;

	CToolView*			m_pMainView;

	/*D3DXVECTOR2 vPoint;
	D3DXVECTOR2 vPoint;
	D3DXVECTOR2 vPoint;*/

};

