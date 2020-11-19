#include "stdafx.h"
#include "Stage2LineMgr.h"
#include "Line.h"

IMPLEMENT_SINGLETON(CStage2LineMgr)

CStage2LineMgr::CStage2LineMgr()
{

}

CStage2LineMgr::~CStage2LineMgr()
{
	Release();
}

void CStage2LineMgr::Initialize()
{
	LINEPOS tPosArr[2] = { LINEPOS(-1009.603f, 420.f), LINEPOS(10000.f, 420.f) };

	m_LineLst.push_back(new CLine(LINEINFO(D3DXVECTOR2(tPosArr[0].fX, tPosArr[0].fY), D3DXVECTOR2(tPosArr[1].fX, tPosArr[1].fY))));
	m_LineLst.push_back(new CLine(LINEINFO(D3DXVECTOR2(tPosArr[1].fX, tPosArr[1].fY), D3DXVECTOR2(tPosArr[0].fX, tPosArr[0].fY))));
}

void CStage2LineMgr::Render()
{
	for (auto& pLine : m_LineLst)
		pLine->Render();
}

void CStage2LineMgr::Release()
{
	for_each(m_LineLst.begin(), m_LineLst.end(), SafeDelete<CLine*>);
	m_LineLst.clear();
}

bool CStage2LineMgr::LineCollision(float fX, float * pOutY)
{
	if (m_LineLst.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& pLine : m_LineLst)
	{
		if (fX >= pLine->GetInfo().vStartPos.x &&
			fX <= pLine->GetInfo().vEndPos.x)
		{
			pTarget = pLine;
			break;
		}
	}

	if (nullptr == pTarget)
		return false;

	else
	{
		// 플레이어가 타야할 라인을 찾았다면
	// 두 점을 지나는 직선의 방정식을 이용하여 플레이어의 y를 구한다.
	// PlayerY = (y2 - y1) / (x2 - x1) * (PlayerX - x1) + y1
		float x1 = pTarget->GetInfo().vStartPos.x;
		float y1 = pTarget->GetInfo().vStartPos.y;
		float x2 = pTarget->GetInfo().vEndPos.x;
		float y2 = pTarget->GetInfo().vEndPos.y;

		*pOutY = (y2 - y1) / (x2 - x1) * (fX - x1) + y1;
		return true;
	}
}
