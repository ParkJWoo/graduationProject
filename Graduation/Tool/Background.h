#pragma once

class CToolView;
class CBackground
{
public:
	CBackground();
	~CBackground();

public:
	void SetMainView(CToolView* pView) { m_pMainView = pView; }
	void SetDrawID(int iDrawID) { m_iDrawID = iDrawID; }

public:
	void Initialize();
	void Update();
	void Render(int iDrawID);
	void Release();

private:
	CToolView*	m_pMainView;

	int			m_iDrawID;
};

