#include "stdafx.h"
#include "Line.h"

CLine::CLine()
	:m_pMainView(nullptr)
{

}

CLine::~CLine()
{
}

void CLine::Initialize()
{
	LINEINFO* pLine = new LINEINFO;

	pLine->vStartPos = vStartPos;
	pLine->vEndPos = vEndPos;

	pLine->fWidth = 5.f;

	m_vecLine.push_back(pLine);
}

void CLine::Update()
{
}

void CLine::Render()
{
	/*for (size_t i = 0; i < m_vecLine.size(); ++i)
	{
		D3DXVECTOR2 vLine[3] =
		{
			{vStartPos.x,vStartPos.y},
			{vEndPos.x,vEndPos.y},
			{vStartPos.x,vStartPos.y}
		};

		CDevice::GetInstance()->GetLine()->SetWidth(5.f);
		CDevice::GetInstance()->GetLine()->Draw(vLine, 5, D3DCOLOR_ARGB(255, 0, 255, 0));
	}*/
	

	D3DXVECTOR2 vGroundLayer[3] =
	{
		{	0.f, 510.f },
		{ WINCX, 510.f },
		{	0.f, 510.f },
	};

	D3DXVECTOR2 vBackgroundLayer[3] =
	{
		{	0.f, 430.f },
		{ WINCX, 430.f },
		{	0.f, 430.f },

	};

	D3DXVECTOR2 vTopLayer[3] =
	{
		{	0.f, 0.f },
		{ WINCX, 0.f },
		{	0.f, 0.f },

	};

	D3DXVECTOR2 vBottomLayer[3] =
	{
		{	0.f, WINCY },
		{ WINCX, WINCY },
		{	0.f,WINCY },

	};

	CDevice::GetInstance()->GetLine()->Draw(vGroundLayer, 5, D3DCOLOR_ARGB(255, 0, 100, 0));
	CDevice::GetInstance()->GetLine()->Draw(vBackgroundLayer, 5, D3DCOLOR_ARGB(255, 0, 100, 0));
	CDevice::GetInstance()->GetLine()->Draw(vTopLayer, 5, D3DCOLOR_ARGB(255, 0, 100, 0));
	CDevice::GetInstance()->GetLine()->Draw(vBottomLayer, 5, D3DCOLOR_ARGB(255, 0, 100, 0));
}

void CLine::Release()
{
	for_each(m_vecLine.begin(), m_vecLine.end(), SafeDelete<LINEINFO*>);
	m_vecLine.clear();
	m_vecLine.shrink_to_fit();
}

