#include "stdafx.h"
#include "FirstLayer.h"
#include "ToolView.h"

CFirstLayer::CFirstLayer()
	:m_pMainView(nullptr), m_iPropDrawID(0)
{
}


CFirstLayer::~CFirstLayer()
{
	Release();
}

void CFirstLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/FirstLayer/First%d.png", L"First",
		TEX_MULTI, L"Prop", 3)))
	{
		AfxMessageBox(L"First Layer Props Image Insert Failed!!!");
		return;
	}
}

void CFirstLayer::Update()
{
	TERRAIN* pTerrain = new TERRAIN;

	pTerrain->vPos = vPosition;
	pTerrain->byDrawID = m_iPropDrawID;
	pTerrain->byOption = 0;

	m_FirstTerrainLst.push_back(pTerrain);
}

void CFirstLayer::Render(/*list<TERRAIN*> pTerrainLst*/)
{
	CRect rcWnd = {  };

	::GetClientRect(m_pMainView->m_hWnd, &rcWnd);

	float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	D3DXMATRIX matScale, matTrans, matWorld;

	list<TERRAIN*>::iterator iter_begin = m_FirstTerrainLst.begin();
	list<TERRAIN*>::iterator iter_end = m_FirstTerrainLst.end();

	for (; iter_begin != iter_end; ++iter_begin)
	{
		D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 1.f);

		D3DXMatrixTranslation(&matTrans, (*iter_begin)->vPos.x - m_pMainView->GetScrollPos(0), 420.f, 0.f);

		matWorld = matScale * matTrans;

		// SetTransform: 행렬을 반영하는 함수.
		CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

		const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"First", L"Prop", (*iter_begin)->byDrawID);

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

void CFirstLayer::Release()
{
	for_each(m_FirstTerrainLst.begin(), m_FirstTerrainLst.end(), SafeDelete<TERRAIN*>);
	m_FirstTerrainLst.clear();
}

void CFirstLayer::PopFirstTerrainLst()
{
	if (m_FirstTerrainLst.empty())
		return;

	m_FirstTerrainLst.pop_back();
}
