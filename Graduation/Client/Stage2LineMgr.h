#pragma once

class CLine;
class CStage2LineMgr
{
	DECLARE_SINGLETON(CStage2LineMgr)

private:
	CStage2LineMgr();
	~CStage2LineMgr();

public:
	void Initialize();
	void Render();
	void Release();

public:
	bool LineCollision(float fX, float* pOutY);

private:
	list<CLine*> m_LineLst;
};

