#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"

IMPLEMENT_SINGLETON(CLineMgr)

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	LINEPOS tPosArr[2] = { LINEPOS(-1009.603f, 400.f), LINEPOS(10000.f, 400.f) };

	m_LineLst.push_back(new CLine(LINEINFO(D3DXVECTOR2(tPosArr[0].fX, tPosArr[0].fY), D3DXVECTOR2(tPosArr[1].fX, tPosArr[1].fY))));
	m_LineLst.push_back(new CLine(LINEINFO(D3DXVECTOR2(tPosArr[1].fX, tPosArr[1].fY), D3DXVECTOR2(tPosArr[0].fX, tPosArr[0].fY))));

	/*LINEPOS tPosArr[4] = { LINEPOS(-509.603f, 400.f), LINEPOS(300.f, 400.f),
		LINEPOS(500.f, 300.f), LINEPOS(700.f, 300.f) };

	m_LineLst.push_back(new CLine(LINEINFO(D3DXVECTOR2(tPosArr[0].fX, tPosArr[0].fY), D3DXVECTOR2(tPosArr[1].fX, tPosArr[1].fY))));
	m_LineLst.push_back(new CLine(LINEINFO(D3DXVECTOR2(tPosArr[1].fX, tPosArr[1].fY), D3DXVECTOR2(tPosArr[2].fX, tPosArr[2].fY))));
	m_LineLst.push_back(new CLine(LINEINFO(D3DXVECTOR2(tPosArr[2].fX, tPosArr[2].fY), D3DXVECTOR2(tPosArr[3].fX, tPosArr[3].fY))));*/
}

void CLineMgr::Render()
{
	for (auto& pLine : m_LineLst)
		pLine->Render();
}

void CLineMgr::Release()
{
	for_each(m_LineLst.begin(), m_LineLst.end(), SafeDelete<CLine*>);
	m_LineLst.clear();
}

bool CLineMgr::LineCollision(float fX, float* pOutY)
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
		// �÷��̾ Ÿ���� ������ ã�Ҵٸ�
	// �� ���� ������ ������ �������� �̿��Ͽ� �÷��̾��� y�� ���Ѵ�.
	// PlayerY = (y2 - y1) / (x2 - x1) * (PlayerX - x1) + y1
		float x1 = pTarget->GetInfo().vStartPos.x;
		float y1 = pTarget->GetInfo().vStartPos.y;
		float x2 = pTarget->GetInfo().vEndPos.x;
		float y2 = pTarget->GetInfo().vEndPos.y;

		*pOutY = (y2 - y1) / (x2 - x1) * (fX - x1) + y1;
		return true;
	}
}
