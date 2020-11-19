#pragma once

class CLine;
class CLineMgr
{
	DECLARE_SINGLETON(CLineMgr)

private:
	CLineMgr();
	~CLineMgr();

public:
	void Initialize();
	void Render();
	void Release();

public:
	bool LineCollision(float fX, float* pOutY);

private:
	list<CLine*> m_LineLst;
};

