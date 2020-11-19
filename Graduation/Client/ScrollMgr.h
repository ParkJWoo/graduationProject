#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();

public:
	static const D3DXVECTOR3& GetScroll() { return m_vScroll; }

public:
	static void SetScroll(float x, float y);
	static void SetScrollX(float x) { m_vScroll.x += x; }

private:
	static D3DXVECTOR3 m_vScroll;
};

