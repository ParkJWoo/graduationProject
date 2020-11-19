#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(LINEINFO & rInfo)
	:m_tInfo(rInfo)
{
}


CLine::~CLine()
{
}

void CLine::Render()
{
	float fScrollX = CScrollMgr::GetScroll().x;

	D3DXVECTOR2 vPoint[4] =
	{
		{ m_tInfo.vStartPos.x - CScrollMgr::GetScroll().x , m_tInfo.vStartPos.y  - CScrollMgr::GetScroll().y},
		{ m_tInfo.vEndPos.x - CScrollMgr::GetScroll().x , m_tInfo.vEndPos.y - CScrollMgr::GetScroll().y},
		{m_tInfo.vStartPos.x - CScrollMgr::GetScroll().x , m_tInfo.vStartPos.y - CScrollMgr::GetScroll().y},
		{m_tInfo.vEndPos.x - CScrollMgr::GetScroll().x , m_tInfo.vEndPos.y - CScrollMgr::GetScroll().y}
	};

	CDevice::GetInstance()->GetLine()->SetWidth(2.f); // ¼±±½±â
	CDevice::GetInstance()->GetLine()->Draw(vPoint, 3, D3DCOLOR_ARGB(255, 255, 0, 0));
}
