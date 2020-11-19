#include "stdafx.h"
#include "SecondLayer.h"
#include "ToolView.h"

CSecondLayer::CSecondLayer()
	:m_pMainView(nullptr), m_iPropDrawID(0)
{
}


CSecondLayer::~CSecondLayer()
{
	Release();
}

void CSecondLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/SecondLayer/Second%d.png", L"Second",
		TEX_MULTI, L"Prop", 2)))
	{
		AfxMessageBox(L"Second Layer Props Insert Failed!!!");
		return;
	}
}

void CSecondLayer::Update()
{
	TERRAIN* pTerrain = new TERRAIN;

	pTerrain->vPos = m_vPosition;
	pTerrain->byDrawID = m_iPropDrawID;
	pTerrain->byOption = 0;

	m_SecondTerrainLst.push_back(pTerrain);
}

void CSecondLayer::Render()
{
	CRect rcWnd = {  };

	::GetClientRect(m_pMainView->m_hWnd, &rcWnd);

	float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	D3DXMATRIX matScale, matTrans, matWorld;

	list<TERRAIN*>::iterator iter_begin = m_SecondTerrainLst.begin();
	list<TERRAIN*>::iterator iter_end = m_SecondTerrainLst.end();

	for (; iter_begin != iter_end; ++iter_begin)
	{
		D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 1.f);

		D3DXMatrixTranslation(&matTrans, (*iter_begin)->vPos.x - m_pMainView->GetScrollPos(0), (*iter_begin)->vPos.y - m_pMainView->GetScrollPos(1), 0.f);

		matWorld = matScale * matTrans;

		// SetTransform: 행렬을 반영하는 함수.
		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Second", L"Prop", (*iter_begin)->byDrawID);

		// 이미지의 중점 구하기.
		int iCenterX = pTexInfo->tImgInfo.Width / 2;
		int iCenterY = pTexInfo->tImgInfo.Height / 2;

		// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
			nullptr /*출력할 이미지 영역의 RECT*/,
			&D3DXVECTOR3(iCenterX, iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
			nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CSecondLayer::Release()
{
	for_each(m_SecondTerrainLst.begin(), m_SecondTerrainLst.end(), SafeDelete<TERRAIN*>);
	m_SecondTerrainLst.clear();
}

void CSecondLayer::PopSecondTerrainLst()
{
	if (m_SecondTerrainLst.empty())
		return;

	m_SecondTerrainLst.pop_back();
}
